#include "reponse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void ajout_tete (int val, Liste *pL){
    Liste p_tmp = malloc(sizeof(Liste));
    p_tmp->valeur = val;
    p_tmp->suivant = *pL;
    *pL = p_tmp;
}

void affiche_liste (Liste l){
    while (NULL != l){
        printf("%d\n",l->valeur);
        l = l->suivant;
    }
}

bool est_triee (Liste l){
    if (NULL == l || NULL == l->suivant) return 1; //On considère que si la liste n'est pas initialisé ou n'a qu'une valeur, la liste est triée
    while (NULL != l->suivant){
        if (l->valeur > l->suivant->valeur) return 0;
        l = l->suivant;
    }
    return 1;
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

void ajout_dans_liste_triee (int val, Liste *pL){
    if (NULL == *pL){ 
        ajout_tete(val, pL); 
        return;
    }
    Liste *p_tmp = pL;
    int prec_val = (*p_tmp)->valeur;
    while (NULL != *p_tmp){
        if (val == prec_val) return;
        if (val < (*p_tmp)->valeur){
            ajout_tete(val, p_tmp);
            return;
        }
        prec_val = (*p_tmp)->valeur;
        p_tmp = &((*p_tmp)->suivant);
    }
    if (val != prec_val){
        ajout_tete(val, p_tmp);
    }
}

void cree_liste_fichier (char nom_fichier[], Liste *pL){
    FILE *fptr;
    int val;

    fptr = fopen(nom_fichier,"r");

    while (1){
        if (fscanf(fptr,"%d",&val) == EOF) break;
        ajout_dans_liste_triee(val, pL);
    }
    fclose(fptr);
}

bool contient_doublons (Liste l){
    if (NULL == l || NULL == l->suivant) return 0;
    Liste tmp_l;
    while (NULL != l){
        tmp_l = l;
        while ((tmp_l = tmp_l->suivant) != NULL){
            if (l->valeur == tmp_l->valeur) return 1;
        }
        l = l->suivant;
    }
    return 0;
}

Liste union_ensemble (Liste l1, Liste l2){
    Liste l = NULL;
    while (l1 != NULL){
        ajout_dans_liste_triee(l1->valeur,&l);
        l1 = l1->suivant;
    }
    while (l2 != NULL){
        ajout_dans_liste_triee(l2->valeur,&l);
        l2 = l2->suivant;
    }
    return l;
}

Liste intersection_ensemble (Liste l1, Liste l2){
    Liste l = NULL;
    Liste l_tmp;
    while (l1 != NULL){
        l_tmp = l2;
        while (l_tmp != NULL){
            if (l1->valeur == l_tmp->valeur){
                ajout_dans_liste_triee(l1->valeur,&l);
            }
            l_tmp = l_tmp->suivant;
        }
        l1 = l1->suivant;
    }
    return l;
}

void liste_vers_ensemble (Liste *pL){ //Renvoie un ensemble ordonné
    Liste l = *pL;
    Liste f_l = NULL;
    while (NULL != l){
        ajout_dans_liste_triee(l->valeur,&f_l);
        l = l->suivant;
    }
    *pL = f_l;
}
