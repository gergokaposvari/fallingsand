//
// Created by Kaposvári Gergő on 2025. 02. 16..
//
#include "PowderParticle.h"
#include <cstdlib>

std::pair<int, int> PowderParticle::nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) {

    // !!! Neighborhood is indexed absolutely in the 11x11 grid, the return value is given as where
    // should the current particle move next relative to its current position !!!

    // If the powder is not pointy then it falls down half the time
    if ((rand() % 2 == 0 || pointy) && neighborhood[2][1]->getState() == State::EMPTY || neighborhood[2][1]->getState() == State::LIQUID) {
        return std::make_pair(1, 0);
    }

    State right = neighborhood[2][2]->getState();
    State left = neighborhood[2][0]->getState();

    bool right_empty_or_liquid = (right == State::EMPTY || right == State::LIQUID);
    bool left_empty_or_liquid = (left == State::EMPTY || left == State::LIQUID);
    bool right_powder_or_solid = (right == State::POWDER || right == State::SOLID);
    bool left_powder_or_solid = (left == State::POWDER || left == State::SOLID);

    if (right_empty_or_liquid && left_powder_or_solid && !pointy) {
        return std::make_pair(1, 1);
    } else if (left_empty_or_liquid && right_powder_or_solid && !pointy) {
        return std::make_pair(1, -1);
    } else if (left_empty_or_liquid && right_empty_or_liquid && !pointy) {
        return direction % 2 == 0 ? std::make_pair(1, -1) : std::make_pair(1, 1);
    }

    return std::make_pair(2, 2);
}
