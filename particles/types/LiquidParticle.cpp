//
// Created by Kaposvári Gergő on 2025. 02. 25..
//
#include "LiquidParticle.h"

std::pair<int, int> LiquidParticle::nextPosition(std::array<std::array<Particle *, 11>, 11> &neighborhood, bool direction) {

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
        return std::make_pair(3, 3);
    }


    if (neighborhood[6][5]->getState() == EMPTY ||(neighborhood[6][5]->getState() == LIQUID && neighborhood[6][5]->getDensity() < density)) {
        return std::make_pair(1, 0);
    }

    State left = neighborhood[5][4]->getState();
    State leftDown = neighborhood[6][4]->getState();
    State right = neighborhood[5][6]->getState();
    State rightDown = neighborhood[6][6]->getState();

    bool isLeftDownEmpty = leftDown == EMPTY;
    bool isRightDownEmpty = rightDown == EMPTY;

    if (isLeftDownEmpty && isRightDownEmpty) {
        return direction ? std::make_pair(1, 1) : std::make_pair(1, -1);
    }

    // Véletlenszerűen választ egy irányt, és abban az irányban legfeljebb 5 távolságra keres helyet
    for (int i = 1; i < 6; i++) {
        if (direction) {
            if (neighborhood[5][5 + i] != nullptr && (neighborhood[5][5 + i]->getState() == EMPTY || (
                    neighborhood[5][5 + i]->getState() == LIQUID && neighborhood[5][5 + i]->getDensity() < density))) {
                return std::make_pair(0, i);
            }
        }else {
            if (neighborhood[5][5-i] != nullptr && (neighborhood[5][5-i]->getState() == EMPTY || (
                    neighborhood[5][5-i]->getState() == LIQUID && neighborhood[5][5-i]->getDensity() < density))) {
                return std::make_pair(0, -i);
            }
        }
    }







    return std::make_pair(2,2);
}

