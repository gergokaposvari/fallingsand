//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef LAVAPARTICLE_H
#define LAVAPARTICLE_H
#include "../LiquidParticle.h"

class StoneParticle;

class LavaParticle : public LiquidParticle{
public:
    int color;

    LavaParticle() : LiquidParticle() {
        setFreezingPoint(200);
        setBoilingPoint(20000000);
        Particle::setTemperature(440);
        LiquidParticle::setDensity(3100);
        color = rand() % 5;
    };

    void display() const override { std::cout << "\033[34m" << std::setw(2) << std::right << "2" << "\033[0m"; }

    Particle* freeze() override;

    SDL_Color getColor() const override {
        static const SDL_Color colors[] = {
            {255, 37, 0, 255},
            {255, 102, 0, 255},
            {242, 242, 23, 255},
            {234, 92, 15, 255},
            {229, 101, 32, 255}
        };

        if (color >= 0 && color < 5) {
            return colors[color];
        }

        return {255, 255, 255, 255}; // White
    }

};

#endif //LAVAPARTICLE_H
