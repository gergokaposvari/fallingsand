//
// Created by Kaposvári Gergő on 2025. 05. 06..
//

#ifndef EXPLOSIVEPOWDERPARTICLE_H
#define EXPLOSIVEPOWDERPARTICLE_H
#include "../PowderParticle.h"

class ExplosivePowderParticle : public PowderParticle {
    int ExplosionTemp;
    int ExplosivePower;
public:

    ExplosivePowderParticle(int Power) : PowderParticle(false) {
        ExplosionTemp = 300;
        ExplosivePower = Power;
    }

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override;


    SDL_Color getColor() const override {
        return {30, 50, 32, 200};
    }


};

#endif //EXPLOSIVEPOWDERPARTICLE_H
