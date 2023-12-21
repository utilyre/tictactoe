#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>

char name(int);
void draw_board(WINDOW *, int[3][3], int cury, int curx);
int check_winner(int[3][3]);

#endif
