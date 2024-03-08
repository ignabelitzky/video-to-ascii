#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <ncurses.h>
#include <vector>

void print_centered(WINDOW *win, int startRow, std::string text);

void draw_menu(WINDOW *win, size_t item);

#endif
