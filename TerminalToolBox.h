#ifndef TERMINALTOOLBOX_H
#define TERMINALTOOLBOX_H


#include <string>    // pour std::string


std::string terminalFinder();

int summonTerminal(int argc,
                   char* argv[]);

std::string getSystemLanguage(const std::string& userOverride = "");


#endif // TERMINALTOOLBOX_H
