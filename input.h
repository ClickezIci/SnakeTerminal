#ifndef INPUT_H
#define INPUT_H

#include <string>

#include "AppState.hpp"
#include "GameState.hpp"

void controls(std::string language,
              Segment &head,
              Board &board,
              bool &paused,
              bool &alive,
              Segment boardStart,
              bool useColors,
              Segment food);


void handleGameInput(const std::string &language,
                     AppState &app,
                     GameState &game, int ch);

// --- INPUT MENUS ---
void handleMenuInput(AppState &app,
                     int ch);
void handlePauseInput(AppState &app,
                      int ch);
void handleGameOverInput(AppState &app,
                         GameState &game,
                         int ch);


#endif // INPUT_H
