#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#include "Display.h"
#include "Structures.hpp"


void sizeWarningScreen(std::string &language);

void badSizeScreen(std::string &language,
             Board &board);

void scorePlacement(Theme &theme, Board &board, int score);

// --- MENUS ---
void buildMenuUi(Theme &theme,
                 Board &board,
                 const std::string &language,
                 GameState game,
                 Display display);

void buildPauseUi(Theme& theme,
                  const Board& board,
                  const std::string& language);

void buildGameOverUi(Theme& theme,
                     const Board& board,
                     const std::string& language, GameState game);


void drawCenteredLines(Board &board,
                       const std::vector<std::string> &lines,
                       int startY,
                       int fg, int bg);
void drawCenteredColoredLine(Board &board,
                             const std::vector<ColoredText> &parts,
                             int y);

void drawCenteredScreen(Board &board,
                        const std::vector<CenteredColoredLine> &lines);

#endif // USERINTERFACE_H
