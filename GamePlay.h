#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include <deque>

//#include "Display.h"
//#include "GameState.hpp"
#include "Structures.hpp"

void initSnake(std::deque<Segment>& snake,
               Segment& head,
               Segment border);

void snakePlacement(const std::deque<Segment>& snake,
                    Board& board);

void foodPlacement(const Segment &border,
                   const std::deque<Segment> &snake,
                   Segment &food);

CellType collision(const Board& board,
                   Segment pos);

#endif // GAMEPLAY_H
