//
// Created by Kaposvári Gergő on 2025. 05. 05..
//

#include "Explosive.h"

std::pair<int, int> Explosive::nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) {

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


    return std::make_pair(2,2);
}
