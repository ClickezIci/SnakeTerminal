#include "UserInterface.h"
#include "Display.h"
#include "Structures.hpp"

#include <iomanip>
#include <iostream>
#include <cstring>


void scorePlacement(Theme &theme, Board &board, int score)
{
    // format 000 → 999
    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << score;
    std::string text = oss.str();

    int y = board.height - 1;
    int x = (board.width - text.size()) / 2;

    const Style& base = theme.getUiStyle(UiStyle::SCORE);

    for (size_t i = 0; i < text.size(); ++i) {
        Style s = base;
        s.ch = static_cast<chtype>(text[i]);

        theme.setCellOverride(x + i, y, s);
    }
}

/*void drawCenteredLines(Board &board,
                       const std::vector<std::string> &lines,
                       int startY,
                       int fg, int bg)
{
    for (size_t l = 0; l < lines.size(); ++l) {
        const std::string &text = lines[l];
        int x = (board.getWidth() - text.size()) / 2;
        int y = startY + static_cast<int>(l);

        for (size_t i = 0; i < text.size(); ++i)
            board.setTextCell(x + i, y, text[i], fg, bg);
    }
}

void drawCenteredColoredLine(Board &board,
                             const std::vector<ColoredText> &parts,
                             int y)
{
    int totalWidth = 0;
    for (const auto &p : parts)
        totalWidth += p.text.size();

    int x = (board.getWidth() - totalWidth) / 2;

    for (const auto &p : parts) {
        for (size_t i = 0; i < p.text.size(); ++i)
            board.setTextCell(x++, y, p.text[i], p.fg, p.bg);
    }
}

void drawCenteredScreen(Board &board,
                        const std::vector<CenteredColoredLine> &lines)
{
    const int totalLines = static_cast<int>(lines.size());
    const int startY = (board.getHeight() - totalLines) / 2;

    int y = startY;

    for (const auto &line : lines) {

        // 1) largeur totale de la ligne
        int totalWidth = 0;
        for (const auto &part : line.parts)
            totalWidth += static_cast<int>(part.text.size());

        // 2) centrage horizontal
        int x = (board.getWidth() - totalWidth) / 2;

        // 3) rendu
        for (const auto &part : line.parts) {
            for (char c : part.text) {
                board.setTextCell(x, y, c, part.fg, part.bg);
                ++x;
            }
        }

        ++y;
    }
}*/

void sizeWarningScreen(std::string &language){
    if (language == "fr"){
        std::cout << "==============================\n"
                  << "SnakeTerminal\n"
                  << "==============================\n\n"
                  << "S'il vous plaît,\n"
                  << "redimensionner votre terminal maintenant.\n"
                  << "Taille recommandee : au moins 60x20\n\n"
                  << "ATTENTION ! :\n"
                  << "Une fois le jeu lance, NE REDIMENSIONNEZ PLUS la fenetre.\n\n"
                  << "Appuyez sur ENTREE pour continuer...";
        std::cin.get();
    }else {
        std::cout << "==============================\n"
                  << "SnakeTerminal\n"
                  << "==============================\n\n"
                  << "Please,\n"
                  << "resize your terminal now.\n"
                  << "Recommended size : at least 60x20\n\n"
                  << "WARNING ! :\n"
                  << "Once the game is launched, DO NOT RESIZE the window.\n\n"
                  << "Press ENTER to continue...";
        std::cin.get();
    };
}

void badSizeScreen(std::string &language, Board &board) {

    /*const std::string prefix =
        (language == "fr")
            ? "Taille actuelle du terminal : "
            : "Terminal actual size: ";

    const std::string size =
        std::to_string(COLS) + " x " + std::to_string(LINES);

    const std::string info =
        (language == "fr")
            ? "Appuyez sur une touche pour continuer"
            : "Press any key to continue";

    drawCenteredScreen(board, std::vector<CenteredColoredLine>{
                                  {
                                      {   // ligne 1
                                          ColoredText{ prefix, COLOR_WHITE, -1 },
                                          ColoredText{ size,   COLOR_YELLOW, -1 }
                                      }
                                  },
                                  {
                                      {}  // ligne vide
                                  },
                                  {
                                      {   // ligne info
                                          ColoredText{ info, COLOR_WHITE, -1 }
                                      }
                                  }
                              });*/
}

