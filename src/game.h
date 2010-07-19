#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

typedef struct game {
    board_t* board;
    player_t** players;
    int current_player; // position in players[] of current player
    move_list_t* moves;
} game_t;

typedef struct game_state {
    move_list_t* moves;
} game_state_t;

game_t* new_two_player_game(board_t*, player_t*, player_t*);
game_t* new_game(player_t* players[]);

int do_move_if_can(game_t*, move_t*);

int play_new_game(player_t** p);
int play_game(game_t*);
void reset_game(game_t*);
void free_game(game_t*);

void apply_move(game_t*, move_t*);
void apply_move_list(game_t*, move_list_t*);

game_state_t* new_game_state();
void save_game_state(game_state_t*, game_t*);
void load_game_state(game_state_t*, game_t*);
game_state_t* copy_game_state(game_state_t* src);
#endif
