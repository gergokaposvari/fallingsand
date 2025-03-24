//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef STONEPARTICLE_H
#define STONEPARTICLE_H


#include "../SolidParticle.h"

class StoneParticle : public SolidParticle {
public:

    // Sets temperature related things
    StoneParticle() : SolidParticle() {
        setMeltingPoint(950);
        Particle::setTemperature(40);
    }

    // Stone turns into lava
    Particle* melt() override;

    // For console display
    void display() const override { std::cout << "\033[37m" << std::setw(2) << std::right << "3" << "\033[0m"; }

    // Color of stone
    SDL_Color getColor() const override {
        return {128, 128, 128, 255};
    }

};

#endif //STONEPARTICLE_H
