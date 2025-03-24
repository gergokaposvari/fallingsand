//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef SOLIDPARTICLE_H
#define SOLIDPARTICLE_H
#include "../Particle.h"

class SolidParticle : public Particle {
    int meltingPoint;
public:
    SolidParticle() : Particle(SOLID) {
    }

    void display() const override { }

    void setMeltingPoint(int meltingPoint) { this->meltingPoint = meltingPoint; }
    int getMeltingPoint() { return this->meltingPoint; }

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 11>, 11> &neighborhood, bool direction) override {

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
        if (avgTemp > this->getMeltingPoint()) {
            return std::make_pair(4, 4);
        }
        return std::make_pair(2, 2);
    }
};

#endif //SOLIDPARTICLE_H
