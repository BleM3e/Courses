#ifndef __REPONSE_H__
#define __REPONSE_H__

#include <stdbool.h>

/*
 * @brief Q1: définir la structure cellule et utiliser
 * un typedef pour définir Cellule et Liste
 */
typedef struct cellule_t
{
    int entier;
    int multiplicite;
    struct cellule_t * suivant;
} Cellule;

typedef Cellule *Liste;

/**
 * @brief Q2: Ajoute un element en tete de la liste
 *
 * @param val element a inserer
 * @param pL pointeur sur liste chainee
 */
void ajout_tete (int val, Liste *pL);

/**
 * @brief Q3: Affiche récursivement le contenu d'une liste chainee
 *
 * @param l liste chainee d'entiers
 */
void affiche_liste (Liste l);

/**
 * @brief Q4: Supprime l'element en tete d'une liste
 *
 * @param pL pointeur sur liste chainee
 */
void supprime_tete (Liste *pL);

/**
 * @brief Q5: Desalloue la liste -- libere la memoire
 *
 * @param pL pointeur sur liste a desallouer
 */
void desalloue_liste (Liste *pL);

/**
 * @brief Q6: Ajout un element dans un multi-ensemble
 *
 * @param val element a inserer
 * @param pL pointeur sur multi-ensemble
 */
void ajout_multi_ensemble (int val, Liste *pL);

/**
 * @brief Q7: Crée un multi-ensemble à partir d'un fichier contenant des entiers
 *
 * @param nom_fichier nom du fichier contenant des entiers (1 par ligne)
 * @param pL pointeur sur multi-ensemble
 */
void cree_multi_ensemble_fichier (char nom_fichier[], Liste *pL);

/**
 * @brief Q8: verifie qu'un multi-ensemble est trié
 *
 * @param L multi-ensemble
 * @return true si triée, false sinon
 */
bool verifie_tri_croissant (Liste L);

/**
 * @brief Q9: détruit un multi-ensemble
 *
 * @param pL pointeur sur multi-ensemble
 */
void detruit_multi_ensemble (Liste *pL);

/**
 * @brief Q10: calcul la multiplicité d'un entier donné
 *
 * @param L multi-ensemble
 * @param x entier recherché
 * @return entier >=0
 */
int calcule_mul (Liste L, int x);

/**
 * @brief Q11: calcul le cardinal d'un multi-ensemble
 *
 * @param L multi-ensemble
 * @return entier >=0
 */
int calcule_card (Liste L);

/**
 * @brief Q12: calcul l'union de deux multi-ensembles
 *
 * @param l1 multi-ensemble
 * @param l2 multi-ensemble
 * @return pointeur sur multi-ensemble
 */
Liste *union_e (Liste l1, Liste l2);

/**
 * @brief Q13: calcul l'intersecion de deux multi-ensembles
 *
 * @param l1 multi-ensemble
 * @param l2 multi-ensemble
 * @return pointeur sur multi-ensemble
 */
Liste *intersection (Liste l1, Liste l2);

/**
 * @brief Q14: calcul la difference de deux multi-ensembles
 *
 * @param l1 multi-ensemble
 * @param l2 multi-ensemble
 * @return pointeur sur multi-ensemble
 */
Liste *difference (Liste l1, Liste l2);

#endif