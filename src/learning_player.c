#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "strategy.h"
#include "learning_player.h"

#define NUM_RAND_GAME_ITS 10

move_t* smart_move(game_t*);
int* run_random_test_games(game_state_t* gs, int n);

player_t* new_learning_player(int number)
{
    player_t* result = (player_t*)malloc(sizeof(player_t));
    result->number = number;
    result->strategy = &smart_move;
    //result->strategy = &random_move;
}

move_t* smart_move(game_t* g)
{
    int me = g->players[g->current_player]->number;
    move_t* result;

    move_list_t* possible_moves = new_move_list();
    move_list_t* curr;
    int c;
    int best_yet = -1;
    move_t* move;

    game_state_t* gs;
    game_state_t* current_game_state = new_game_state();
    save_game_state(current_game_state, g);
    int* single_result_set;

    // add all possible moves to possible_moves list
    for (c = 0; c < 9; c++) {
        if (g->board->state[c] == 0) {
            move = new_move();
            move->i = c % 3;
            move->j = c / 3;
            move_list_add(possible_moves, move);
        }
    }

    // if none possible (shouldn't happen) return null
    if (possible_moves->len == 0) {
        result = NULL;
    } else if(possible_moves->len == 1) {
        result = copy_move(possible_moves->move); // get a copy of first move on list
    } else { // choose!

        result = new_move();

        // for each move, we run a bunch of random games and see
        // which move has the highest number of winning games
        c = 0;
        for (curr = possible_moves; curr != NULL; curr = curr->next) {
            gs = copy_game_state(current_game_state);     // clone current state
            move_list_add(gs->moves, curr->move);         // add move currently under consideration
            single_result_set = run_random_test_games( gs, 5 ); // get results of 5 test games
            if(single_result_set[me] > best_yet) {
                result->i = curr->move->i;
                result->j = curr->move->j;
                best_yet = single_result_set[me]; // update best_yet
            }

            free(single_result_set);
            free_game_state(gs);
            c++;
        }
    }

    free_move_list(possible_moves);
    return result;
}


int* run_random_test_games(game_state_t* gs, int n)
{
    int* results = (int*)malloc(3*sizeof(int));

    player_t** players = (player_t**)malloc(2*sizeof(player_t*));

    players[0] = new_random_player(1);
    players[1] = new_random_player(2);

    game_t* test_game = new_game(players);
    int i;

    results[0] = 0;
    results[1] = 0;
    results[2] = 0;
    for (i = 0; i < n; i++) {
        load_game_state(gs, test_game);     // load test state
        ++(results[play_game(test_game)]);  // play out game, increment result
    }

    free(players[0]);
    free(players[1]);
    free_game(test_game);

    return results;
}
