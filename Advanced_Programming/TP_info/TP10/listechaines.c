#include "listechaines.h"

//Affichage de la liste en ligne
void afficher_liste(struct cell *list)
{
    while (NULL != list)
    {
        printf("%s\n",list->val);
        list = list->suiv;
    }
}

//Ajout d'un mot en tete de la liste
void ajout_tete(struct cell **p_list, char *word)
{
    Liste p_tmp = malloc(sizeof(Cellule));
    strcpy(p_tmp->val,word);
    p_tmp->suiv = *p_list;
    *p_list = p_tmp;
}

//Suppression du mot en tete de la liste
void supp_tete(struct cell **p_list)
{
    if (NULL != *p_list)
    {
        Liste p_tmp = *p_list;
        *p_list = (*p_list)->suiv;
        free(p_tmp);
    }
    else perror("Want to free a NULL pointer");
}

//Ajout un mot dans une liste supposee
// triee dans l'ordre alphabetique
void ajout_alphab(struct cell **p_list, char *word)
{   // Empty List or word < next_word, then add the word
    if ((NULL == *p_list) || (strcmp(word, (*p_list)->val) < 0))
    {
        ajout_tete(p_list,word);
    }
    else
    {
        // word > next_word, then search with the next_next_word
        if (strcmp(word, (*p_list)->val) > 0)
        {
            ajout_alphab(&(*p_list)->suiv, word);
        }
        // else (== 0) the word is already in the list, no duplicate?
    }
}

//Dit si un mot donne est dans la liste
//pas forcement triee
bool appartient(struct cell *list, char *word)
{
    while (NULL != list)
    {
        if (strcmp(word, list->val) == 0) return true;
        list = list->suiv;
    }
    return false;
}

//Donne la taille de la liste.
int taille(struct cell *list)
{
    int size = 0;
    while (NULL != list)
    {
        size++;
        list = list->suiv;
    }
    return size;
}

//construit une liste triee a partir d'un fichier
void charge_fichier(FILE *fp, struct cell **p_list)
{
    char word[MAXSIZE];

    // Count of element to read for each fscanf
    const int NB_TO_READ = 1;

    while (fscanf(fp ,"%s", word) == NB_TO_READ)
    {
        ajout_alphab(p_list, word);
    }

    if (feof(fp))   printf("End of file, everything is fine\n");
    if(ferror(fp))  printf("READING ERROR!\n");
}

//Destruction de Liste.
void detruire_liste(struct cell **p_list)
{
    while (NULL != *p_list)
    {
        supp_tete(p_list);
    }
}