//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef STONEPARTICLE_H
#define STONEPARTICLE_H


#include "../SolidParticle.h"

class LavaParticle;


class StoneParticle : public SolidParticle {
public:

    StoneParticle() : SolidParticle() {
        setMeltingPoint(200);
        Particle::setTemperature(20);
    }

    Particle* melt() override;

    void display() const override { std::cout << "\033[37m" << std::setw(2) << std::right << "3" << "\033[0m"; }
    SDL_Color getColor() const override {
        return {128, 128, 128, 255};
    }

};

#endif //STONEPARTICLE_H
