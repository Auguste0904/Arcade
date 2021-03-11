-- PROJECT: Arcade --

Group: Auguste ALEXANDRE - Eliot LE-GALL - Romain DUFOURT

USAGE:
    ./arcade [lib]

DESCRIPTION:
    Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.
    You will be able to play 2 different video games (Nibbler or Pacman) and switch between them and graphic libraries when you want at running time.
    There are at least 3 different graphic libraries available: - SFML
                                                                - Ncurses
                                                                - SDL2
    Enjoy !!!

EXAMPLES:
    ./arcade lib/lib_arcade_sfml.so
    ./arcade lib/lib_arcade_ncurses.so
    ./arcade lib/lib_arcade_sdl2.so

HOW TO INSTALL:
    SFML: sudo dnf install SFML-devel
    nCurses: sudo dnf install ncurses-devel
    SDL2: sudo dnf install SDL2-devel