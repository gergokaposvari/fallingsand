//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef ICEPARTICLE_H
#define ICEPARTICLE_H
#include "../SolidParticle.h"

class IceParticle : public SolidParticle {
public:

    // Sets temperature related things
    IceParticle(): SolidParticle() {
        setMeltingPoint(0);
        Particle::setTemperature(-5);
    }

    // Ice turns into water
    Particle* melt() override;

    // Color of ice
    SDL_Color getColor() const override {
        return {173, 216, 230, 200};
    }
};

#endif //ICEPARTICLE_H
