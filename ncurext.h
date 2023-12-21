#ifndef NCUREXT_H
#define NCUREXT_H

#include <ncurses.h>

#define KEY_ESC 27

WINDOW *initwin(int, int, int, int);
void clearwin(WINDOW *);

#endif
