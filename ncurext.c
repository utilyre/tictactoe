#include <ncurses.h>

WINDOW *initwin(int height, int width, int y, int x) {
  WINDOW *win = newwin(height, width, y, x);
  refresh();
  box(win, 0, 0);
  wrefresh(win);
  return win;
}

void clearwin(WINDOW *win) {
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(win);
  delwin(win);
}
