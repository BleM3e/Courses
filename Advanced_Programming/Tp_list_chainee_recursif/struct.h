#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct multi_ensemble
{
    int entier;
    int multiplicité;
} Multi_ens;

typedef struct cellule_t
{
    Multi_ens valeur;
    struct cellule_t * suivant;
} Cellule;

typedef Cellule *Liste;


#endif