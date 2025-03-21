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


    ParticleManager particleManager;



    Simulation() : gen(std::random_device{}()), dist(0, 4) {
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if (x == 0 || y == 0 || x == rows-1 || y == cols-1) {
                    grid[x][y] = new EdgeParticle();
                }else{
                    grid[x][y] = new Particle();
                }
            }
        }

        for (int x = 1; x < rows-1; ++x) {
            for (int y = 1; y < cols-1; ++y) {
                if (dist(gen) % 10 == 0) {
                    delete grid[x][y];
                    if (dist(gen) % 4 == 0) {
                        grid[x][y] = new WaterParticle();
                    }else {
                        grid[x][y] = new SandParticle((dist(gen) % 4 == 0));
                    }
                }
            }
        }
        for ( int i = 5; i < cols-5; ++i ) {
            delete grid[48][i];
            grid[48][i] = new StoneParticle();
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
                std::array<std::array<Particle*, 3>, 3> neighborhood = {{
                    {grid[x-1][y-1], grid[x-1][y], grid[x-1][y+1]},
                    {grid[x][y-1], grid[x][y], grid[x][y+1]},
                    {grid[x+1][y-1], grid[x+1][y], grid[x+1][y+1]}
                }};

                std::pair move = grid[x][y]->nextPosition(neighborhood, dist(gen) % 2 == 0);

                if (move != std::make_pair(2, 2)) {
                    if (move == std::make_pair(3, 3)) {
                        grid[x][y] = grid[x][y]->freeze();
                    }else {
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
    }

    void putCell(int x, int y) {

        if (x > rows-1 || x <= 0 || y <= 0  || y > cols-1) {
            return;
        }
        if(grid[x][y]->getState() == EMPTY) {
            delete grid[x][y];
            grid[x][y] = particleManager.createNewParticle();
        }
    }
};
