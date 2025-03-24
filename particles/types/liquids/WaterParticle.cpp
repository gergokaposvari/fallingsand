//
// Created by Kaposvári Gergő on 2025. 03. 24..
//
#include "WaterParticle.h"
#include "../solids/IceParticle.h"

Particle *WaterParticle::freeze() {
    return new IceParticle();
}
