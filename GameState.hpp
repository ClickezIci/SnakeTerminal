#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <deque>
#include "Structures.hpp"

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct GameState {
    Segment border;
    Segment head;
    Segment food;
    std::deque<Segment> snake;

    Direction dir = Direction::RIGHT;
    Direction nextDir = Direction::RIGHT;

    bool alive;
    int score;
    bool ateFood;
    int tick;

    GameState();              // ✅ DÉCLARATION
    void resetTickFlags();
};

enum class Screen {
    MENU,
    GAME,
    PAUSE,
    GAME_OVER,
    EXIT
};

struct AppState {
    Screen screen = Screen::MENU;
    bool running = true;
    bool screenJustEntered = true;
};

#endif
