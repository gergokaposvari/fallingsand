//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef SOLIDPARTICLE_H
#define SOLIDPARTICLE_H
#include "../Particle.h"

class SolidParticle : public Particle {
    int meltingPoint;
public:
    SolidParticle() : Particle(SOLID) { }

    void display() const override { }

    void setMeltingPoint(int meltingPoint) { this->meltingPoint = meltingPoint; }
    int getMeltingPoint() { return this->meltingPoint; }

    std::pair<int, int> nextPosition(std::array<std::array<Particle*, 3>, 3>& neighborhood, bool direction) override { return std::make_pair(2, 2); }
};

#endif //SOLIDPARTICLE_H
