#include "reponse.h"
#include <stdio.h>

int main ()
{
    Liste l = NULL;
    //Liste m = NULL;
    //Liste n = NULL;
    //Liste o = NULL;
    
    /*
    ajout_dans_liste_triee(0, &l);
    ajout_dans_liste_triee(-2, &l);
    ajout_dans_liste_triee(3, &l);
    ajout_dans_liste_triee(2, &l);
    ajout_dans_liste_triee(-5, &l);
    ajout_dans_liste_triee(-2, &l);
    ajout_dans_liste_triee(3, &l);
    ajout_dans_liste_triee(1, &l);
    ajout_dans_liste_triee(5, &l);
    ajout_dans_liste_triee(5, &l);
    ajout_dans_liste_triee(5, &l);
*/
    ajout_tete(2,&l);
    ajout_tete(-2,&l);
    ajout_tete(-4,&l);
    ajout_tete(1,&l);
    ajout_tete(3,&l);
    ajout_tete(2,&l);

    liste_vers_ensemble(&l);

    affiche_liste(l);
/*
    cree_liste_fichier("test.txt",&m);

    n = union_ensemble(l,m);

    affiche_liste(n);

    printf("\n");

    o = intersection_ensemble(l,m);

    affiche_liste(o);

    desalloue_liste(&n);
    desalloue_liste(&o);
    */
    desalloue_liste(&l);
    //desalloue_liste(&m);

    return 0;
}
