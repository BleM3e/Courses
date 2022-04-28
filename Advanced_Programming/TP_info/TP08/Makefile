### Variables generiques
CC=clang# compilateur
CFLAGS=-I. -W -Wall -g -MMD -std=c99# warning + dependances
EXTRA_CFLAGS=

### Variables liées à la compilation des sources

### Cibles de compilation
default: clean

### Construction des executables
exo1: exo1.o
	$(CC) $^ $(CFLAGS) -o $@

exo2: exo2.o
	$(CC) $^ $(CFLAGS) -o $@

exo3: exo3.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f *.o *.d exo1 exo2 exo3

### Construction generique des fichiers .o
.c.o:
		$(CC) $(CFLAGS) -c $<

### Inclusion des dependances
-include $(DEP)