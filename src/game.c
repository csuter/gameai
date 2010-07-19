#include <stdio.h>
#include <stdlib.h>
#include "game.h"

game_t* new_game(player_t* players[])
{
    game_t* result = (game_t*)malloc(sizeof(game_t));

    result->board = new_board();
    result->players = players;
    result->moves = new_move_list();

    return result;
}

int check_move(game_t* g, move_t* move)
{
    if (move) {
        if (g->board->state[3*move->j+move->i] == 0) {
            return 1;
        }
    }
    return 0;
}

void apply_move(game_t* g, move_t* move)
{
    board_t* board = g->board;
    player_t* p = g->players[g->current_player];

    // update board state
    board->state[3*move->j+move->i] = p->number;
    // set first non-zero element of moves to 3*i + j + )1 (in {1,...,9})
    move_list_add(g->moves, copy_move(move));

    g->current_player += 1;
    g->current_player %= 2;
}

int check_and_apply_move(game_t* g, move_t* move)
{
    if (check_move(g, move)) {
        apply_move(g, move);
        return 1;
    }
    return 0;
}

int play_new_game(player_t** p) {
    game_t* g = new_game(p);
    zero_board(g->board);
    int result = play_game(g);
    free_game(g);
    return result;
}

int play_game(game_t* g)
{
    move_t* move;
    int winner;
    int going = 1;
    player_t* curr;
    g->current_player = 0;

    while (going) {
        curr = g->players[g->current_player];

        // get next move from curr player's strategy, check for
        // legality. if failed check, free move, do again;
        while ( !check_move(g, move = (*(curr->strategy))(g)) )
            free(move);

        apply_move(g, move); // makes a copy of move in g->moves,
        free(move);          // so we can free our copy.

        // check for win state
        if (winner = board_won(g->board)) {
            going = 0;
            break;
        } else {
            if (board_full(g->board)) {
                going = 0;
                winner = 0;
            }
        }
    }

    return winner;
}

void reset_game(game_t* g)
{
    zero_board(g->board);
    free_move_list(g->moves);
    g->moves = new_move_list();
    g->current_player = 0;
}

void free_game(game_t* g)
{
    free(g->board);
    free_move_list(g->moves);
    free(g);
}

void apply_move_list(game_t* g, move_list_t* moves)
{
    move_list_t* curr = moves;
    while (curr) {
        if (curr->move) {
            apply_move(g, curr->move);
        }
        curr = curr->next;
    }
}

game_state_t* new_game_state()
{
    return (game_state_t*)malloc(sizeof(game_state_t));
}

void save_game_state(game_state_t* gs, game_t* g)
{
    gs->moves = new_move_list();
    if (g->moves->move == NULL) return;
    move_list_t* g_curr;
    for(g_curr = g->moves; g_curr != NULL; g_curr = g_curr->next) {
        move_list_add(gs->moves, copy_move(g_curr->move));
    }
}

void load_game_state(game_state_t* gs, game_t* g)
{
    zero_board(g->board);       // reset the board
    free_move_list(g->moves);   // free g's current move list
    g->moves = new_move_list();
    g->current_player = 0;
    apply_move_list(g, gs->moves);
}

void free_game_state(game_state_t* gs)
{
    free_move_list(gs->moves);
    free(gs);
}

game_state_t* copy_game_state(game_state_t* src)
{
    game_state_t* dest = new_game_state();
    dest->moves = new_move_list();
    if (src->moves->move == NULL) return dest;
    move_list_t* curr;
    for (curr = src->moves; curr != NULL; curr = curr->next) {
        move_list_add(dest->moves, copy_move(curr->move));
    }
    return dest;
}
