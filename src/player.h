#ifndef PLAYER_H
#define PLAYER_H

#include "strategy.h"

struct player;

typedef struct player {
    int number;
    strategy_t strategy;
} player_t;

player_t* new_player(int);

player_t* new_human_player(int);
player_t* new_random_player(int);
#endif
