cmake_minimum_required(VERSION 3.16)

project(SnakeTerminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SnakeTerminal main.cpp
    TerminalToolBox.h
    UserInterface.h
    Structures.hpp
    Display.h
    GamePlay.h
    TerminalToolBox.cpp
    UserInterface.cpp
    Structures.cpp
    GamePlay.cpp
    Display.cpp
    SnakeTerminal.cpp
    SnakeTerminal.h
    GameState.hpp GameState.cpp

    input.h input.cpp
    saveSpace.cpp
    saveSpace.hpp
)

include(GNUInstallDirs)
install(TARGETS SnakeTerminal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(SnakeTerminal ${CURSES_LIBRARIES})
target_include_directories(SnakeTerminal PRIVATE ${CURSES_INCLUDE_DIR})

target_link_libraries(SnakeTerminal ncursesw)
