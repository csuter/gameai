#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "strategy.h"
#include "player.h"
#include "move.h"

player_t* new_player(int number)
{
    player_t* result = (player_t*)malloc(sizeof(player_t));
    result->number = number;
    return result;
}

player_t* new_human_player(int number)
{
    player_t* result = new_player(number);
    result->strategy = &poll_stdin_for_move;
}

player_t* new_random_player(int number)
{
    player_t* result = new_player(number);
    result->strategy = &random_move;
}

void print_board(board_t* board)
{
    printf(
            " %s | %s | %s \n---+---+---\n %s | %s | %s \n---+---+---\n %s | %s | %s\n",
            (board->state[0]==0)?" ":(board->state[0]==1)?"x":"o",
            (board->state[1]==0)?" ":(board->state[1]==1)?"x":"o",
            (board->state[2]==0)?" ":(board->state[2]==1)?"x":"o",
            (board->state[3]==0)?" ":(board->state[3]==1)?"x":"o",
            (board->state[4]==0)?" ":(board->state[4]==1)?"x":"o",
            (board->state[5]==0)?" ":(board->state[5]==1)?"x":"o",
            (board->state[6]==0)?" ":(board->state[6]==1)?"x":"o",
            (board->state[7]==0)?" ":(board->state[7]==1)?"x":"o",
            (board->state[8]==0)?" ":(board->state[8]==1)?"x":"o"
          );
}

