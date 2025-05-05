#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_ttf.h>
#include "FSsimulation/Simulation.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 840;
const int CELL_SIZE = 3;
bool running = true;
bool placing = false;
bool deleting = false;
int BRUSH_SIZE = 5;

// Places cells in a BRUSH_SIZE sized square
void mousePress(Simulation& mainSimulation) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int gridX = mouseX / CELL_SIZE;
    int gridY = mouseY / CELL_SIZE;

    if (BRUSH_SIZE == 1) {
        mainSimulation.putCell(gridY, gridX);
    }else {
        for (int i = -1*BRUSH_SIZE; i <= BRUSH_SIZE; i++) {
            for (int j = -1*BRUSH_SIZE; j <= BRUSH_SIZE; j++) {
                mainSimulation.putCell(gridY+i, gridX+j);
            }
        }
    }

}

void deleteArea(Simulation& mainSimulation){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int gridX = mouseX / CELL_SIZE;
    int gridY = mouseY / CELL_SIZE;

    if (BRUSH_SIZE == 1) {
        mainSimulation.deleteCell(gridY, gridX);
    }else {
        for (int i = -1*BRUSH_SIZE; i <= BRUSH_SIZE; i++) {
            for (int j = -1*BRUSH_SIZE; j <= BRUSH_SIZE; j++) {
                mainSimulation.deleteCell(gridY+i, gridX+j);
            }
        }
    }
}

// Handles user input
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
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    deleting = true;
                    deleteArea(mainSimulation);
                }
            break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    placing = false;
                }
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    deleting = false;
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
                }else if (e.key.keysym.sym == SDLK_t) {
                    mainSimulation.testPerf();
                }else if (e.key.keysym.sym == SDLK_c) {
                    mainSimulation.clearGrid();
                }

                break;
        }
    }
}

// Function to render the FPS counter
void renderFPS(SDL_Renderer* renderer, TTF_Font* font, int fps) {
    SDL_Color color = {255, 255, 255, 255}; // White color
    char fpsText[16];
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);

    SDL_Surface* surface = TTF_RenderText_Solid(font, fpsText, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) return;

    int textW, textH;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect destRect = {WINDOW_WIDTH - textW - 10, 10, textW, textH};

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

//The main loop drawing the game and starting the simulation
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF could not initialize! TTF_Error: %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 16);
    if (!font) {
        SDL_Log("Failed to load font! TTF_Error: %s", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
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
    const int FRAME_DELAY = 1000 / 120;
    int simulateEveryXFrames = 0;
    int frameCount = 0;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        frameStart = SDL_GetTicks();
        frameCount++;

        Uint32 elapsed = frameStart - lastTime;
        int fps = (elapsed > 0) ? (frameCount * 1000) / elapsed : 0;
        if (elapsed > 1000) {
            frameCount = 0;
            lastTime = frameStart;

        }

        update(mainSimulation);
        if (placing) {
            mousePress(mainSimulation);
        }
        if (deleting) {
            deleteArea(mainSimulation);
        }
        if (!running) break;


        mainSimulation.simulateTurn();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        mainSimulation.render(renderer, CELL_SIZE);
        renderFPS(renderer, font, fps);

        SDL_RenderPresent(renderer);


    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
