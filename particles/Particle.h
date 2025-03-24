#ifndef PARTICLE_H
#define PARTICLE_H
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <SDL2/SDL.h>

#include "types/State.h"

class Particle {
    State state;
    bool traversed = false;

    int temperature;

    int neighborhoodSize = 3;


public:



    Particle(State state = EMPTY) : state(state) {
        Particle::setTemperature(123);
    }

    virtual ~Particle() {}

    virtual void display() const { std::cout << std::setw(2) << 0; }

    virtual SDL_Color getColor() const {
        return {0, 0, 0, 255};
    }

    virtual State getState() const { return state; }

    virtual bool getTraversed() const { return traversed; }
    virtual void setTraversed(bool state) { traversed = state; }

    virtual int getTemperature() const { return temperature; }
    virtual void setTemperature(int temperature) { this->temperature = temperature; }

    virtual int getDensity() {return -1;}
    virtual void setDensity(int density) { return;}

    virtual int getNeighborhoodSize() { return neighborhoodSize; }
    virtual void setNeighborhoodSize(int size) { neighborhoodSize = size; }


    virtual Particle* freeze() {
        return new Particle();
    }

    virtual Particle* melt() {
        return new Particle();
    }


    virtual std::pair<int, int> nextPosition(std::array<std::array<Particle *, 11>, 11> &neighborhood, bool direction) { return {2,2}; }
};

#endif // PARTICLE_H