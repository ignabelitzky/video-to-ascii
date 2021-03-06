#pragma once

#include <string>
#include <ncurses.h>
#include <vector>

void print_centered(WINDOW *win, int startRow, std::string text);

void draw_menu(WINDOW *win, int item);
