### Starting Template of Makefile
### Variables generiques
CC=clang# compilateur
FLAGS=-W -Wall -g -MMD# warning + dependances
EXTRA_CFLAGS=

### Variables liées à la compilation des sources
SRC=$(wildcard *.c)		# Tous les fichiers .c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

### Cibles de compilation


### Construction des executables


### Construction generique des fichiers .o
.c.o:
	$(CC) $(FLAGS) -c $<

### Inclusion des dependances
-include $(DEP)
