#include <stdbool.h>

/*
 * @brief Q1: définir la structure cellule et utiliser
 * un typedef pour définir Cellule et Liste
 */
typedef struct cellule_t
{
    int valeur;
    struct cellule_t * suivant;
} Cellule;

typedef Cellule *Liste;

/**
 * @brief Q2: Ajoute un element en tete de la liste
 *
 * @param val element a inserer
 * @param pL liste chainee
 */
void ajout_tete (int val, Liste *pL);

/**
 * @brief Q3: Affiche le contenu d'une liste chainee
 *
 * @param l liste chainee d'entiers
 */
void affiche_liste (Liste l);

/**
 * @brief Q4: Verifie si une liste est triee par ordre croissant
 *
 * @param l liste a verifier
 * @return 1 si triee, 0 sinon
 */
bool est_triee (Liste l);

/**
 * @brief Q5: Supprime l'element en tete d'une liste
 *
 * @param pL liste chainee
 */
void supprime_tete (Liste *pL);

/**
 * @brief Q6: Desalloue la liste -- libere la memoire
 *
 * @param pL liste a desallouer
 */
void desalloue_liste (Liste *pL);

/**
 * @brief Q8: Ajout un element dans une liste triée
 *
 * @param val element a inserer
 * @param pL liste chainee
 */
void ajout_dans_liste_triee (int val, Liste *pL);

/**
 * @brief Q9: Crée une liste à partir d'un fichier contenant des entiers
 *
 * @param nom_fichier nom du fichier contenant des entiers (1 par ligne)
 * @param pL liste chainee
 */
void cree_liste_fichier (char nom_fichier[], Liste *pL);

/**
 * @brief Q10: Verifie si une liste contient des doublons
 *
 * @param l liste a verifier
 * @return 1 si doublons, 0 sinon
 */
bool contient_doublons (Liste l);

/**
 * @brief Q11: Union de deux listes
 *
 * @param l1 première liste
 * @param l2 deuxième liste
 * @return ptr sur la liste résultante
 */
Liste union_ensemble (Liste l1, Liste l2);

/**
 * @brief Q12: Intersection de deux listes
 *
 * @param l1 première liste
 * @param l2 deuxième liste
 * @return ptr sur la liste résultante
 */
Liste intersection_ensemble (Liste l1, Liste l2);

/**
 * @brief Q13: Transformation liste vers ensemble
 *
 * @param pL pointeur sur une liste
 */
void liste_vers_ensemble (Liste *pL);
