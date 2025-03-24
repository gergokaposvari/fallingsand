//
// Created by Kaposvári Gergő on 2025. 03. 24..
//
#include "IceParticle.h"
#include "../liquids/WaterParticle.h"

Particle *IceParticle::melt() {
    return new WaterParticle();
}