void buildMenuUi(Theme& theme,
                 Board& board,
                 const std::string& language,
                 GameState game,
                 Display display)
{
    /*int period = 3000;
    //render titleStyle = breathingText(period);

    std::vector<CenteredColoredLine> screen;


    // ===== TITRE =====
    const std::vector<std::string> title = {
        "  _____ _   _    _    _  __ _____ ",
        " / ____| \\ | |  / \\  | |/ /| ____|",
        "| (___ |  \\| | / _ \\ | ' / |  _|  ",
        " \\___ \\| . ` |/ ___ \\|  <  | |___ ",
        " ____) | |\\  /_/   \\_\\_|\\_\\|_____|",
        "|_____/|_| \\_|                    ",
        "",
        " _____ _____ ____  __  __ ___ _   _    _    _     ",
        "|_   _| ____|  _ \\|  \\/  |_ _| \\ | |  / \\  | |    ",
        "  | | |  _| | |_) | |\\/| || ||  \\| | / _ \\ | |    ",
        "  | | | |___|  _ <| |  | || || |\\  |/ ___ \\| |___ ",
        "  |_| |_____|_| \\_\\_|  |_|___|_| \\_/_/   \\_\\_____|"
    };*/

    /*for (const auto &line : title) {
        screen.push_back(
            CenteredColoredLine{
                {
                    ColoredText{ line, -1, titleStyle.fg }
                }
            }
            );
    }*/

    // ===== CONTROLS =====
    /*screen.push_back({}); // ligne vide

    if (language == "fr") {
        screen.push_back({ { ColoredText{ "Appuyez sur ESPACE pour commencer", COLOR_WHITE, -1 } } });
        screen.push_back({ { ColoredText{ "Appuyez sur ECHAP pour quitter",  COLOR_WHITE, -1 } } });
    } else {
        screen.push_back({ { ColoredText{ "Press SPACE to start", COLOR_WHITE, -1 } } });
        screen.push_back({ { ColoredText{ "Press ESCAPE to quit", COLOR_WHITE, -1 } } });
    }

    //std::cerr << frame << "\n";

    drawCenteredScreen(board, screen);*/

    int y = 1;

    auto draw = [&](int x, int y, const std::string& s, const Style& base)
    {
        for (size_t i = 0; i < s.size(); ++i) {
            Style st = base;
            st.ch = static_cast<chtype>(s[i]);
            theme.setCellOverride(x + i, y, st);
        }
    };

    const Style& title = theme.getUiStyle(UiStyle::MENU_TITLE);
    const Style& text  = theme.getUiStyle(UiStyle::MENU_TEXT);

    Style titleHot = title;
    titleHot.fg = COLOR_RED;
    titleHot.attr |= 0;

    StyleOverride on {
        .fg = COLOR_RED
    };

    StyleOverride off {
        .fg = COLOR_YELLOW
    };

    titleHot = callFX(title, on, off, game.tick, 1);



    Style textHot = title;
    textHot.fg = COLOR_WHITE;
    textHot.bg = -1;
    textHot.attr |= A_DIM;

    std::vector<std::string> titleLine =
        std::vector<std::string>{
                 "  _____ _   _    _    _  __ _____ ",
                 " / ____| \\ | |  / \\  | |/ /| ____|",
                 "| (___ |  \\| | / _ \\ | ' / |  _|  ",
                 " \\___ \\| . ` |/ ___ \\|  <  | |___ ",
                 " ____) | |\\  /_/   \\_\\_|\\_\\|_____|",
                 "|_____/|_| \\_|                    ",
                 "",
                 " _____ _____ ____  __  __ ___ _   _    _    _     ",
                 "|_   _| ____|  _ \\|  \\/  |_ _| \\ | |  / \\  | |    ",
                 "  | | |  _| | |_) | |\\/| || ||  \\| | / _ \\ | |    ",
                 "  | | | |___|  _ <| |  | || || |\\  |/ ___ \\| |___ ",
                 "  |_| |_____|_| \\_\\_|  |_|___|_| \\_/_/   \\_\\_____|"
        };

    for (size_t i = 0; i < titleLine.size(); ++i) {
        const auto& line = titleLine[i];
        int x = (board.width - static_cast<int>(line.size())) / 2;
        draw(x, y + static_cast<int>(i), line, titleHot);
    }
    y = board.height / 2;

    std::vector<std::string> lines =
        (language == "fr")
            ? std::vector<std::string>{
                  "APPUYEZ SUR ESPACE",
                  "POUR COMMENCER"
              }
            : std::vector<std::string>{
                  "PRESS SPACE TO START"
              };

    for (size_t i = 0; i < lines.size(); ++i) {
        const auto& line = lines[i];
        int x = (board.width - line.size()) / 2;
        draw(x, y + i+5, line, textHot);
    }

}


