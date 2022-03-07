#include "menu.h"

void print_centered(WINDOW *win, int startRow, std::string text) {
    int centerCol = win->_maxx / 2;
    int halfLength = text.length() / 2;
    int adjustedCol = centerCol - halfLength;

    mvwprintw(win, startRow, adjustedCol, text.c_str());
}

void draw_menu(WINDOW *win, int item) {
    std::string mainmenu = "Main menu";
    std::string stopMessage = "Press m or M to go back to the menu";
    std::string quitMessage = "Press q or Q to close the program";
    std::string instructions = "Use arrow keys (up and down) for selection";
    std::vector<std::string> menu {
        "Encanto",
        "Matrix",
        "Quantum of Solace",
        "Interstellar",
        "Pirates of the Caribbean",
        "Inception",
    };
    wclear(win);
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    wbkgd(win, COLOR_PAIR(1));
    print_centered(win, 1, mainmenu);
    print_centered(win, 3, instructions);
    for(int i = 0; i < menu.size(); ++i) {
        if(i == item)
            wattron(win, A_REVERSE);
        print_centered(win, 6 + (i * 2), menu.at(i));
        wattroff(win, A_REVERSE);
    }
    print_centered(win, win->_maxy - 3, stopMessage);
    print_centered(win, win->_maxy - 1, quitMessage);
    wmove(win, 0, 0);
    wrefresh(win);
}
