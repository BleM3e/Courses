#ifndef __ANNU1_H__
#define __ANNU1_H__

#define TAILLE_NAME 20
#define TAILLE_TEL 10
#define MAX_PERSONNES 100

struct date_t
{
    int jour;
    int mois;
    int annee;
};

struct personne_t
{
    char nom[TAILLE_NAME];
    char prenom[TAILLE_NAME];
    char telephone[TAILLE_TEL];
    struct date_t date_de_naissance;
};

struct annuaire_t
{
    struct personne_t pers[MAX_PERSONNES];
    int dernier;
};

struct date_t lire_date ();
void          affiche_date (struct date_t);
int           lire_personne (struct personne_t *pers);
void          affiche_personne (struct personne_t pers);
void          construire_annuaire (struct annuaire_t *annu);
int           lire_personne_annu (struct personne_t *pers);
void          affiche_annuaire (struct annuaire_t a);
int           compare_dates (struct date_t d1, struct date_t d2);
void          trie_annu_date (struct annuaire_t *p_a);
void          trie_annu_nom (struct annuaire_t *p_a);

#endif
