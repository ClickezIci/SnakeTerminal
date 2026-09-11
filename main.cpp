#include "TerminalToolBox.h"
#include "SnakeTerminal.h"

int main(int argc, char* argv[])
{

    std::string language = /*"en";//*/getSystemLanguage();
    summonTerminal(argc, argv);

    snakeTerminal(language);

    return 0;

}

//Par ClickezIci <3
