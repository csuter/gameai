#include <stdlib.h>

#include "board.h"

board_t* new_board()
{
    board_t* result = malloc(sizeof(board_t));
    zero_board(result);
    return result;
}

int board_won(board_t* b)
{
    int i;
    // check rows
    int s;
    //  0,0 1,0 2,0
    //  0,1 1,1 2,1
    //  0,2 1,2 2,2
    //
    //   0   1   2
    //   3   4   5
    //   6   7   8
    //
    // i =   0     1     2
    //     3*0+i 3*0+i 3*0+i
    //     3*1+i 3*1+i 3*1+i
    //     3*2+i 3*2+i 3*2+i
    //
    // i
    // 0  3*i+0 3*i+1 3*i+2
    // 1  3*i+0 3*i+1 3*i+2
    // 2  3*i+0 3*i+1 3*i+2

    // check rows
    for (i = 0; i < 3; i++) {
        s = b->state[3*i+0];  // get leftmost element of row i
        if (s == 0) continue; // if leftmost element is 0, skip row
        // if both the center and rightmost elements of row i
        // are equal to the leftmost element, player s wins; return s
        if ((s == b->state[3*i+1]) && (s == b->state[3*i+2])) {
            return s;
        }
    }

    // check cols
    for (i = 0; i < 3; i++) {
        s = b->state[3*0+i]; // get topmost element of col i
        if (s == 0) continue; // if topmost element is 0, skip col
        // if both the middle and bottommost elements of coli
        // are equal to the topmost element, player s wins; return s
        if ((s == b->state[3*1+i]) && (s == b->state[3*2+i])) {
            return s;
        }
    }
    // check diagonals, starting with center
    s = b->state[4];
    if (s == 0) return 0; // center not set; no diags possible
    if ((s == b->state[0]) && (s == b->state[8])) {
        return s; // top-left to bottom-right
    }
    if ((s == b->state[2]) && (s == b->state[6])) {
        return s; // top-right to bottom-left
    }
    return 0;
}

int board_full(board_t* b)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (b->state[i] == 0) return 0;
    }
    return 1;
}

void zero_board(board_t* b)
{
    int i;
    for (i=0;i<9;i++)
        b->state[i] = 0;
}
