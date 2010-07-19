#ifndef STRATEGY_H
#define STRATEGY_H

#include "move.h"

struct game;
typedef move_t* (*strategy_t) (struct game *);

move_t* poll_stdin_for_move(struct game*);
move_t* random_move(struct game*);
#endif
