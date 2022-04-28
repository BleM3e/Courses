#include "reponse.h"
#include <stdio.h>

int main ()
{
    Liste l = NULL;

    Liste m = NULL;
    
    /*
    ajout_tete(1,&l);
    ajout_tete(-1,&l);
    ajout_tete(0,&l);
    ajout_tete(2,&l);
    ajout_tete(3,&l);
    */

    
    ajout_multi_ensemble(0,&l);
    ajout_multi_ensemble(-1,&l);
    ajout_multi_ensemble(1,&l);
    ajout_multi_ensemble(4,&l);
    ajout_multi_ensemble(2,&l);
    ajout_multi_ensemble(-3,&l);
    ajout_multi_ensemble(4,&l);
    ajout_multi_ensemble(-1,&l);
    ajout_multi_ensemble(3,&l);
    
    /*
    int MULTI_CHECK = 10;
    int LENGTH_TO_CHECK = 10; 
    
    int          seed  = 2;
    unsigned int multi = 1 + rand () % MULTI_CHECK;
    
    printf("%d\n", multi);;
    
    int          val_array[LENGTH_TO_CHECK];
    for (unsigned int i = 0; i < LENGTH_TO_CHECK; i++)
    {
        val_array[i] = seed * i;
        ajout_multi_ensemble (val_array[i], &l);
    }
    // re-insert same values
    for (unsigned int i = 0; i < LENGTH_TO_CHECK; i++)
    {
        for (unsigned int j = 1; j < multi; j++)
            ajout_multi_ensemble (val_array[i], &l);
    }*/
    
    ajout_multi_ensemble (3, &m);
    ajout_multi_ensemble (5, &m);
    ajout_multi_ensemble (3, &m);
    ajout_multi_ensemble (3, &m);
    ajout_multi_ensemble (5, &m);
    ajout_multi_ensemble (-1, &m);

/*
    (3== calcule_mul (l, 3))?printf("vrai\n"):printf("faux\n");
    (2== calcule_mul (l, 5))?printf("vrai\n"):printf("faux\n");
*/
    //printf("%d\n",calcule_card(l));
    affiche_liste(l);
    printf("\n");
    affiche_liste(m);
    printf("\n");

    Liste   *l3  = difference (l, m);
    Cellule *ptr = *l3;
    while (NULL != ptr)
    {
        int m1 = calcule_mul (l, ptr->entier);
        int m2 = calcule_mul (m, ptr->entier);
        (ptr->multiplicite == (m1 - m2) > 0 ? m1 - m2 : 0)?printf("e: %d m: %d d: %d\tVrai\n",ptr->entier,ptr->multiplicite,m1-m2):printf("e: %d m: %d d: %d\tFaux\n",ptr->entier,ptr->multiplicite,m1-m2);
        ptr = ptr->suivant;
    }
    affiche_liste(*l3);

    desalloue_liste(&l);
    desalloue_liste(&m);
    desalloue_liste(l3);

    return 0;
}
