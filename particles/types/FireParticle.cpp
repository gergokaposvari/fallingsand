//
// Created by Kaposvári Gergő on 2025. 05. 05..
//

#include "FireParticle.h"


std::pair<int, int> FireParticle::nextPosition(std::array<std::array<Particle *, 15>, 15> &neighborhood, bool direction) {

    AliveFor--;
    if (AliveFor == 0) {
        return std::make_pair(15, 15);
    }

    State LeftUp = neighborhood[0][0]->getState();
    State MiddleUp = neighborhood[0][1]->getState();
    State RightUp = neighborhood[0][2]->getState();

    bool isLeftUpEmpty = LeftUp == State::EMPTY;
    bool isMiddleUpEmpty = MiddleUp == State::EMPTY;
    bool isRightUpEmpty = RightUp == State::EMPTY;

    std::array<std::pair<int, int>, 3> possibleMoves = {{
        {-1, -1},
        {-1, 0},
        {-1, 1}
    }};
    std::array<bool, 3> isEmpty = {
            isLeftUpEmpty,
            isMiddleUpEmpty,
            isRightUpEmpty
    };

    int betweenOneAndThree = rand() % 3;

    if (isEmpty[betweenOneAndThree]) {
        return possibleMoves[betweenOneAndThree];
    }

    return std::make_pair(2,2);
}