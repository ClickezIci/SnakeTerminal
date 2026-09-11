#include <clocale>
#include <cstring>
//#include <string>
#include <ncursesw/ncurses.h>
//#include <chrono>

#include "Display.h"


void ncurseInit(){
    setlocale(LC_ALL, "");
    initscr();            // Démarre ncurses
    cbreak();             // lecture immédiate des touches
    noecho();             // N'affiche pas les touches tapées
    curs_set(0);          // Cache le curseur
    keypad(stdscr, TRUE);  // Interprète les touches spéciales
    nodelay(stdscr, TRUE); // getch() ne bloque pas
    clear();
}

bool colors(){
    if (has_colors()) {
        start_color();
        use_default_colors();

        /*init_pair(1, COLOR_BLACK, COLOR_BLUE); //couleur cadre
        init_pair(2, COLOR_WHITE, COLOR_RED); //couleur erreurs
        init_pair(3, COLOR_YELLOW, -1);        //couleur snakeHead
        init_pair(4, COLOR_GREEN, -1);         //couleur snakeBody
        init_pair(5, COLOR_RED, -1);           //couleur snakeFood
        init_pair(6, COLOR_WHITE, COLOR_BLACK);//couleur snakeCounter
        init_pair(7, COLOR_YELLOW, -1);
        if (!can_change_color())
            return false; // terminal trop nul, on abandonne proprement*/

        /*if (COLORS < 16 || !can_change_color())
            return false;

        constexpr int BREATH_BASE = 17;

        init_color(17,  1000, 1000, 0);
        init_color(18,  1000, 900,  0);
        init_color(19, 1000, 800,  0);
        init_color(20, 1000, 700,  0);
        init_color(21, 1000, 600,  0);
        init_color(22, 1000, 500,  0);
        init_color(23, 1000, 350,  0);
        init_color(24, 1000, 200,  0);

        init_pair(PAIR_WALL,       COLOR_BLACK, COLOR_BLUE);
        init_pair(PAIR_SNAKE_HEAD, -1, COLOR_YELLOW);
        init_pair(PAIR_SNAKE_BODY, -1,  COLOR_GREEN);
        init_pair(PAIR_FOOD,       -1,    COLOR_RED);
        init_pair(PAIR_SCORE,     COLOR_BLACK,  -1);

        init_pair(PAIR_TITLE_0, COLOR_WHITE, 17);
        init_pair(PAIR_TITLE_1, COLOR_WHITE, 18);
        init_pair(PAIR_TITLE_2, COLOR_WHITE, 19);
        init_pair(PAIR_TITLE_3, COLOR_WHITE, 20);
        init_pair(PAIR_TITLE_4, COLOR_WHITE, 21);
        init_pair(PAIR_TITLE_5, COLOR_WHITE, 22);
        init_pair(PAIR_TITLE_6, COLOR_WHITE, 23);
        init_pair(PAIR_TITLE_7, COLOR_WHITE, 24);

        int pair = PAIR_TITLE_0 + BREATH_BASE;*/

        return true;
    }else
        return false;
}

Theme::Theme() {
    // Initialisation par défaut du thème
    // (on mettra des vraies couleurs après)
    styling[static_cast<int>(CellType::EMPTY)]     = { ' ', -1, -1, 0 };
    styling[static_cast<int>(CellType::WALL)]      = { '#', -1, -1, A_DIM };
    styling[static_cast<int>(CellType::PAWN_HEAD)] = { ':', COLOR_YELLOW, -1, 0 };
    styling[static_cast<int>(CellType::PAWN_BODY)] = { 'O', COLOR_GREEN, -1, 0 };
    styling[static_cast<int>(CellType::ITEM)]      = { '*', COLOR_RED, -1, A_DIM };
}

Theme& Display::getTheme() {
    return theme;
}

//static const Style STYLES[] = {
    /* EMPTY     */ //{ ' ', -1, -1, 0 },
    /* WALL      */ //{ '#', -1, -1, A_BOLD },
    /* SNAKEHEAD */ //{ '@', -1, -1, A_BOLD },
    /* SNAKETAIL */ //{ 'o', -1, -1, 0 },
    /* FOOD      */ //{ '*', -1, -1, A_BOLD }
