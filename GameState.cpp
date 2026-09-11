#include "GameState.hpp"

GameState::GameState()
    : border{59, 19},
    head{border.x / 2, border.y / 2},
    food{0, 0},
    snake{
        {border.x / 2, border.y / 2},
        {border.x / 2, border.y / 2 + 1},
        {border.x / 2, border.y / 2 + 2}
    },
    alive(true),
    score(0),
    ateFood(false),
    tick(0)
{}

void GameState::resetTickFlags() {
    ateFood = false;
}
