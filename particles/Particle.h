#ifndef PARTICLE_H
#define PARTICLE_H
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <SDL2/SDL.h>

#include "types/State.h"

class Particle {
    // The state of the particle (empty, powder, liquid solid)
    State state;

    // Stores if the particle has moved this turn
    bool traversed = false;

    // Temp of the particle
    int temperature;
protected:
    // The size of the neighborhood which is looked at when asking the particle to move
    int neighborhoodSize = 1;


public:


    // Default particle is empty
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

    // Given the current neighborhood the particle determines where to move next,
    // direction is used to decide left or right, it is generated randomly in simulation.h
    virtual std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) { return {2,2}; }
};

#endif // PARTICLE_H