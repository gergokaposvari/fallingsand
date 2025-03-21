//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef WATERPARTICLE_H
#define WATERPARTICLE_H
#include "../LiquidParticle.h"
#include "../solids/IceParticle.h"

class WaterParticle : public LiquidParticle{
    public:

    WaterParticle() : LiquidParticle() {
        setFreezingPoint(0);
        setBoilingPoint(100);
        Particle::setTemperature(10);
    };

    void display() const override { std::cout << "\033[34m" << std::setw(2) << std::right << "2" << "\033[0m"; }

    Particle* freeze() override {
        return new IceParticle();
    }

    SDL_Color getColor() const override {
        return {0, 0, 255, 255};
    }

};

#endif //WATERPARTICLE_H
