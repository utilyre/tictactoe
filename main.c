#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#define KEY_ESC 27

char name(int player) {
  switch (player) {
  case 1:
    return 'O';
  case 2:
    return 'X';
  default:
    return '-';
  }
}

void draw_board(WINDOW *win, int board[3][3], int cury, int curx) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      char cur = ' ';
      if (i == cury && j == curx) {
        cur = '*';
      }

      mvwprintw(win, 2 * i + 1, 4 * j + 2, "%c%c", name(board[i][j]), cur);
    }
  }

  wrefresh(win);
}

int check_winner(int board[3][3]) {
  // horizontal
  if (board[0][0] && board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
    return board[0][0];
  }
  if (board[1][0] && board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
    return board[1][0];
  }
  if (board[2][0] && board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
    return board[2][0];
  }
  // vertical
  if (board[0][0] && board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
    return board[0][0];
  }
  if (board[0][1] && board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
    return board[0][1];
  }
  if (board[0][2] && board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
    return board[0][2];
  }
  // diagonal
  if (board[0][0] && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return board[0][0];
  }
  if (board[0][2] && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return board[0][2];
  }

  bool full = true;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (!board[i][j]) {
        full = false;
      }
    }
  }
  if (full) {
    return 0;
  }

  return -1;
}

int main() {
  bool turn; // turn+1 is player number
  int cury = 0, curx = 0;
  int board[3][3];
  bzero(board, sizeof(board));

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, true);

  mvprintw(2, (COLS - 11) / 2, "Tic Tac Toe");

  WINDOW *wboard = newwin(7, 13, (LINES - 7) / 2, (COLS - 13) / 2);
  refresh();
  box(wboard, 0, 0);
  wrefresh(wboard);

  while (1) {
    mvprintw((LINES - 10) / 2, (COLS - 8) / 2, "next: %c", name(turn + 1));
    draw_board(wboard, board, cury, curx);

    int winner = check_winner(board);
    if (winner != -1) {
      wborder(wboard, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
      wrefresh(wboard);
      delwin(wboard);
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
