//
// Created by Kaposvári Gergő on 2025. 02. 25..
//
#include "LiquidParticle.h"

std::pair<int, int> LiquidParticle::nextPosition(std::array<std::array<Particle *, 3>, 3> &neighborhood, bool direction) {

    int avgTemp = 0;
    int countedParticles = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++ ) {
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



    if (neighborhood[2][1]->getState() == EMPTY) {
        return std::make_pair(1, 0);
    }


    State left = neighborhood[1][0]->getState();
    State leftDown = neighborhood[2][0]->getState();
    State right = neighborhood[1][2]->getState();
    State rightDown = neighborhood[2][2]->getState();

    bool isLeftDownEmpty = leftDown == EMPTY;
    bool isRightDownEmpty = rightDown == EMPTY;
    bool isLeftEmpty = left == EMPTY;
    bool isRightEmpty = right == EMPTY;

    if (isLeftEmpty || isRightEmpty) {
        if (left == SOLID || left == POWDER)
            return std::make_pair(0, 1);
        if (right == SOLID || right == POWDER)
            return std::make_pair(0, -1);
        return direction ? std::make_pair(0, 1) : std::make_pair(0, -1);
    } else if (isLeftDownEmpty && isRightDownEmpty) {
        return direction ? std::make_pair(1, 1) : std::make_pair(1, -1);
    } else if (isLeftDownEmpty) {
        return std::make_pair(1, -1);
    } else if (isRightDownEmpty) {
        return std::make_pair(1, 1);
    }


    return std::make_pair(2,2);
}

