//
// Created by Kaposvári Gergő on 2025. 03. 24..
//
#include "LavaParticle.h"
#include "../solids/StoneParticle.h"

Particle *LavaParticle::freeze() {
    return new StoneParticle();
}