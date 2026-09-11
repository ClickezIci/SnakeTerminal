#include <unistd.h>
#include <fcntl.h>

//#include "AppState.hpp"
#include "Structures.hpp"
#include "UserInterface.h"
#include "GamePlay.h"
#include "Display.h"
#include "GameState.hpp"
#include "input.h"
#include "saveSpace.hpp"

void buildSnakeLevel(Board& board,
                     Theme& theme) {

    // géométrie
    for (int x = 0; x < board.width; ++x) {
        board.setCell(x, 0, CellType::WALL);
        board.setCell(x, board.height - 1, CellType::WALL);
    }
    for (int y = 0; y < board.height; ++y) {
        board.setCell(0, y, CellType::WALL);
        board.setCell(board.width - 1, y, CellType::WALL);
    }

}

void applySnakeTheme(Theme& theme)
{
    theme.set(CellType::EMPTY,      { ' ', -1,  -1,  0 });
    theme.set(CellType::WALL,      { '#', COLOR_BLACK,  COLOR_BLUE,  A_DIM });
    theme.set(CellType::PAWN_HEAD, { '@', COLOR_YELLOW, -1,          0     });
    theme.set(CellType::PAWN_BODY, { 'O', COLOR_GREEN,  -1,          0     });
    theme.set(CellType::ITEM,      { '*', COLOR_RED,    -1,          0     });
    applyUiTheme(theme);
}

/*static constexpr off_t SAVE_OFFSET = 0x2c340;   // offset réel de .save
static constexpr size_t SAVE_SIZE = 131072;

inline void load_save_from_self()
{
    int fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) return;

    pread(fd, g_save_area, SAVE_SIZE, SAVE_OFFSET);
    close(fd);
}

inline void flush_save_to_self()
{
    int fd = open("/proc/self/exe", O_RDWR);
    if (fd < 0) return;

    pwrite(fd, g_save_area, SAVE_SIZE, SAVE_OFFSET);
    close(fd);
}*/


