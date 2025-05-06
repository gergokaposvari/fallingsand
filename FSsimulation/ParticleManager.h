//
// Created by Kaposvári Gergő on 2025. 03. 11..
//

#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <functional>

#include "../particles/EdgeParticle.h"
#include "../particles/Particle.h"
#include "../particles/types/Explosive.h"
#include "../particles/types/FireParticle.h"
#include "../particles/types/PowderParticle.h"
#include "../particles/types/liquids/WaterParticle.h"
#include "../particles/types/liquids/LavaParticle.h"
#include "../particles/types/powders/ExplosivePowderParticle.h"
#include "../particles/types/powders/SandParticle.h"
#include "../particles/types/solids/StoneParticle.h"


class ParticleManager {
private:
    std::vector<std::function<Particle*()>> particleFactories;
    std::vector<std::string> particleNames;
    size_t currentIndex = 0;

public:
    ParticleManager() {
        particleFactories.emplace_back([]() { return new StoneParticle(); });
        particleNames.emplace_back("Stone");
        particleFactories.emplace_back([]() { return new WaterParticle(); });
        particleNames.emplace_back("Water");
        particleFactories.emplace_back([]() { return new SandParticle(rand() % 16 == 0); });
        particleNames.emplace_back("Sand");
        particleFactories.emplace_back([]()   { return new IceParticle(); });
        particleNames.emplace_back("Ice");
        particleFactories.emplace_back([]() { return new LavaParticle(); });
        particleNames.emplace_back("Lava");
        particleFactories.emplace_back([]() { return new Explosive(60); });
        particleNames.emplace_back("Explosive");
        particleFactories.emplace_back([]() { return new ExplosivePowderParticle(20); });
        particleNames.emplace_back("Explosive Powder");
        particleFactories.emplace_back([]() { return new FireParticle(); });
        particleNames.emplace_back("Fire");
    }

    void switchParticle() {
        currentIndex = (currentIndex + 1) % particleFactories.size();
        std::cout << "Particle: " << particleNames[currentIndex] << std::endl;
    }

    Particle* createNewParticle() const {
        return particleFactories[currentIndex]();
    }

};


#endif //PARTICLEMANAGER_H
