#include "struct.h"
#include <stdio.h>

void ajout_tete (Multi_ens val, Liste *pL){
    Liste p_tmp = malloc(sizeof(Liste));
    p_tmp->valeur = val;
    p_tmp->suivant = *pL;
    *pL = p_tmp;
}

void affiche_liste (Liste l){
    while (NULL != l){
        printf("P: %p\tV: %d\tM: %d\n",l,l->valeur.entier,l->valeur.multiplicité);
        l = l->suivant;
    }
}

void supprime_tete (Liste *pL){
    Liste p_tmp = (*pL)->suivant;
    free(*pL);
    *pL = p_tmp;
}

void desalloue_liste (Liste *pL){
    while (NULL != *pL){
        supprime_tete(pL);
    }
}

