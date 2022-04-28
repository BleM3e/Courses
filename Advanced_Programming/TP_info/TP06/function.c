#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 50

struct processus processus_null = {0,"",""};

/**
 * @brief Initialisation d'un ordonnanceur
 *
 * @param s Pointeur sur un ordonnanceur
 */
void init_sched (struct sched *s)
{
    for (int i = 0; i < TAILLE_PRIO; i++)
    {
        s->prio[i].t=NULL;
        s->prio[i].q=NULL;
    }
}

/**
 * @brief Fonction ajouter un processus à un ordonnanceur
 *
 * @param s Pointeur sur un ordonnanceur
 * @param processus Processus à ajouter
 * @param prio Priorité du processus
 */
void ajouter (struct sched *s, Proc processus, int prio)
{
    struct cell *p_cell = malloc(sizeof(struct cell));
    p_cell->processus   = processus;

    if (NULL == (s->prio[prio]).t)
    {
        p_cell->suiv = NULL;
        (s->prio[prio]).t = p_cell;
        (s->prio[prio]).q = p_cell;
    }
    else
    {
        p_cell->suiv              = ((s->prio[prio]).q)->suiv;
        ((s->prio[prio]).q)->suiv = p_cell;
        (s->prio[prio]).q         = p_cell;
    }
}

/**
 * @brief Fonction pour afficher le prochain processus à être exécuté
 *
 * @param s Ordonnanceur
 * @return Proc* Renvoie l'adresse du prochain processus à exécuté
 */
Proc *suivant (struct sched s)
{
    for (int i = 0; i < TAILLE_PRIO; i++)
    {
        if (s.prio[i].t != NULL) return &(s.prio[i].t->processus);
    }
    Proc *p_proc = malloc(sizeof(Proc));
    *p_proc = processus_null;
    return p_proc;
}

/**
 * @brief Remplissage d'un ordonnanceur à partir d'un fichier d'extension .csv
 *
 * @param nom_fichier Nom du fichier d'extension .csv
 * @param s Pointeur sur l'ordonnanceur à remplir
 */
void fill_file (char * nom_fichier, struct sched *s)
{
    FILE * f_p; //Pointeur de fichier
    char buff[TAILLE_BUFFER];

    int prio;

    Proc * processus = malloc(sizeof(Proc));

    f_p = fopen(nom_fichier,"r");

    fgets(buff,sizeof(buff),f_p);
    char *tok = strtok(buff,",");

    while (1)
    {
        if (fgets(buff,sizeof(buff),f_p) == NULL) break;
        tok = strtok(buff,",");
        processus->pid = atoi(tok);
        tok = strtok(NULL, ",");
        strcpy(processus->user,tok);
        tok = strtok(NULL, ",");
        prio = atoi(tok);
        tok = strtok(NULL, "\n");
        strcpy(processus->p_nom,tok);

        //printf("%d,%s\n",processus->pid,processus->p_nom);

        ajouter(s, *processus, prio);
    }
    free(processus);

    printf("Ajout effectuer!\n");

    fclose(f_p);
}

/**
 * @brief Fonction pour afficher les processus par priorité croissante
 *
 * @param s Ordonnanceur à afficher
 */
void afficher (struct sched s)
{
    struct cell *p_cell = NULL;

    for (int i = 0; i < TAILLE_PRIO; i++)
    {
        printf("Prio : %d\n",i);
        p_cell = s.prio[i].t;
        while (NULL != p_cell)
        {
            printf("%d,%s\n",p_cell->processus.pid,p_cell->processus.p_nom);
            p_cell = p_cell->suiv;
        }
    }
    printf("Affichage terminé !\n");
}

/**
 * @brief Fonction pour désallouer la mémoire alloué à l'ordonnanceur
 *
 * @param s Pointeur sur l'ordonnanceur à désallouer
 */
void desallouer (struct sched *s)
{
    struct cell *tmp_p = NULL;

    for (int i = 0; i < TAILLE_PRIO; i++)
    {
        while (NULL != s->prio[i].t)
        {
            tmp_p = s->prio[i].t->suiv;
            free(s->prio[i].t);
            s->prio[i].t = tmp_p;
        }
        s->prio[i].q=NULL;
    }
    printf("Libération mémoire effectué !\n");
}