//
// Created by Kaposvári Gergő on 2025. 03. 24..
//
#include "StoneParticle.h"
#include "../liquids/LavaParticle.h"

Particle *StoneParticle::melt() {
    return new LavaParticle();
}
