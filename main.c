#include "ncurext.h"
#include "util.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

int main() {
  bool turn = false; // NOTE: turn+1 is player number
  int cury = 0, curx = 0;
  int board[3][3];
  bzero(board, sizeof(board));

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, true);

  mvprintw(2, (COLS - 11) / 2, "Tic Tac Toe");
  WINDOW *wboard = initwin(7, 13, (LINES - 7) / 2, (COLS - 13) / 2);

  while (true) {
    mvprintw(LINES / 2 - 5, (COLS - 7) / 2, "next: %c", name(turn + 1));
    draw_board(wboard, board, cury, curx);

    int winner = check_winner(board);
    if (winner != -1) {
      clearwin(wboard);
      clear();

      if (winner) {
        mvprintw(LINES / 2, (COLS - 9) / 2, "winner: %c", name(winner));
      } else {
        mvprintw(LINES / 2, (COLS - 4) / 2, "draw");
      }

      getch();
      endwin();
      exit(0);
    }

    switch (getch()) {
    case 'q':
    case KEY_ESC:
      delwin(wboard);
      endwin();
      exit(0);
    case 'h':
    case KEY_LEFT:
      if (curx > 0)
        --curx;
      break;
    case 'k':
    case KEY_UP:
      if (cury > 0)
        --cury;
      break;
    case 'l':
    case KEY_RIGHT:
      if (curx < 2)
        ++curx;
      break;
    case 'j':
    case KEY_DOWN:
      if (cury < 2)
        ++cury;
      break;
    case ' ':
      if (!board[cury][curx]) {
        board[cury][curx] = turn + 1;
        turn = !turn;
      }

      break;
    }
  }

  delwin(wboard);
  endwin();
  return 0;
}
