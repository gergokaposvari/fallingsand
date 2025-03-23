//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef LIQUIDPARTICLE_H
#define LIQUIDPARTICLE_H
#include <functional>

#include "../Particle.h"

class LiquidParticle : public Particle {
    int boilingPoint;
    int freezingPoint;

    int density = 997;

public:
    LiquidParticle() : Particle(LIQUID) {
        this->Particle::setNeighborhoodSize(11);
    }

    void display() const override { }

    void setBoilingPoint(int boilingPoint) { this->boilingPoint = boilingPoint; }
    int getBoilingPoint() { return this->boilingPoint; }

    void setFreezingPoint(int freezingPoint) { this->freezingPoint = freezingPoint; }
    int getFreezingPoint() { return this->freezingPoint; }

    void setDensity(int density) override { this->density = density; }
    int getDensity() override { return this->density; }




    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 11>, 11> &neighborhood, bool direction) override;
};

#endif //LIQUIDPARTICLE_H
