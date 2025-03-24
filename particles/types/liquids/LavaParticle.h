//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef LAVAPARTICLE_H
#define LAVAPARTICLE_H
#include "../LiquidParticle.h"

class StoneParticle;

class LavaParticle : public LiquidParticle{
public:
    // A random number between 1 and 5 for color
    int color;

    // Sets temperature related variables and density, also color randomness.
    LavaParticle() : LiquidParticle() {
        setFreezingPoint(1200);
        //setBoilingPoint(20000000);
        Particle::setTemperature(2400);
        LiquidParticle::setDensity(3100);
        color = rand() % 5;
    };

    // From early development, when the simulation ran on console
    void display() const override { std::cout << "\033[34m" << std::setw(2) << std::right << "2" << "\033[0m"; }

    // Lava turns to Stone
    Particle* freeze() override;

    // Different colors to make lava look like lava, shades of orange and red
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
