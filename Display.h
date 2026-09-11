#ifndef DISPLAY_H
#define DISPLAY_H


//#include <deque>
//#include <string>
#include <array>
#include <optional>

#include "GameState.hpp"
#include "Structures.hpp"

struct RGB {
    short r; // 0..1000
    short g;
    short b;

    bool operator<(const RGB& other) const {
        if (r != other.r) return r < other.r;
        if (g != other.g) return g < other.g;
        return b < other.b;
    }
};

struct Style {
    chtype ch;
    short  fg;
    short  bg;
    int    attr;

    // optionnel
    const RGB* fgRgb = nullptr;
    const RGB* bgRgb = nullptr;
};

struct SnakeSkin {
    Style head;
    Style body;
};

enum class UiStyle {
    SCORE,
    MENU_TITLE,
    MENU_TEXT,
    MENU_BUTTON
};

enum class SnakeSkinId {
    CLASSIC
};

enum class UiAnchor {
    Center,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

struct UiBlock {
    UiAnchor anchor;
    int offsetX = 0;
    int offsetY = 0;

    std::vector<CenteredColoredLine> lines;
};

class Theme {
public:
    Theme();

    // style par type (déjà existant)
    std::array<Style,  static_cast<size_t>(CellType::COUNT)> styling;

    // override ponctuel par coordonnée
    std::map<std::pair<int,int>, Style> cellOverrides;

    // 🎨 API THEME (logique → visuel)
    void set(CellType type, const Style& style);
    const Style& resolve(CellType type) const;



    // 🎯 Overrides ponctuels
    void setCellOverride(int x, int y, const Style& style)
    {
        cellOverrides[{x,y}] = style;
    }

    bool hasCellOverride(int x, int y) const
    {
        return cellOverrides.find({x,y}) != cellOverrides.end();
    }

    const Style& getCellOverride(int x, int y) const
    {
        return cellOverrides.at({x,y});
    }

    void clearOverrides()
    {
        cellOverrides.clear();
    }
    std::map<UiStyle, Style> uiStyles;

    void setUiStyle(UiStyle id, const Style& style) {
        uiStyles[id] = style;
    }

    const Style& getUiStyle(UiStyle id) const {
        static Style fallback { ' ', -1, -1, 0 };

        auto it = uiStyles.find(id);
        if (it == uiStyles.end())
            return fallback;

        return it->second;
    }

};

class Display {
public:
    void render(const Board& board, Segment origin, GameState game);
    Theme& getTheme();   // 👈 autorisé

private:
    Theme theme;   // 👈 LA solution
};

struct render {
    static short get(const Style &s);
    static short getIndexed(short fg, short bg);
    static short getRgb(short fgIndexed, const RGB* fgRgb,
                        short bgIndexed, const RGB* bgRgb);
};

struct StyleOverride {
    std::optional<chtype> ch;
    std::optional<short>  fg;
    std::optional<short>  bg;
    std::optional<int>    attr;
    const RGB* fgRgb = nullptr;
    const RGB* bgRgb = nullptr;
};


void ncurseInit();

bool colors();

class ColorRegistry {
public:
    static short get(const RGB& rgb)
    {
        static short next = 16; // éviter couleurs système
        static std::map<std::tuple<short,short,short>, short> map;

        auto key = std::make_tuple(rgb.r, rgb.g, rgb.b);
        auto it = map.find(key);
        if (it != map.end())
            return it->second;

        if (!can_change_color() || next >= COLORS)
            return COLOR_WHITE; // fallback safe

        init_color(next, rgb.r, rgb.g, rgb.b);
        map[key] = next;
        return next++;
    }
};

struct StyleLayer {
    void apply(Style& s, Direction dir);
};

struct HeadDirectionLayer {
    void apply(Style& s, Direction dir, int &timer);
};

/*void drawBoard(const Board &board,
               Segment boardStart,
               bool useColors);

void snakeRender(Segment head,
                 std::deque<Segment> &snake,
                 Board &board,
                 bool paused,
                 bool ateFood);

void foodRender(Segment food,
                Board &board,
                int fg,
                int bg);

void scoreRender(int &score,
                 bool &alive,
                 Board &board,
                 Segment border, int fg, int bg);

void drawCell(int x,
              int y,
              char ch,
              int color = 0);

void drawString(int x,
                int y,
                const std::string &text,
                int color);

int blinkColor(int c1,
               int c2,
               int period = 20);
int breathingColor(int period);
RenderColors breathingText(int period);*/

void applySnakeSkin(Theme& theme, SnakeSkinId skinId);

void overrideWALLCells(Theme& theme,
                       const Board& board,
                       const Style& wallStyle);

void applyUiTheme(Theme& theme);

Style callFX(
    const Style& base,
    const StyleOverride& a,
    const StyleOverride& b,
    int tick,
    int period
    );

#endif // DISPLAY_H