//};

void applyUiTheme(Theme& theme)
{
    theme.setUiStyle(UiStyle::SCORE,
                     {
                         ' ',                // caractère neutre (sera écrasé)
                         COLOR_WHITE,       // fg
                         COLOR_BLACK,                 // bg
                         A_BOLD              // attr
                     });

    theme.setUiStyle(UiStyle::MENU_TITLE,
                     { ' ', COLOR_YELLOW, -1, A_BOLD });

    theme.setUiStyle(UiStyle::MENU_TEXT,
                     { ' ', COLOR_WHITE, -1, 0 });

    theme.setUiStyle(UiStyle::MENU_BUTTON,
                     { ' ', COLOR_CYAN, -1, A_BOLD });
}


short render::get(const Style& s) {
    if (s.fgRgb || s.bgRgb)
        return getRgb(s.fg, s.fgRgb, s.bg, s.bgRgb);

    return getIndexed(s.fg, s.bg);
    /*static short nextColor = 16;   // 0–15 réservés
    static short nextPair  = 1;

    static std::map<RGB, short> rgbColors;
    static std::map<std::pair<short,short>, short> pairs;

    auto resolveColor = [&](short index, const RGB* rgb) -> short {
        if (rgb) {
            auto it = rgbColors.find(*rgb);
            if (it != rgbColors.end())
                return it->second;

            short id = nextColor++;
            init_color(id, rgb->r, rgb->g, rgb->b);
            rgbColors[*rgb] = id;
            return id;
        }
        return index;
    };

    //short fg = resolveColor(s.fg, s.fgRgb);
    //short bg = resolveColor(s.bg, s.bgRgb);

    short pair;

    if (s.fgRgb || s.bgRgb) {
        pair = render::getRgb(s.fgRgb, s.bgRgb);
    } else {
        pair = render::get(s.fg, s.bg);
    }


    auto key = std::make_pair(fg, bg);
    auto it = pairs.find(key);
    if (it != pairs.end())
        return it->second;

    short pairId = nextPair++;
    init_pair(pairId, fg, bg);
    pairs[key] = pairId;
    return pairId;*/
}

short render::getIndexed(short fg, short bg)
{
    static short nextPair = 1;
    static std::map<std::pair<short, short>, short> pairs;

    auto key = std::make_pair(fg, bg);
    auto it = pairs.find(key);
    if (it != pairs.end())
        return it->second;

    short id = nextPair++;
    init_pair(id, fg, bg);
    pairs[key] = id;
    return id;
}

short render::getRgb(short fgIndexed, const RGB* fgRgb,
                     short bgIndexed, const RGB* bgRgb
                     ) {
    static short nextColor = 16;   // 0–15 réservés
    static short nextPair  = 64;

    static std::map<RGB, short> rgbColors;
    static std::map<std::pair<short, short>, short> pairs;

    auto resolveRgb = [&](short indexed, const RGB* rgb) -> short {
        if (!rgb)
            return indexed;

        auto it = rgbColors.find(*rgb);
        if (it != rgbColors.end())
            return it->second;

        short id = nextColor++;
        init_color(id, rgb->r, rgb->g, rgb->b);
        rgbColors[*rgb] = id;
        return id;
    };

    short fg = resolveRgb(fgIndexed, fgRgb);
    short bg = resolveRgb(bgIndexed, bgRgb);

    auto key = std::make_pair(fg, bg);
    auto it = pairs.find(key);
    if (it != pairs.end())
        return it->second;

    short pairId = nextPair++;
    init_pair(pairId, fg, bg);
    pairs[key] = pairId;
    return pairId;
}

const Style& Theme::resolve(CellType type) const {
    return styling[static_cast<int>(type)];
}

void Theme::set(CellType type, const Style& style) {
    styling[static_cast<int>(type)] = style;
}

