#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

void init_cell(struct cell ** pl){
    *pl = NULL;
}

void init_list(struct list * p_l){
    p_l -> t = NULL;
    p_l -> q = NULL;
}

void ajout_tete(struct cell ** pl, element x){
    struct cell * ptr = malloc(sizeof(struct cell));
    ptr -> val = x;
    ptr -> suiv = *pl;
    *pl = ptr;
}

void free_cell(struct cell ** pl){
    if (*pl == NULL) return;
    struct cell * p_tmp = (*pl) -> suiv;
    free(*pl);
    *pl = p_tmp;
}

void free_all_cell(struct cell ** pl){
    while (*pl != NULL) free_cell(pl);
}