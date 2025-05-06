//
// Created by Kaposvári Gergő on 2025. 05. 06..
//


#include "ExplosivePowderParticle.h"

#include <utility>



std::pair<int, int> ExplosivePowderParticle::nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction){
    int avgTemp = 0;
    int countedParticles = 0;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++ ) {
            if (neighborhood[i][j]->getTemperature() != 123) {
                avgTemp += neighborhood[i][j]->getTemperature();
                countedParticles++;
            }
        }
    }
    avgTemp /= countedParticles;
    this->setTemperature(avgTemp);
    if (avgTemp > this->ExplosionTemp) {

        return std::make_pair(33, ExplosivePower);
    }

    // If the powder is not pointy then it falls down half the time
    if (rand() % 2 == 0  && neighborhood[2][1]->getState() == State::EMPTY || neighborhood[2][1]->getState() == State::LIQUID) {
        return std::make_pair(1, 0);
    }

    State right = neighborhood[2][2]->getState();
    State left = neighborhood[2][0]->getState();

    bool right_empty_or_liquid = (right == State::EMPTY || right == State::LIQUID);
    bool left_empty_or_liquid = (left == State::EMPTY || left == State::LIQUID);
    bool right_powder_or_solid = (right == State::POWDER || right == State::SOLID);
    bool left_powder_or_solid = (left == State::POWDER || left == State::SOLID);

    if (right_empty_or_liquid && left_powder_or_solid) {
        return std::make_pair(1, 1);
    } else if (left_empty_or_liquid && right_powder_or_solid) {
        return std::make_pair(1, -1);
    } else if (left_empty_or_liquid && right_empty_or_liquid) {
        return direction % 2 == 0 ? std::make_pair(1, -1) : std::make_pair(1, 1);
    }

    return std::make_pair(2, 2);
}
