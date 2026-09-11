#include "input.h"
#include "GamePlay.h"

#include <ncurses.h>


void handleGameInput(const std::string &language,
                     AppState &app,
                     GameState &game,
                     int ch)
{
    if (ch == ERR) return;

    // --- GLOBAL ---
    if (ch == 27) { // ESC
        app.screen = Screen::EXIT;
        return;
    }

    if (ch == ' ') {
        app.screen = Screen::PAUSE;
        app.screenJustEntered = true;
        return;
    }

    // --- DIRECTION SEULEMENT ---
    if (language == "fr") {
        switch (ch) {
        case 'z': case 'Z': game.nextDir = Direction::UP;    break;
        case 's': case 'S': game.nextDir = Direction::DOWN;  break;
        case 'q': case 'Q': game.nextDir = Direction::LEFT;  break;
        case 'd': case 'D': game.nextDir = Direction::RIGHT; break;
        }
    } else {
        switch (ch) {
        case 'w': case 'W': game.nextDir = Direction::UP;    break;
        case 's': case 'S': game.nextDir = Direction::DOWN;  break;
        case 'a': case 'A': game.nextDir = Direction::LEFT;  break;
        case 'd': case 'D': game.nextDir = Direction::RIGHT; break;
        }
    }
}

void handleMenuInput(AppState &app,
                     int ch)
{
    if (ch == ERR) return;

    if (ch == ' ') {
        app.screen = Screen::GAME;
        app.screenJustEntered = true;
    }
    else if (ch == 27) { // ESC
        app.screen = Screen::EXIT;
    }
}

void handlePauseInput(AppState &app,
                      int ch)
{
    if (ch == ERR) return;

    if (ch == ' '){
        app.screen = Screen::GAME;
        app.screenJustEntered = true;
    }
    else if (ch == 27) {
        app.screen = Screen::EXIT;
    }
}

void handleGameOverInput(AppState &app,
                         GameState &game,
                         int ch)
{
    if (ch == ERR) return;

    if (ch == ' ') {
        game = GameState();          // reset complet
        //foodPlacement(game.border, game.snake, game.food, display, game);
        app.screen = Screen::MENU;
        app.screenJustEntered = true;
    }
    else if (ch == 27) {
        app.screen = Screen::EXIT;
    }
}
