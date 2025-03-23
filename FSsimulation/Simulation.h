#include <iostream>
#include <mutex>
#include <random>
#include <SDL_render.h>
#include <__random/random_device.h>

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
public:
    static const int rows = 200;
    static const int cols = 200;
    Particle* grid[rows][cols];
    std::list<Particle*> movedParticles;
    int tickRate = 0;

    int balrament = 0;
    int jobbrament = 0;


    ParticleManager particleManager;



    Simulation() : gen(std::random_device{}()), dist(0, 1) {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if (x == 0 || y == 0 || x == rows-1 || y == cols-1) {
                    grid[x][y] = new EdgeParticle();
                }else{
                    grid[x][y] = new Particle();
                }
            }
        }
    }

    ~Simulation() {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                delete grid[x][y];
            }
        }
    }

    void switchActive() {
        particleManager.switchParticle();
    }

    void render(SDL_Renderer* renderer, int cellSize) {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                SDL_Rect rect = { y * cellSize, x * cellSize, cellSize, cellSize };
                SDL_SetRenderDrawColor(renderer, grid[x][y]->getColor().r,
                                                 grid[x][y]->getColor().g,
                                                 grid[x][y]->getColor().b, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }



    void simulateTurn() {
        for (int x = 1; x < rows-1; ++x) {
            for (int y = 1; y < cols-1; ++y) {
                if (grid[x][y]->getTraversed())
                    continue;
                int size = grid[x][y]->getNeighborhoodSize();
                int radius = size / 2;

                constexpr int MAX_SIZE = 11;
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
                std::pair move = grid[x][y]->nextPosition(neighborhood, dist(gen) == 0);


                if (move != std::make_pair(2, 2)) {
                    if (move == std::make_pair(3, 3)) {
                        grid[x][y] = grid[x][y]->freeze();
                    }else {
                        if (move.second < 0){
                            balrament++;
                        }
                        if (move.second > 0) {
                            jobbrament++;
                        }
                        Particle *temp = new Particle();
                        temp = grid[x][y];
                        grid[x][y] = grid[x+move.first][y+move.second];
                        grid[x+move.first][y+move.second] = temp;

                        grid[x+move.first][y+move.second]->setTraversed(true);
                        movedParticles.push_back(grid[x+move.first][y+move.second]);

                    }
                }
            }
        }
        flushMoved();
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

    void flushMoved() const {
        for (Particle* p : movedParticles) {
            p->setTraversed(false);
        }
        std::cout << "balra:" << balrament << std::endl;
        std::cout << "jobbra:" << jobbrament << std::endl;
    }

    void putCell(int x, int y) {

        if (x > rows-1 || x <= 0 || y <= 0  || y > cols-1) {
            return;
        }
        if(grid[x][y]->getState() == EMPTY) {


            delete grid[x][y];
            grid[x][y] = particleManager.createNewParticle();
            grid[x][y]->setTraversed(true);
            movedParticles.push_back(grid[x][y]);
        }
    }
};
