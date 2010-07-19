#include <stdio.h>
#include <stdlib.h>
#include "move.h"

move_t* new_move()
{
    return (move_t*)malloc(sizeof(move_t));
}

move_t* copy_move(move_t* src)
{
    move_t* dest = new_move();
    dest->i = src->i;
    dest->j = src->j;
    return dest;
}

move_list_t* new_move_list()
{
    move_list_t* result = (move_list_t*)malloc(sizeof(move_list_t));
    result->len = 0;
    result->move = NULL;
    result->next = NULL;
}

move_list_t* move_list_add(move_list_t* list, move_t* move)
{
    list->len++;
    if (list->move == NULL) {
        list->move = move;
        return list;
    }
    move_list_t* last = list;             // start at teh start
    while (last->next) last = last->next; // find last in list
    last->next = new_move_list();         // set last's next to new
    last->next->move = move;              // set last->next->move to added move;
    return list; // return head of modified list;
}

void free_move_list(move_list_t* list)
{
    move_list_t* curr = list;
    move_list_t* next = list->next;

    while(curr) {
        if (curr->move) free(curr->move);
        next = curr->next;
        free(curr);
        curr = next;
    }
}
