#include "reponse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void ajout_tete (int val, Liste *pL) {
    Liste p_tmp = malloc(sizeof(Liste));
    p_tmp->entier = val;
    p_tmp->multiplicite = 1;
    p_tmp->suivant = *pL;
    *pL = p_tmp;
}

void affiche_liste (Liste l) {
    if (NULL == l) return;
    printf("%d %d\n",l->entier,l->multiplicite);
    affiche_liste(l->suivant);
}

void supprime_tete (Liste *pL) {
    Liste p_tmp = (*pL)->suivant;
    free(*pL);
    *pL = p_tmp;
}

void desalloue_liste (Liste *pL) {
    while (NULL != *pL) {
        supprime_tete(pL);
    }
}

void ajout_multi_ensemble (int val, Liste *pL) {
    if (*pL == NULL || val < (*pL)->entier) {
        ajout_tete(val, pL);
        return;
    }
    if (val == (*pL)->entier) {
        (*pL)->multiplicite++;
        return;
    }
    ajout_multi_ensemble(val, &((*pL)->suivant));
}

void cree_multi_ensemble_fichier (char nom_fichier[], Liste *pL) {
    FILE *fptr;
    int val;

    fptr = fopen(nom_fichier,"r");

    while (1) {
        if (fscanf(fptr,"%d",&val) == EOF) break;
        ajout_multi_ensemble(val, pL);
    }
    fclose(fptr);
}

bool verifie_tri_croissant (Liste L) { 
    if (NULL == L->suivant) return true;
    return (L->entier < L->suivant->entier) ? verifie_tri_croissant(L->suivant) : false;
}

void detruit_multi_ensemble (Liste *pL) {
    if (NULL == *pL) return;
    supprime_tete(pL);
    detruit_multi_ensemble(pL);
}

int calcule_mul (Liste L, int x) {
    if (NULL == L) return 0;
    if (x == L->entier) return L->multiplicite;
    return calcule_mul(L->suivant,x);
}

int calcule_card (Liste L) {
    if (NULL == L) return 0;
    return L->multiplicite + calcule_card(L->suivant);
}

/*
 * On parcours l1 et ensuite l2 pour renvoyer l'adresse d'un pointeur qui sera l'union.
 * Et on remonte le parcours pour ajouter les valeurs des deux listes.
 */
Liste *union_e (Liste l1, Liste l2) {
    if (NULL == l1 && NULL == l2) {
        Liste *l = malloc(sizeof(Liste*));
        *l = NULL;
        return l;
    }
    if (NULL == l1) {
        Liste *l = union_e(l1,l2->suivant);
        for (int i = 0; i<l2->multiplicite; i++) ajout_multi_ensemble(l2->entier,l);
        return l;
    }
    Liste *l = union_e(l1->suivant,l2);
    for (int i = 0; i<l1->multiplicite; i++) ajout_multi_ensemble(l1->entier,l);
    return l;
}

Liste *intersection (Liste l1, Liste l2) {
    if (NULL == l1) {
        Liste *l = malloc(sizeof(Liste*));
        *l = NULL;
        return l;
    }
    Liste *l = intersection(l1->suivant,l2);
    int min_multi = (l1->multiplicite<l2->multiplicite)?l1->multiplicite:l2->multiplicite;
    if (calcule_mul(l2,l1->entier) != 0) {
        for (int i = 0; i<min_multi; i++) ajout_multi_ensemble(l1->entier,l);
    }

    return l;
}

Liste *difference (Liste l1, Liste l2) {
    if (NULL == l1 && NULL == l2) {
        Liste *l = malloc(sizeof(Liste*));
        *l = NULL;
        return l;
    }
    if (NULL == l2) {
        Liste *l = difference(l1->suivant,l2);
        for (int i = 0; i<l1->multiplicite; i++) ajout_multi_ensemble(l1->entier,l);
        return l;
    }
    Liste *l = difference(l1,l2->suivant);
    int m = calcule_mul (*l, l2->entier);

    if (m != 0) {
        Liste p_tmp = *l;
        while (l2->entier != p_tmp->entier) {
            p_tmp = p_tmp->suivant;
        }
        p_tmp->multiplicite = (p_tmp->multiplicite - l2->multiplicite) > 0 ? p_tmp->multiplicite - l2->multiplicite : 0;
    }
    return l;
}