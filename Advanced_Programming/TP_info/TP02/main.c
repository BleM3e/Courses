#include "reponse.h"
#include <stdio.h>

int main (void)
{
    struct annuaire_t annu;
    annu.dernier = 0;
    construire_annuaire(&annu);
    affiche_annuaire(annu);

    struct annuaire_t cp_annu;

    cp_annu = annu;   //Copie de annu
    trie_annu_date(&cp_annu);
    affiche_annuaire(cp_annu);

    cp_annu = annu;
    trie_annu_nom(&cp_annu);
    affiche_annuaire(cp_annu);

    return 0;
}
