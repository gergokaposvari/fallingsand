//
// Created by Kaposvári Gergő on 2025. 02. 25..
//
#include "LiquidParticle.h"

std::pair<int, int> LiquidParticle::nextPosition(std::array<std::array<Particle *, 11>, 11> &neighborhood, bool direction) {

    // !!! Neighborhood is indexed absolutely in the 11x11 grid, the return value is given as where
    // should the current particle move next relative to its current position !!!

    // Calculation of average temperature in the immediate neighbors
    int avgTemp = 0;
    int countedParticles = 0;
    for (int i = 4; i <= 6; i++) {
        for (int j = 4; j <= 6; j++ ) {
            if (neighborhood[i][j]->getTemperature() != 123) {
                avgTemp += neighborhood[i][j]->getTemperature();
                countedParticles++;
            }
        }
    }
    avgTemp /= countedParticles;
    if (avgTemp < this->getFreezingPoint()) {
        // (3,3) signals the liquid should freeze
        return std::make_pair(3, 3);
    }

    // The liquid should mainly flow down, but added some randomness so it doesnt fall as a square
    if (rand() % 2 ==0 && neighborhood[6][5]->getState() == EMPTY ||(neighborhood[6][5]->getState() == LIQUID && neighborhood[6][5]->getDensity() < density)) {
        return std::make_pair(1, 0);
    }


    State leftDown = neighborhood[6][4]->getState();
    State rightDown = neighborhood[6][6]->getState();

    bool isLeftDownEmpty = leftDown == EMPTY;
    bool isRightDownEmpty = rightDown == EMPTY;

    if (isLeftDownEmpty && isRightDownEmpty) {
        return direction ? std::make_pair(1, 1) : std::make_pair(1, -1);
    }

    // It chooses left or right randomly, then looks for empty space or less dense liquid at a maximum distance of 5
    for (int i = 1; i < 6; i++) {
        int offset = direction ? i : -i;
        for (int row = 5; row <= 6; row++) {
            if (neighborhood[row][5 + offset] &&
                (neighborhood[row][5 + offset]->getState() == EMPTY ||
                 (neighborhood[row][5 + offset]->getState() == LIQUID &&
                  neighborhood[row][5 + offset]->getDensity() < density))) {
                    return std::make_pair(row - 5, offset);
                  }
        }
    }


    // (2,2) signals no movement
    return std::make_pair(2,2);
}

