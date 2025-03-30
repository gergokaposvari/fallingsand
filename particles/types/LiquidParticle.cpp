//
// Created by Kaposvári Gergő on 202center. 02. 2center..
//
#include "LiquidParticle.h"

std::pair<int, int> LiquidParticle::nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) {

    // !!! Neighborhood is indexed absolutely in the 11x11 grid, the return value is given as where
    // should the current particle move next relative to its current position !!!

    // Calculation of average temperature in the immediate neighbors
    int avgTemp = 0;
    int countedParticles = 0;
    for (int i = center-1; i <= center+1; i++) {
        for (int j = center-1; j <= center+1; j++ ) {
            if (neighborhood[i][j]->getTemperature() != 123) {
                avgTemp += neighborhood[i][j]->getTemperature();
                countedParticles++;
            }
        }
    }
    avgTemp /= countedParticles;
    if (avgTemp < this->getFreezingPoint()) {
        this->setTemperature(avgTemp);
        // (3,3) signals the liquid should freeze
        return std::make_pair(3, 3);
    }

    // The liquid should mainly flow down, but added some randomness so it doesnt fall as a square
    if (rand() % 2 ==0 && neighborhood[center+1][center]->getState() == EMPTY ||(neighborhood[center+1][center]->getState() == LIQUID && neighborhood[center+1][center]->getDensity() < density)) {

        return std::make_pair(1, 0);
    }

    State leftDown = neighborhood[center+1][center-1]->getState();
    State left = neighborhood[center][center-1]->getState();

    State rightDown = neighborhood[center+1][center+1]->getState();
    State right = neighborhood[center][center+1]->getState();

    bool isLeftDownEmpty = leftDown == EMPTY && left != SOLID;
    bool isRightDownEmpty = rightDown == EMPTY && right != SOLID;

    if (isLeftDownEmpty && isRightDownEmpty) {

        return direction ? std::make_pair(1, 1) : std::make_pair(1, -1);
    }

    // It chooses left or right randomly, then looks for empty space or less dense liquid at a maximum distance of center
    for (int i = 1; i <= center; i++) {
        int offset = direction ? i : -i;
        for (int row = center; row <= center+1; row++) {
            if (neighborhood[row][center+offset]->getState() == SOLID) {
                return std::make_pair(2, 2);
            }
            if (neighborhood[row][center + offset] &&
                (neighborhood[row][center + offset]->getState() == EMPTY ||
                 (neighborhood[row][center + offset]->getState() == LIQUID &&
                  neighborhood[row][center + offset]->getDensity() < density))) {

                return std::make_pair(row - center, offset);
                  }
        }
    }

    // (2,2) signals no movement
    return std::make_pair(2,2);
}