void drawCell(int x, int y, const Style& s) {
    short pair = render::get(s);
    attron(COLOR_PAIR(pair) | s.attr);
    mvaddch(y, x, s.ch);
    attroff(COLOR_PAIR(pair) | s.attr);
}

inline const SnakeSkin& getSnakeSkin(SnakeSkinId id)
{
    static const RGB SNAKE_BODY_GREEN = { 0, 400, 0 };
    static const RGB SNAKE_BODY2_GREEN = { 0, 350, 0 };
    static const RGB SNAKE_HEAD_YELLOW = { 400, 400, 0 };

    static const std::map<SnakeSkinId, SnakeSkin> skins = {
        {
            SnakeSkinId::CLASSIC,
            {
                // head
                {
                    ':',
                    COLOR_BLACK, -1,
                    0,
                    nullptr,         // fgRgb
                    &SNAKE_HEAD_YELLOW         // bgRgb
                },

                // body
                {
                    '0',
                    -1, -1,
                    0,
                    &SNAKE_BODY2_GREEN,
                    &SNAKE_BODY_GREEN
                }
            }
        }
    };

    return skins.at(id);
}

void HeadDirectionLayer::apply(Style& s, Direction dir,int &timer)
{
    float factor = 1.8;
    static int timerBuffer = timer;
    //static Direction oldDir = dir;
    //static bool old = false;

    //if(dir != oldDir)old = true;

    if(dir == Direction::UP || dir == Direction::DOWN){
        timer = timerBuffer*factor;
    }else timer = timerBuffer;

    switch (dir) {
    case Direction::UP:    s.ch = '.';
        //if(old)timer = timer*2;
        //old = false;
        break;
    case Direction::DOWN:  s.ch = '"';
        //if(old)timer = timer*2;
        break;
        //old = false;
    case Direction::LEFT:  s.ch = ':';
        //if(old)timer = timerBuffer;
        break;
        //old = false;
    case Direction::RIGHT: s.ch = ':';
        //if(old)timer = timerBuffer;
        break;
        //old = false;
    }
}

void Display::render(const Board &board, Segment origin, GameState game) {
    for (int y = 0; y < board.height; ++y) {
        for (int x = 0; x < board.width; ++x) {

            Style style = theme.resolve(board.getCell(x, y));

            // 🔥 priorité à l’override
            if (theme.hasCellOverride(x, y)) {
                style = theme.getCellOverride(x, y);
            }

            if (board.hasTextCell(x, y)) {
                TextCell t = board.getTextCell(x, y);
                style.ch = static_cast<chtype>(t.ch);
                // couleurs déjà dans la pair
                short pair = t.pair;
                attron(COLOR_PAIR(pair));
                mvaddch(origin.y + y, origin.x + x, style.ch);
                attroff(COLOR_PAIR(pair));
                continue;
            }

            Style resolved = style;

            if (resolved.fgRgb)
                resolved.fg = ColorRegistry::get(*resolved.fgRgb);

            if (resolved.bgRgb)
                resolved.bg = ColorRegistry::get(*resolved.bgRgb);


            drawCell(origin.x + x,
                     origin.y + y,
                     style);
        }
    }
    refresh();
}



void applySnakeSkin(Theme& theme, SnakeSkinId skinId)
{
    const SnakeSkin& skin = getSnakeSkin(skinId);

    theme.set(CellType::PAWN_HEAD, skin.head);
    theme.set(CellType::PAWN_BODY, skin.body);
}

void overrideWALLCells(Theme& theme,
                        const Board& board,
                        const Style& wallStyle)
{
    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            if (board.getCell(x, y) == CellType::WALL) {
                theme.setCellOverride(x, y, wallStyle);
            }
        }
    }
}


