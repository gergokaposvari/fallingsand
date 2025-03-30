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
        Particle::setNeighborhoodSize(3);
    }

    void display() const override { }

    void setMeltingPoint(int meltingPoint) { this->meltingPoint = meltingPoint; }
    int getMeltingPoint() { return this->meltingPoint; }

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override {


        // !!! Neighborhood is indexed absolutely in the 11x11 grid, the return value is given as where
        // should the current particle move next relative to its current position !!!

        // Calculation of average temperature in the immediate neighbors
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
            this->setTemperature(avgTemp);
            // (4,4) signals melting
            return std::make_pair(4, 4);
        }

        // (2,2) signals no movement
        return std::make_pair(2, 2);
    }
};

#endif //SOLIDPARTICLE_H
