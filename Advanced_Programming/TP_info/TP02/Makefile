### Variables generiques
CC=clang # compilateur
CFLAGS=-I. -W -Wall -g -MMD # warnings + dependances
EXTRA_CFLAGS= # aucune pour ce TP
EXTRA_LDFLAGS=# aucune pour ce TP

### Variables liées à la compilation des sources
EXEC=structures		# ./structures pour executer
SRC=reponse.c main.c# pas tous les .c cf question 10
OBJ=$(SRC:.c=.o)	# *.c --> *.o
DEP=$(SRC:.c=.d)	# *.c --> *.d

### Cibles de compilation
default: $(EXEC)

#### Construction de l'executable
$(EXEC): $(OBJ)
	$(CC) $^ $(EXTRA_LDFLAGS) -o $@

#### Construction generique des fichiers .o
#.c.o:
#	$(CC) $(CFLAGS) -c $<
#	ne fonctionne pas à cause de la question 10
reponse.o: reponse.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

### Inclusion des dependances
-include $(DEP)

### Nettoyage du repertoire
.PHONY: clean
clean:
	@rm -rf $(EXEC) $(OBJ) $(DEP)