void buildPauseUi(Theme& theme,
                  const Board& board,
                  const std::string& language)
{
    const std::vector<std::string> lines =
        (language == "fr")
            ? std::vector<std::string>{
                  "== PAUSE ==",
                  "",
                  "ESPACE : reprendre",
                  "ECHAP  : quitter"
              }
            : std::vector<std::string>{
                  "== PAUSE ==",
                  "",
                  "SPACE : resume",
                  "ESC   : quit"
              };

    const int w = board.getWidth();
    const int h = board.getHeight();

    const int startY = h / 2 - lines.size() / 2;

    Style text = theme.getUiStyle(UiStyle::MENU_TEXT);
    Style title = theme.getUiStyle(UiStyle::MENU_TITLE);

    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];
        const int startX = w / 2 - line.size() / 2;

        for (size_t j = 0; j < line.size(); ++j) {
            Style s = (i == 0 ? title : text);
            s.ch = line[j];

            theme.setCellOverride(startX + j,
                                  startY + i,
                                  s);
        }
    }
}


void buildGameOverUi(Theme& theme,
                     const Board& board,
                     const std::string& language,
                     GameState game
                     )
{
    //RenderColors colors { COLOR_WHITE, -1 };

    /*std::vector<CenteredColoredLine> screen;

    int period = 3000;
    // ===== TITRE =====
    //int titleColor = breathingColor(period);
    if (language == "fr") {
        screen.push_back(
            CenteredColoredLine{
                {
                    ColoredText{ "FIN DE PARTIE", COLOR_WHITE, -1}
                }
            }
            );
    } else
    {
        screen.push_back(
            CenteredColoredLine{
                {
                    ColoredText{ "GAME OVER", COLOR_WHITE, -1 }
                }
            }
            );
    }

    // ligne vide
    screen.push_back({});

    // ===== SCORE =====
    screen.push_back({
                      { { "Score: ", -1, COLOR_BLACK },
                       { std::to_string(score), COLOR_YELLOW, 9 } }
    });

    // ligne vide
    screen.push_back({});

    // ===== CONTROLS =====
    if (language == "fr") {
        screen.push_back({
            { ColoredText{ "Appuyez sur ESPACE pour rejouer", COLOR_WHITE, -1 } }
        });
        screen.push_back({
            { ColoredText{ "Appuyez sur ECHAP pour quitter", COLOR_WHITE, -1 } }
        });
    } else {
        screen.push_back({
            { ColoredText{ "Press SPACE to retry", COLOR_WHITE, -1 } }
        });
        screen.push_back({
            { ColoredText{ "Press ESCAPE to quit", COLOR_WHITE, -1 } }
        });
    }

    drawCenteredScreen(board, screen);*/

    const std::vector<std::string> lines =
        (language == "fr")
            ? std::vector<std::string>{
                  "== FIN DE PARTIE ==",
                  "",
                  "Score : " + std::to_string(game.score),
                  "",
                  "ESPACE : continuer",
                  "ECHAP  : quitter"
              }
            : std::vector<std::string>{
                  "== GAME OVER ==",
                  "",
                  "Score : " + std::to_string(game.score),
                  "",
                  "SPACE : continue",
                  "ESC   : quit"
              };

    const int w = board.getWidth();
    const int h = board.getHeight();
    const int startY = h / 2 - static_cast<int>(lines.size()) / 2;

    Style text  = theme.getUiStyle(UiStyle::MENU_TEXT);
    Style title = theme.getUiStyle(UiStyle::MENU_TITLE);

    // Style spécifique pour la valeur du score
    Style scoreStyle = text;
    scoreStyle.fg = COLOR_YELLOW;
    scoreStyle.bg = COLOR_RED;
    scoreStyle.attr |= A_BOLD;

    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];
        const int startX = w / 2 - static_cast<int>(line.size()) / 2;

        // Détection de la ligne score
        const bool isScoreLine = (line.rfind("Score :", 0) == 0);
        const size_t scoreValueStart = isScoreLine ? std::string("Score : ").size() : 0;

        for (size_t j = 0; j < line.size(); ++j) {
            Style s;

            if (i == 0) {
                s = title;                  // titre
            }
            else if (isScoreLine && j >= scoreValueStart) {
                s = scoreStyle;             // valeur numérique
            }
            else {
                s = text;                   // texte normal
            }

            s.ch = line[j];

            theme.setCellOverride(startX + j,
                                  startY + i,
                                  s);
        }
        Style frame = theme.resolve(CellType::WALL);
        frame.bg = COLOR_RED;
        frame.attr |= A_BLINK;

        overrideWALLCells(theme, board, frame);
    }
}
