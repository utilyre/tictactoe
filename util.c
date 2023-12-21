#include <ncurses.h>

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
      mvwprintw(win, 2 * i + 1, 4 * j + 2, "%c%c", name(board[i][j]),
                (i == cury && j == curx) ? '*' : ' ');
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
