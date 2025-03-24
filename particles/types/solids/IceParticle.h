//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef ICEPARTICLE_H
#define ICEPARTICLE_H
#include "../SolidParticle.h"

class IceParticle : public SolidParticle {
public:


    IceParticle(): SolidParticle() {
        setMeltingPoint(0);
        Particle::setTemperature(-30);
    }

    Particle* melt() override;


    SDL_Color getColor() const override {
        return {173, 216, 230, 200};
    }
};

#endif //ICEPARTICLE_H
