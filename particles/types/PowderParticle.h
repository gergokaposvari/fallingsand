#ifndef POWDERPARTICLE_H
#define POWDERPARTICLE_H
#include "../Particle.h"

class PowderParticle : public Particle {
    bool pointy;
public:

    explicit PowderParticle(bool pointy) : Particle(POWDER), pointy(pointy) {
        Particle::setNeighborhoodSize(3);
    }

    void display() const override {}

    std::pair<int, int> nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) override;
};

#endif // POWDERPARTICLE_H