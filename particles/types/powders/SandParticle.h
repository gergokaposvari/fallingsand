#ifndef SANDPARTICLE_H
#define SANDPARTICLE_H
#include <iomanip>
#include <ios>
#include <iostream>

#include "../PowderParticle.h"

class SandParticle : public PowderParticle {
public:

    SandParticle(bool pointy) : PowderParticle(pointy) {
        Particle::setTemperature(20);
    }

    void display() const override { std::cout << "\033[33m" << std::setw(2) << std::right << "1" << "\033[0m"; }
    SDL_Color getColor() const override {
        return {194, 178, 128, 255};
    }

};

#endif //SANDPARTICLE_H
