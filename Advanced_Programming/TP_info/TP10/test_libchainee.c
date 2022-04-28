#include "listechaines.h"

int main(int argc, char *argv[])
{
    if (argc < 2) return EXIT_FAILURE;

    Liste list = NULL;
    FILE *fp = fopen(argv[1], "r");

    charge_fichier(fp, &list);
    afficher_liste(list);
    printf("The length of list is %d\n", taille(list));
    Liste p_tmp = list;
    for (int i = 0; i < 10; i++)
    {
        if (NULL == p_tmp) break;
        p_tmp = p_tmp->suiv;
    }
    printf("%s is %sin list\n", p_tmp->val, (appartient(list, p_tmp->val)==true)?"":"not ");
    printf("%s is %sin list\n", "saucisse", (appartient(list, "saucisse")==true)?"":"not ");

    detruire_liste(&list);

    return EXIT_SUCCESS;
}