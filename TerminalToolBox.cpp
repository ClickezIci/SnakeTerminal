#include <cstdio>    // pour FILE*, fopen, fgets, pclose
#include <array>
#include <memory>
#include <algorithm>
#include <unistd.h>
#include <cstring>

#include "TerminalToolBox.h"

std::string terminalFinder() {
    // Essayer GNOME
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
        popen("gsettings get org.gnome.desktop.default-applications.terminal exec", "r"), pclose
        );
    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        result.erase(remove(result.begin(), result.end(), '\''), result.end());
        result.erase(remove(result.begin(), result.end(), '\n'), result.end());
        if (!result.empty()) return result;
    }


    // Essayer KDE
    const char* home = getenv("HOME");
    if (home) {
        std::string konsolePath = std::string(home) + "/.config/konsolerc";
        FILE* f = fopen(konsolePath.c_str(), "r");
        if (f) {
            char line[256];
            while (fgets(line, sizeof(line), f)) {
                std::string s(line);
                if (s.find("DefaultProfile=") != std::string::npos) {
                    fclose(f);
                    return "konsole"; // fallback sur konsole
                }
            }
            fclose(f);
        }
    }

    // Fallbacks génériques
    const char* fallbacks[] = { "x-terminal-emulator", "gnome-terminal", "konsole", "xterm" };
    for (auto t : fallbacks) {
        if (system(("which " + std::string(t) + " > /dev/null 2>&1").c_str()) == 0) {
            return t;
        }
    }

    return ""; // aucun trouvé
}

int summonTerminal(int argc, char* argv[]){
    // Si déjà dans un terminal ou déjà relancé, on ne fait rien
    bool alreadyTty = isatty(STDIN_FILENO);
    bool sentinel = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--tty") == 0) {
            sentinel = true;
            break;
        }
    }

    // Si stdin n'est pas un terminal
    if (!alreadyTty && !sentinel) {
        std::string term = terminalFinder();
        if (!term.empty()) {
            // Relancer le programme dans le terminal détecté
            std::string cmd = term + " -e " + argv[0];
            for (int i = 1; i < argc; ++i) {
                cmd += " ";
                cmd += argv[i];
            }
            cmd += " --tty"; // Evite une boucle infinie qui ouvre des terminaux
            system(cmd.c_str());
            return 0; // on quitte l'ancien processus
        } else {
            return 1;
        }
    }
    return 0;
}

std::string getSystemLanguage(const std::string& userOverride) {
    // Override utilisateur
    if (!userOverride.empty()) {
        std::string lang = userOverride;
        transform(lang.begin(), lang.end(), lang.begin(), ::tolower);
        return lang;
    }

    // Détection système
    setlocale(LC_ALL, "");
    const char* loc = setlocale(LC_ALL, nullptr);

    if (loc && strlen(loc) >= 2) {
        std::string sysLang(loc, 2);
        transform(sysLang.begin(), sysLang.end(), sysLang.begin(), ::tolower);
        return sysLang;
    }

    return "";
}
