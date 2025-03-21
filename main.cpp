#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "FSsimulation/Simulation.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int CELL_SIZE = 4;
bool running = true;
bool placing = false;
int BRUSH_SIZE = 5;

void mousePress(Simulation& mainSimulation) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int gridX = mouseX / CELL_SIZE;
    int gridY = mouseY / CELL_SIZE;

    for (int i = -1*BRUSH_SIZE; i <= BRUSH_SIZE; i++) {
        for (int j = -1*BRUSH_SIZE; j <= BRUSH_SIZE; j++) {
            mainSimulation.putCell(gridY+i, gridX+j);
        }
    }

}

void update(Simulation& mainSimulation) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    placing = true;
                    mousePress(mainSimulation);
                }
            break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    placing = false;
                }
            break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_DOWN) {
                    if (BRUSH_SIZE > 1) {
                        BRUSH_SIZE--;
                    }
                }else if (e.key.keysym.sym == SDLK_UP) {
                    if (BRUSH_SIZE < 10) {
                        BRUSH_SIZE++;
                    }
                }else if (e.key.keysym.sym == SDLK_p) {
                    mainSimulation.switchActive();
                }

                break;
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Falling Sand Simulation",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Simulation mainSimulation;

    SDL_Event event;

    Uint32 frameStart;
    const int FRAME_DELAY = 1000 / 60;
    int simulateEveryXFrames = 0;

    while (running) {
        frameStart = SDL_GetTicks();

        update(mainSimulation);

        if (placing) {
            mousePress(mainSimulation);
        }

        if (!running) break;

        //if ( simulateEveryXFrames % 2 == 0){
            mainSimulation.simulateTurn();
        //}

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        mainSimulation.render(renderer, CELL_SIZE);

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
            simulateEveryXFrames++;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



