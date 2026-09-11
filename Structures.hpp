#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP


#include <map>
#include <ncursesw/ncurses.h>
#include <string>
#include <variant>
#include <vector>

/*enum ColorPair {
    PAIR_WALL = 1,
    PAIR_SNAKE_HEAD,
    PAIR_SNAKE_BODY,
    PAIR_FOOD,
    PAIR_SCORE,

    PAIR_TITLE_0,
    PAIR_TITLE_1,
    PAIR_TITLE_2,
    PAIR_TITLE_3,
    PAIR_TITLE_4,
    PAIR_TITLE_5,
    PAIR_TITLE_6,
    PAIR_TITLE_7,
};*/

static const std::vector<int> BREATH_COLORS = {
    17, 18, 19, 20, 21, 22, 23, 24,
    23, 24, 23,
    22, 23, 22,
    21, 20, 19, 18, 17
};

struct ColoredText {
    std::string text;
    int fg;
    int bg;
};

struct CenteredLine {
    std::string text;
    int color;
};

struct CenteredColoredLine {
    std::vector<ColoredText> parts;
    CenteredColoredLine(std::initializer_list<ColoredText> p)
        : parts(p) {}
};

struct CenteredScreenLine {
    std::variant<CenteredLine, CenteredColoredLine> content;
};

struct Segment {
    int x;
    int y;
    bool operator==(const Segment &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Segment &other) const {
        return !(*this == other);
    }
};

struct TextCell {
    char ch;
    int pair = 0;   // 0 = pas de couleur / défaut
};

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} UserControl;


enum class CellType {
    EMPTY,
    WALL,
    PAWN_HEAD,
    PAWN_BODY,
    ITEM,
    COUNT
};

struct Cell {
    CellType type = CellType::EMPTY;
};

struct Board {
private:
    std::vector<std::vector<CellType>> cells;
    std::map<std::pair<int,int>, TextCell> textCells;

public:
    int width;
    int height;

    Board(int w, int h);

    int getWidth() const;
    int getHeight() const;

    bool isEmpty(int x, int y) const;
    bool isItem(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isPawnBody(int x, int y) const;

    void setCell(int x, int y, CellType type);
    CellType getCell(int x, int y) const;
    void setTextCell(int x, int y, char c, int fg, int bg);
    TextCell getTextCell(int x, int y) const;
    bool hasTextCell(int x, int y) const;
    void clearTextCells();
    void clearGameplayCells();
    void clearAllCells();

    void refresh(); // si tu l’utilises dans le constructeur
};

//void buildBoard(Board &board);

constexpr int MAX_COLORS = 16;

// bg = -1 autorisé → mappé proprement
constexpr int bgIndex(int bg) {
    return bg < 0 ? 0 : bg + 1;
}

constexpr int makePair(int fg, int bg) {
    return 1 + fg * (MAX_COLORS + 1) + bgIndex(bg);
}


#endif // STRUCTURES_H
