#include <cstdlib>

#include "GamePlay.h"
#include "GameState.hpp"
#include "Display.h"


void initSnake(std::deque<Segment>& snake,
               Segment& head,
               Segment border)
{
    snake.clear();

    head = { border.x / 2, border.y / 2 };

    snake.push_back(head);
    snake.push_back({ head.x - 1, head.y });
    snake.push_back({ head.x - 2, head.y });
}


void snakePlacement(const std::deque<Segment>& snake,
                    Board& board)
{
    for (size_t i = 0; i < snake.size(); ++i) {
        const Segment& seg = snake[i];

        board.setCell(
            seg.x,
            seg.y,
            (i == 0) ? CellType::PAWN_HEAD
                     : CellType::PAWN_BODY
            );
    }
}

void foodPlacement(const Segment &border,
                   const std::deque<Segment> &snake,
                   Segment &food){


    while (true) {
        food.x = 1 + rand() % (border.x - 2);
        food.y = 1 + rand() % (border.y - 2);

        bool onSnake = false;
        for (const auto &s : snake) {
            if (s.x == food.x && s.y == food.y) {
                onSnake = true;
                break;
            }
        }

        if (!onSnake)
            return;
    }
}

CellType collision(const Board& board,
                   Segment pos)
{
    if (board.isWall(pos.x, pos.y))
        return CellType::WALL;

    if (board.isPawnBody(pos.x, pos.y))
        return CellType::PAWN_BODY;

    if (board.isItem(pos.x, pos.y))
        return CellType::ITEM;

    return CellType::EMPTY;
}

