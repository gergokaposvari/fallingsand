//
// Created by Kaposvári Gergő on 2025. 02. 25..
//

#ifndef LIQUIDPARTICLE_H
#define LIQUIDPARTICLE_H
#include <functional>

#include "../Particle.h"

class LiquidParticle : public Particle {
    //int boilingPoint;
    int freezingPoint;

    int density = 997;
    int center;


public:
    // Sets the Liquids neighborhood to 11x11 grid, because for smoother water a lateral move of 5 is helpful
    LiquidParticle() : Particle(LIQUID) {
        this->Particle::setNeighborhoodSize(11);
        center = Particle::getNeighborhoodSize()/2;
    }


    void display() const override { }

    //void setBoilingPoint(int boilingPoint) { this->boilingPoint = boilingPoint; }
    //int getBoilingPoint() { return this->boilingPoint; }


    void setFreezingPoint(int freezingPoint) { this->freezingPoint = freezingPoint; }
    int getFreezingPoint() { return this->freezingPoint; }

    void setDensity(int density) override { this->density = density; }
    int getDensity() override { return this->density; }

    void setNeighborhoodSize(int size) override {
        if (size >= 3 &&size <= 15 ){
            neighborhoodSize = size;
            center = size/2;
        }
    }




    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override;
};

#endif //LIQUIDPARTICLE_H
