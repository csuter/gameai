#ifndef BOARD_H
#define BOARD_H

typedef struct board {
    char state[9];
} board_t;

board_t* new_board();
void print_board(board_t*);
int board_won(board_t*);
int board_full(board_t*);

void zero_board(board_t*);

#endif
