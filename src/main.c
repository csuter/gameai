#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "learning_player.h"

#define X_WINS 0
#define Y_WINS 1
#define CATS 2

int main(char argc, char argv[])
{
    int i;
    srand ( time(NULL) );

    player_t** p = (player_t**)malloc(2 * sizeof(player_t*));

    p[0] = new_learning_player(1);
    //p[0] = new_random_player(1);
    p[1] = new_random_player(2);

    int results[3];
    results[X_WINS] = 0;
    results[Y_WINS] = 0;
    results[CATS] = 0;

    int n_runs = 1;

    int result;
    for (i = 0; i < n_runs; i++) {
        result = play_new_game(p);
        if (result == 0) results[CATS]++;
        else if (result == 1) results[X_WINS]++;
        else if (result == 2) results[Y_WINS]++;
    }

    printf("Cats: %d\n", results[CATS]);
    printf(" P 1: %d\n", results[X_WINS]);
    printf(" P 2: %d\n", results[Y_WINS]);

    free(p[0]);
    free(p[1]);
    free(p);

    return 0;
}
