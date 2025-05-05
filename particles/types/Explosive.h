//
// Created by Kaposvári Gergő on 2025. 05. 05..
//

#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H
#include "SolidParticle.h"


class Explosive : public SolidParticle {
    int ExplosionTemp;
    int ExplosivePower;
public:

    Explosive(int Power) : SolidParticle() {
        ExplosionTemp = 300;
        ExplosivePower = Power;
    }

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override;


    SDL_Color getColor() const override {
        return {255, 255, 0, 200};
    }


};



#endif //EXPLOSIVE_H
