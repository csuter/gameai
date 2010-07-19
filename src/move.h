#ifndef MOVE_H
#define MOVE_H

struct move_list;

typedef struct move {
    int i, j;
} move_t;

typedef struct move_list {
    move_t* move;
    int len;
    struct move_list* next;
} move_list_t;

move_t* new_move();
move_list_t* new_move_list();
move_list_t* move_list_add(move_list_t*, move_t*);
move_t* move_list_get(move_list_t*,int);

move_t* copy_move(move_t*);

void free_move_list(move_list_t*);

#endif
