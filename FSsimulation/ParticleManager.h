//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <functional>

#include "../particles/EdgeParticle.h"
#include "../particles/Particle.h"
#include "../particles/types/PowderParticle.h"
#include "../particles/types/liquids/WaterParticle.h"
#include "../particles/types/liquids/LavaParticle.h"
#include "../particles/types/powders/SandParticle.h"
#include "../particles/types/solids/StoneParticle.h"


class ParticleManager {
private:
    std::vector<std::function<Particle*()>> particleFactories;
    size_t currentIndex = 0;

public:
    ParticleManager() {
        particleFactories.emplace_back([]() { return new StoneParticle(); });
        particleFactories.emplace_back([]() { return new WaterParticle(); });
        particleFactories.emplace_back([]() { return new SandParticle(rand() % 16 == 0); });
        particleFactories.emplace_back([]()   { return new IceParticle(); });
        particleFactories.emplace_back([]() { return new LavaParticle(); });
    }

    void switchParticle() {
        currentIndex = (currentIndex + 1) % particleFactories.size();
        std::cout << "Particle: " << currentIndex << std::endl;
    }

    Particle* createNewParticle() const {
        return particleFactories[currentIndex]();
    }

};


#endif //PARTICLEMANAGER_H
