//
// Created by Kaposvári Gergő on 2025. 05. 05..
//

#ifndef FIREPARTICLE_H
#define FIREPARTICLE_H

#include "../Particle.h"



class FireParticle : public Particle {

    int AliveFor;

    public:

    FireParticle(int Alive = 20) : Particle(FIRE) {
        this->Particle::setNeighborhoodSize(3);
        Particle::setTemperature(479);
        AliveFor = Alive + (rand() % 10 - 5);
    }

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override;


    SDL_Color getColor() const override {
        return {255, 0, 0, 200};
    }
};



#endif //FIREPARTICLE_H
