#include <map>
#include <utility> // pour std::pair

#include "Structures.hpp"


// Constructeur
Board::Board(int w, int h)
    : width(w),
    height(h),
    cells(h, std::vector<CellType>(w, CellType::EMPTY)) {
    // Remplir les murs automatiquement sur les bords
    /*for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                cells[y][x] = CellType::WALL;
            }
        }
    }*/
    /*start_color();
    use_default_colors();

    int maxPairs = std::min(256, COLOR_PAIRS);

    int idx = 1;
    for (int fg = 0; fg < 16 && idx < maxPairs; ++fg) {
        for (int bg = 0; bg < 16 && idx < maxPairs; ++bg) {
            init_pair(idx, fg, bg);
            ++idx;
        }
    }*/
}


void Board::setTextCell(int x, int y, char c, int fg, int bg) {
    textCells[{x, y}] = {
        c,
        makePair(fg, bg)
    };
}

TextCell Board::getTextCell(int x, int y) const {
    auto it = textCells.find({x, y});
    if (it != textCells.end())
        return it->second;

    return {'\0', 0};
}

bool Board::hasTextCell(int x, int y) const {
    return textCells.find({x, y}) != textCells.end();
}

void Board::clearTextCells() {

    textCells.clear();
}

void Board::clearAllCells() {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            cells[y][x] = CellType::EMPTY;
}


void Board::clearGameplayCells() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (cells[y][x]) {
            case CellType::PAWN_HEAD:
            case CellType::PAWN_BODY:
            case CellType::ITEM:
                cells[y][x] = CellType::EMPTY;
                break;
            default:
                break;
            }
        }
    }
}

int Board::getWidth() const {
    return width;
}
int Board::getHeight() const {
    return height;
}

// Vérifie si une case est libre
bool Board::isEmpty(int x, int y) const {
    return cells[y][x] == CellType::EMPTY;
}

bool Board::isItem(int x, int y) const {
    return cells[y][x] == CellType::ITEM;
}

bool Board::isWall(int x, int y) const {
    return cells[y][x] == CellType::WALL;
}

bool Board::isPawnBody(int x, int y) const {
    return cells[y][x] == CellType::PAWN_BODY;
}

// Modifier une case
void Board::setCell(int x, int y, CellType type) {
    cells[y][x] = type;
}

// Lire une case
CellType Board::getCell(int x, int y) const {
    return cells[y][x];
}

/*void buildBoard(Board &board)
{
    int w = board.width;
    int h = board.height;

    // Haut + bas
    for (int x = 0; x < w; ++x) {
        board.setCell(x, 0, CellType::WALL);
        board.setCell(x, h - 1, CellType::WALL);
    }

    // Gauche + droite
    for (int y = 0; y < h; ++y) {
        board.setCell(0, y, CellType::WALL);
        board.setCell(w - 1, y, CellType::WALL);
    }
}*/
