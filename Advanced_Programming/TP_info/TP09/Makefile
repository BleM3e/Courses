### Variables generiques
CC=clang# compilateur
CFLAGS=-I. -W -Wall -g -MMD# warning + dependances
EXTRA_CFLAGS=

### Variables liées à la compilation des sources
SRC=$(wildcard *.c)		# Tous les fichiers .c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

### Cibles de compilation
default: main clean

### Construction des executables
main: main.o
	$(CC) $^ $(CFLAGS)

exemple: getline_expl.o
	$(CC) $^ $(CFLAGS) -o getline_expl

test_memoire:
	valgrind -s ./getline_expl

clean:
	rm -f $(OBJ) $(DEP) getline_expl

### Construction generique des fichiers .o
.c.o:
		$(CC) $(CFLAGS) -c $<

### Inclusion des dependances
-include $(DEP)