void snakeTerminal(std::string language){
    sizeWarningScreen(language);

    constexpr uint32_t SAVE_INDEX = 0;

    ncurseInit();

    bool useColors = colors();
    int fg = COLOR_WHITE;
    int bg = -1; // fond terminal par défaut
    const Segment border {59, 19};
    Board board(border.x, border.y);
    Segment boardStart {(COLS - border.x) / 2, (LINES - border.y) / 2};
    Display display;
    AppState app;
    GameState game;

    if (COLS < border.x + 1 || LINES < border.y + 1) {
        badSizeScreen(language, board);

        display.render(board, boardStart, game);
        nodelay(stdscr, FALSE);
        getch();
        endwin();
        return;   // 🔒 arrêt immédiat
    }

    buildSnakeLevel(board, display.getTheme());
    applySnakeTheme(display.getTheme());

    game.score = 0;          // 🔥 ICI


    //foodPlacement(game.border, game.snake, game.food);

    int timer = 200;

    //save_load();


    //load_save_from_self();
    //auto& score = save_at<uint64_t>(0);

    while (app.running) {

        int ch = getch();

        switch (app.screen) {

        // ---------------- MENU ----------------
        case Screen::MENU:
            display.getTheme().clearOverrides();   // 🔥 OBLIGATOIRE
            board.clearGameplayCells();
            if (app.screenJustEntered) {

                //board.clearTextCells();   // init une fois

                game.alive = true;
                game.ateFood = false;


                /*// read
                uint8_t v = g_save_area[SAVE_INDEX];

                mvprintw(0, 0, "save[%u] = %u", SAVE_INDEX, v);*/



                //score += 42;

                app.screenJustEntered = false;

            }

            //board.clearTextCells();       // ← IMPORTANT
            buildMenuUi(display.getTheme(),
                        board,
                        language,
                        game,
                        display);  // ← CHAQUE FRAME

            //mvprintw(0, 0, "Score: %llu",
            //         (unsigned long long)score);

            display.render(board, boardStart, game);
            handleMenuInput(app, ch);
            break;


        // ---------------- GAME ----------------
        case Screen::GAME:
        {
            board.clearTextCells();
            //scorePlacement(board, game.score);
            game.resetTickFlags();
            nodelay(stdscr, TRUE);

            if (app.screenJustEntered) {
                board.clearAllCells();
                applySnakeSkin(display.getTheme(), SnakeSkinId::CLASSIC);
                //buildBoard(board);              // murs uniquement
                game.snake.clear();
                initSnake(game.snake, game.head, game.border);
                foodPlacement(game.border, game.snake, game.food);
                buildSnakeLevel(board, display.getTheme());

                app.screenJustEntered = false;
            }

            // 1️⃣ INPUT
            handleGameInput(language, app, game, ch);

            // 2️⃣ UPDATE (logique pure)
            if ((game.dir == Direction::UP    && game.nextDir != Direction::DOWN) ||
                (game.dir == Direction::DOWN  && game.nextDir != Direction::UP)   ||
                (game.dir == Direction::LEFT  && game.nextDir != Direction::RIGHT)||
                (game.dir == Direction::RIGHT && game.nextDir != Direction::LEFT))
            {
                game.dir = game.nextDir;
            }

            switch (game.dir) {
            case Direction::UP:    game.head.y--; break;
            case Direction::DOWN:  game.head.y++; break;
            case Direction::LEFT:  game.head.x--; break;
            case Direction::RIGHT: game.head.x++; break;
            }

            CellType hit = collision(board, game.head);

            if (hit == CellType::WALL || hit == CellType::PAWN_BODY) {
                app.screen = Screen::GAME_OVER;
                app.screenJustEntered = true;
                break;
            }

            if (hit == CellType::ITEM) {
                game.score++;
                game.ateFood = true;
                foodPlacement(game.border, game.snake, game.food);
            }

            /*if (game.head == game.food) {

                foodPlacement(game.border, game.snake, game.food);
            }*/

            game.snake.push_front(game.head);
            if (!game.ateFood)
                game.snake.pop_back();

            // 3️⃣ PROJECTION VISUELLE
            board.clearGameplayCells();
            snakePlacement(game.snake,
                           board);
            /*foodPlacement(game.border,
                          game.snake,
                          game.food);*/

            display.getTheme().clearOverrides();

            const Segment& head = game.snake.front();

            Style headStyle = display.getTheme().resolve(CellType::PAWN_HEAD);

            HeadDirectionLayer dirLayer;
            dirLayer.apply(headStyle, game.dir, timer);

            Style food = display.getTheme().resolve(CellType::ITEM);

            StyleOverride on {
                .ch = '*',
                .fg = COLOR_RED
            };

            StyleOverride off {
                .ch = '*',
                .fg = COLOR_YELLOW
            };

            Style fx = callFX(food, on, off, game.tick, 1);
            display.getTheme().setCellOverride(game.food.x, game.food.y, fx);

            display.getTheme().setCellOverride(head.x, head.y, headStyle);

            scorePlacement(display.getTheme(), board, game.score);

            board.setCell(game.food.x,
                          game.food.y,
                          CellType::ITEM);

            // 4️⃣ RENDER
            display.render(board, boardStart, game);

            break;
        }

        // ---------------- PAUSE ----------------
        case Screen::PAUSE:{
            if (app.screenJustEntered) {
                display.getTheme().clearOverrides();

                board.clearGameplayCells();
                board.clearTextCells();   // UNE FOIS
                app.screenJustEntered = false;
            }

            buildPauseUi(display.getTheme(),
                         board,
                         language);

            display.render(board, boardStart, game);
            handlePauseInput(app, ch);

            //usleep(50 * 1000);
            break;
        }


        // ---------------- GAME OVER ----------------
        case Screen::GAME_OVER:{
            display.getTheme().clearOverrides();

            if (app.screenJustEntered) {
                board.clearTextCells();
                board.clearGameplayCells();

                // write (persistant)
                //g_save_area[SAVE_INDEX]++;

                app.screenJustEntered = false;
            }

            buildGameOverUi(display.getTheme(),
                            board,
                            language,
                            game);

            display.render(board,boardStart, game);
            handleGameOverInput(app, game, ch);

            break;
        }

        case Screen::EXIT:
            app.running = false;
            break;
        }

        //uint64_t score = save_at<uint64_t>(0);
        //mvprintw(0, 0, "Score: %llu", (unsigned long long)score);


        usleep(timer * 1000);
        napms(16); // 60 FPS GLOBAL

    }

    //save_flush();

    getch();
    endwin();

}
