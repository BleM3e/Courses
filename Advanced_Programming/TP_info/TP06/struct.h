#ifndef __STRUCT_H__
#define __STRUCT_H__

#define TAILLE_NOM 30
#define TAILLE_PRIO 41

typedef struct processus {
    int pid;
    char p_nom[TAILLE_NOM];
    char user[TAILLE_NOM];
} Proc;

struct cell {
    Proc processus;
    struct cell *suiv;
};

struct file_prio {
    struct cell *t;
    struct cell *q;
};

struct sched {
    struct file_prio prio[TAILLE_PRIO];
};

#endif