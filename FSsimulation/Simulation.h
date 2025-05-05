#include <iostream>
#include <mutex>
#include <random>
#include <SDL_render.h>
#include <__random/random_device.h>
#include <thread>
#include <vector>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio.hpp>
#include <boost/thread/locks.hpp>



#include "ParticleManager.h"
#include "../particles/EdgeParticle.h"
#include "../particles/Particle.h"
#include "../particles/types/PowderParticle.h"
#include "../particles/types/liquids/WaterParticle.h"
#include "../particles/types/powders/SandParticle.h"
#include "../particles/types/solids/StoneParticle.h"

class Simulation {
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
    std::mutex gridMutex;
    static const int rows = 280;
    static const int cols = 400;
    std::mutex cellLocks[rows][cols];

public:
    Particle* grid[rows][cols];
    std::vector<std::list<Particle*>> movedParticlesPerThread;
    static const int nThreads = 4;
    std::mutex movedParticlesPerThreadMutex[nThreads];

    int turn = 0;

    ParticleManager particleManager;
    boost::asio::thread_pool threadPool;

    Simulation() : gen(std::random_device{}()), dist(0, 9), threadPool(nThreads) {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1) {
                    grid[x][y] = new EdgeParticle();
                } else {
                    grid[x][y] = new Particle();
                }
            }
        }
        movedParticlesPerThread.resize(nThreads);
    }

    ~Simulation() {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                delete grid[x][y];
            }
        }
        threadPool.join();
    }

    void switchActive() {
        particleManager.switchParticle();
    }

    void render(SDL_Renderer* renderer, int cellSize) {
        int totalChunks = nThreads;
        int colsPerChunk = cols / totalChunks;


        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if ( y % colsPerChunk == 0 ) {
                    SDL_Rect rect = { y * cellSize, x * cellSize, cellSize, cellSize };
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }else {
                    SDL_Rect rect = { y * cellSize, x * cellSize, cellSize, cellSize };
                    SDL_SetRenderDrawColor(renderer, grid[x][y]->getColor().r,
                                                     grid[x][y]->getColor().g,
                                                     grid[x][y]->getColor().b, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }

    void simulateTurn() {
        int totalChunks = nThreads;
        int colsPerChunk = cols / totalChunks;

        for (int i = nThreads-1; i >= 0; --i) {
            int startCol = i * colsPerChunk;
            int endCol = (i == totalChunks - 1) ? cols : startCol + colsPerChunk;

            boost::asio::post(threadPool, [this, startCol, endCol, i]() {
                this->processChunk(endCol, startCol, i);
                this->flushMoved(i);
            });
        }

    }


    void processChunk(int endCol, int startCol, int threadIndex) {
        for (int x = rows-2; x > 0; x--) {
            if (x % 2 == 0) {
                for (int y = startCol; y < endCol; y++) {
                    processParticle(x, y, threadIndex);
                }
            } else {
                for (int y = endCol; y > startCol; y--) {
                    processParticle(x, y, threadIndex);
                }
            }
        }
        turn++;
    }

    // This is needed to alternate left to right order
    void processParticle(int x, int y, int threadIndex) {

        if (grid[x][y]->getTraversed())
            return;
        int size = grid[x][y]->getNeighborhoodSize();
        int radius = size / 2;


        constexpr int MAX_SIZE = 15;
        std::array<std::array<Particle*, MAX_SIZE>, MAX_SIZE> neighborhood;
        if (size > MAX_SIZE) size = MAX_SIZE;

        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    neighborhood[dx + radius][dy + radius] = grid[nx][ny];

                } else {
                    neighborhood[dx + radius][dy + radius] = nullptr;
                }
            }
        }
        std::pair move = grid[x][y]->nextPosition(neighborhood, (dist(gen) % 2 == 0));


        if (move != std::make_pair(2, 2)) {
            if (move == std::make_pair(3, 3)) {
                grid[x][y] = grid[x][y]->freeze();
            } else if (move == std::make_pair(4, 4)) {
                grid[x][y] = grid[x][y]->melt();
            } else if (move == std::make_pair(15, 15)) {
                grid[x][y] = new Particle();
            } else if (move.first == 33){
                boost::unique_lock<std::mutex> lock(gridMutex);
                int maxDist = move.second;

                for (int dx = -maxDist; dx <= maxDist; ++dx) {
                    for (int dy = -maxDist; dy <= maxDist; ++dy) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 1 && nx < rows-1 && ny >= 1 && ny < cols-1) {
                            double distance = sqrt(dx * dx + dy * dy);
                            if (distance <= maxDist) {
                                grid[nx][ny] = new FireParticle(35);
                            }
                        }
                    }
                }

                lock.unlock();
            } else {
                int newX = x + move.first;
                int newY = y + move.second;

                std::scoped_lock lock(cellLocks[x][y], cellLocks[newX][newY], movedParticlesPerThreadMutex[threadIndex]);
                Particle *temp = grid[x][y];
                grid[x][y] = grid[newX][newY];
                grid[newX][newY] = temp;

                grid[newX][newY]->setTraversed(true);
                movedParticlesPerThread[threadIndex].push_back(grid[newX][newY]);
            }
        }
    }

    void displayGrid() {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                grid[x][y]->display();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    void flushMoved(const int i) {
        std::scoped_lock lock(movedParticlesPerThreadMutex[i]);
        for (Particle* p : movedParticlesPerThread[i]) {
            p->setTraversed(false);
        }
        movedParticlesPerThread[i].clear();
    }

    void putCell(int x, int y) {
        std::scoped_lock lock(cellLocks[x][y]);
        int place = 0;
        if (particleManager.createNewParticle()->getState() == SOLID) {
            place = 1;
        } else {
            place = 5;
        }
        if (dist(gen) % place == 0) {
            if (x > rows-1 || x <= 0 || y <= 0  || y > cols-1) {
                return;
            }
            if(grid[x][y]->getState() == EMPTY) {
                grid[x][y] = particleManager.createNewParticle();
            }
        }
    }
    void deleteCell(int x, int y) {
        std::scoped_lock lock(cellLocks[x][y]);
        grid[x][y] = new Particle();
    }

    void testPerf() {
        for ( int i = 1; i < cols-1; i++) {
            for (int j = 1; j < 100; j++) {
                std::scoped_lock lock(cellLocks[j][i]);
                grid[j][i] = new WaterParticle();
            }
        }
    }

    void clearGrid() {
        for (int x = 1; x < rows-1; ++x) {
            for (int y = 1; y < cols-1; ++y) {
                grid[x][y] = new Particle();
            }
        }
    }
};