Style callFX(
    const Style& base,
    const StyleOverride& a,
    const StyleOverride& b,
    int tick,
    int period
    ) {
    Style s = base;

    const bool on = ((tick / period) % 2) == 0;
    const StyleOverride& o = on ? a : b;

    if (o.ch)   s.ch   = *o.ch;
    if (o.fg)   s.fg   = *o.fg;
    if (o.bg)   s.bg   = *o.bg;
    if (o.attr) s.attr = *o.attr;

    if (o.fgRgb) {
        s.fgRgb = o.fgRgb;
        s.fg = -1;
    }

    if (o.bgRgb) {
        s.bgRgb = o.bgRgb;
        s.bg = -1;
    }

    return s;
}
/*void snakeRender(Segment head,
                 std::deque<Segment> &snake,
                 Board &board,
                 bool paused,
                 bool ateFood){

    //bool eat = board.isFood(head.x, head.y);

    if (!paused) {
        // --- Mise à jour logique ---
        snake.push_front(head);

        if (!ateFood) {
            snake.pop_back();
        }
    }

    // --- Reconstruction VISUELLE COMPLÈTE ---
    // 1) Nettoyer ancien serpent
    board.clearGameplayCells();

    // 2) Redessiner depuis la source de vérité
    for (size_t i = 0; i < snake.size(); ++i) {
        const Segment &seg = snake[i];

        if (i == 0)
            board.setCell(seg.x, seg.y, CellType::SNAKEHEAD);
        else
            board.setCell(seg.x, seg.y, CellType::SNAKETAIL);
    }
}


void foodRender(Segment food,
                Board &board,
                int fg,
                int bg){

    int period = 300;
    int color = blinkColor(period, COLOR_RED, COLOR_YELLOW);


    board.setTextCell(food.x,
                      food.y,
                      '*',
                      fg,
                      bg);
}

void scoreRender(int &score,
                 bool &alive,
                 Board &board,
                 Segment border,
                 int fg,
                 int bg){
    Segment scorePos {border.x / 2 - 1, border.y - 1};

    std::string scoreStr = std::to_string(score);

    for (size_t i = 0; i < scoreStr.size(); ++i) {
        board.setTextCell(scorePos.x + i,
                          scorePos.y,
                          scoreStr[i],
                          fg,
                          bg);
    }
}*/

/*void drawCell(int x, int y, char ch, int color) {
    if (x < 0 || y < 0 || x >= COLS || y >= LINES)
        return;

    if (color > 0) attron(COLOR_PAIR(color));
    mvaddch(y, x, ch);   // ncurses reste ici
    if (color > 0) attroff(COLOR_PAIR(color));
}*/

/*void drawString(int x, int y, const std::string &text, int color = 0) {
    for (size_t i = 0; i < text.size(); ++i) {
        drawCell(x + i, y, text[i], color);
    }
}

int blinkColor(int c1,
               int c2,
               int period)
{
    using namespace std::chrono;

    static auto start = steady_clock::now();

    auto now = steady_clock::now();
    auto elapsed = duration_cast<milliseconds>(now - start).count();

    bool toggle = (elapsed / period) % 2;
    return toggle ? c1 : c2;
}

int breathingIndex(int period)
{
    using namespace std::chrono;

    static auto start = steady_clock::now();

    auto now = steady_clock::now();
    auto elapsed =
        duration_cast<milliseconds>(now - start).count();

    constexpr int STEPS = 8; // PAIR_TITLE_0 → PAIR_TITLE_7

    return (elapsed * STEPS / period) % STEPS;
}

int breathingPair(int period) {
    int index = breathingIndex(period); // 0..7
    return PAIR_TITLE_0 + index;
}

int breathingColor(int period)
{
    using namespace std::chrono;

    static auto start = steady_clock::now();

    auto now = steady_clock::now();
    auto elapsed =
        duration_cast<milliseconds>(now - start).count();

    const int steps = BREATH_COLORS.size();

    // position dans le cycle
    int index = (elapsed * steps / period) % steps;

    return BREATH_COLORS[index];
}*/

/*RenderColors breathingText(int period) {
    return { breathingColor(period), -1 };
}*/

/*int breathingColor2(int period)
{
    using namespace std::chrono;

    static auto start = steady_clock::now();

    auto now = steady_clock::now();
    auto elapsed =
        duration_cast<milliseconds>(now - start).count();

    const int steps = BREATH_COLORS.size();

    // position dans le cycle
    int index = (elapsed * steps / period) % steps;

    return BREATH_COLORS[index];
}*/
