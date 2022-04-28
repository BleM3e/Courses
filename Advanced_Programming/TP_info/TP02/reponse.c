#include "reponse.h"
#include <stdio.h>
#include <string.h>

struct date_t lire_date(){
    struct date_t date;
    scanf("%d",&(date.jour));
    scanf("%d",&(date.mois));
    scanf("%d",&(date.annee));
    return date;
}

void affiche_date(struct date_t date){
    printf("%d/%d/%d",date.jour,date.mois,date.annee);
}

int lire_personne(struct personne_t *pers){
    scanf("%19s %19s",pers->nom,pers->prenom);
    pers->date_de_naissance = lire_date();
    scanf("%9s",pers->telephone);
    return 0;
}

void affiche_personne(struct personne_t pers){
    printf("%s %s\n",pers.nom,pers.prenom);
    affiche_date(pers.date_de_naissance);
    printf(" %s\n",pers.telephone);
}

void construire_annuaire(struct annuaire_t *annu){
    int etat;
    while ((etat = lire_personne_annu(&(annu->pers[annu->dernier]))) == 0){
        if (etat == 0){
            annu->dernier++;
        }
    }
    annu->dernier--;
}

int lire_personne_annu(struct personne_t *pers){
    if (scanf("%19s",pers->nom) == EOF) return 1;
    scanf("%19s",pers->prenom);
    pers->date_de_naissance = lire_date();
    scanf("%9s",pers->telephone);
    return 0;
}

void affiche_annuaire(struct annuaire_t a){
    for (int i = 0; i <= a.dernier; i++){
        printf("%d%d. ",i/10,i%10);
        affiche_personne(a.pers[i]);
    }
}

int compare_dates(struct date_t d1, struct date_t d2){
    if (d1.annee != d2.annee) return d1.annee>d2.annee?1:-1;
    if (d1.mois != d2.mois) return d1.mois>d2.mois?1:-1;
    if (d1.jour != d2.jour) return d1.jour>d2.jour?1:-1;
    return 0;
}

void trie_annu_date(struct annuaire_t * p_a){
    int n_ranger = 1; //Vaut 1 lorsque l'annuaire n'est pas encore trié, 0 sinon
    while (n_ranger == 1){
        n_ranger = 0;
        for (int i = 0; i < p_a -> dernier; i++){
            if (compare_dates((p_a -> pers[i]).date_de_naissance, (p_a -> pers[i+1]).date_de_naissance)==1){
                n_ranger = 1;
                struct personne_t tmp_pers = p_a->pers[i];
                p_a->pers[i] = p_a->pers[i+1];
                p_a->pers[i+1] = tmp_pers;
            }
        }
    }
}

void trie_annu_nom(struct annuaire_t * p_a){
    int n_ranger = 1;
    while (n_ranger == 1) {
        n_ranger = 0;
        for (int i = 0; i < p_a -> dernier; i++){
            if (strcmp((p_a->pers[i]).nom,(p_a->pers[i+1]).nom) <= 0){
                if (strcmp((p_a->pers[i]).prenom,(p_a->pers[i+1]).prenom) > 0){
                    n_ranger = 1;
                    struct personne_t tmp_pers = p_a->pers[i];
                    p_a->pers[i] = p_a->pers[i+1];
                    p_a->pers[i+1] = tmp_pers;
                }
            }
            else {
                n_ranger = 1;
                struct personne_t tmp_pers = p_a->pers[i];
                p_a->pers[i] = p_a->pers[i+1];
                p_a->pers[i+1] = tmp_pers;
            }
        }
    }
}