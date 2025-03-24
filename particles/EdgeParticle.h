//
// Created by Kaposvári Gergő on 2025. 02. 18..
//

#ifndef EDGEPARTICLE_H
#define EDGEPARTICLE_H
#include "Particle.h"

class EdgeParticle : public Particle {
public:

    //A falak sima tömör részecskék
    explicit EdgeParticle() : Particle(SOLID) { }

    void display() const override { std::cout << "\033[31m-1\033[0m"; }
    SDL_Color getColor() const override {
        return {128, 128, 128, 255};
    }
};

#endif //EDGEPARTICLE_H
