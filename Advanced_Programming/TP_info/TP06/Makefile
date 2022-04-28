### Variables generiques
CC=clang # compilateur
CFLAGS=-I. -W -Wall -g -MMD -std=c99 # warning + dependances
EXTRA_CFLAGS=

### Variables liées à la compilation des sources
EXEC=./a.out
SRC=$(wildcard *.c)		# Tous les fichiers .c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

### Cibles de compilation
default: $(EXEC)

### Construction des executables
$(EXEC): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

### Construction generique des fichiers .o
.c.o:
		$(CC) $(CFLAGS) -c $<

### Inclusion des dependances
-include $(DEP)
