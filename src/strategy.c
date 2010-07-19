#include <stdio.h>
#include "move.h"
#include "game.h"
#include "strategy.h"

move_t* poll_stdin_for_move(game_t *g)
{
    print_board(g->board);

    move_t* move = new_move();
    printf("Player %d, enter \"i j\" (both 0,1, or 2, space separated): ", g->players[g->current_player]->number);
    scanf("%d %d", &(move->i), &(move->j));

    return move;
}

move_t* random_move(game_t *g)
{
    move_t* move = new_move();
    move->i = rand() % 3;
    move->j = rand() % 3;
    return move;
}
