# Projet de Programmation Avancée (SE3 - 2020/2021)

Ce dépôt `GIT` contient les livrables de Clément KOPERSKI et Sami AGGAR pour le projet de Programmation Avancée du Semestre 6 de la filière Systèmes Embarqués de Polytech Lille.
Le but de ce tutorat est de réaliser une application codée en langage C, permettant à un utilisateur de réaliser des requêtes qui interrogent une base de données contenant les
informations de 58492 vols intranationaux qui ont eu lieu aux Etats-Unis en 2014.


## CONTENU 

Ce dépôt contient à la racine différents répertoires dans lesquels se trouvent les fichiers nécessaires à la réalisation du programme, ces répertoires sont les suivants:
* __src:__ fichiers sources (.c) 
     * hash_functions.c: fonctions de hachages + procedure de test (hash_test)
     * read_data.c: lecture des données des fichiers csv + stockage dans les structures de données + procédures d'affichage générique
     * requests.c: procédures permettant de réaliser l'action de chacune des requêtes formulées par l'utilisateur
     * menu.c: interface utilisateur + fonctions de manipulation de chaînes de caractères
     * main.c: ouverture/fermeture des fichiers csv + appel aux fonctions de lecture + interaction avec les requêtes utilisateur + libération espace mémoire 
* __includes:__ fichiers header (.h)
     * data_structures.h: inclusion des librairies standard + définition des constantes + définition des structures de données
     * hash_functions.h: prototypes des procédures de hachage
     * read_data.h: prototypes des procédures de lecture/affichage des données
     * requests.h: prototypes des procédures des requêtes
     * menu.h: prototypes des procédures d'interprétation des requêtes utilisateur
* __data:__
     * LICENSE: certification de libre accès aux données
     * airlines.csv: données des compagnies aériennes
     * airports.csv: données des aéroports
     * flights.csv: données des vols
     * requetes.txt: batterie de requêtes tests
* D'autres fichiers se trouvent à la racine:
     * __Makefile:__ fichier établissant les règles de compilation
     * __Rapport.pdf:__ compte-rendu au format PDF faisant part de nos réflexions sur l'architecture du programme
     * __README.md:__ fichier que vous êtes actuellement en train de lire !
     * __.clang-format:__ fichier établissant les règles de formatage du code C (mis à disposition par M. DEQUIDT)


## COMPILATION

La compilation de notre programme est pleinement automatisée grâce au Makefile. Le compilateur utilisé est `gcc` avec les options `-g -W -Wall -Wextra -O2`.
Le Makefile utilise des variables internes, des règles de compilation et des commandes bash.

La commande `make` initie les étapes de compilation suivantes:
   * Création des deux répertoires __bin__ et __obj__ qui contiendront respectivement l'exécutable et les fichiers objets (.o) 
   * Génération des fichiers objets (obj/\*.o) à partir des fichiers sources (src/\*.c)
   * Production de l'exécutable (bin/project) à partir des fichiers objets (obj/\*.o)

La commande `make clean` réalise les actions suivantes:
   * Suppression des fichiers objets (obj/\*.o)
   * Suppression du binaire (bin/project)
   * Suppression des dossiers __bin__ et __obj__

Après avoir récupéré une copie de notre dépôt `GIT`, il faut exécuter la commande `make` à la racine pour générer l'exécutable.
La commande `make clean` permet de supprimer les fichiers compilés.


## UTILISATION DU PROGRAMME

Pour exécuter le programme en interagissant manuellement avec lui, il suffit d'entrer la commande `./bin/project` à la racine.
Pour exécuter le programme avec redirection de l'entrée standard, il suffit d'entrer la commande `./bin/project < data/requetes.txt` à la racine.

Le fonctionnement du programme est cyclique et il exécute les étapes suivantes:
1. Charger le fichier de données
2. Attendre une commande
3. Traiter la commande
4. Afficher le résultat de cette commande
5. Revenir à l'étape 2

Les requêtes renseignables sont les suivantes:

- `show-airports <airline_id>` : affiche tous les aéroports depuis lesquels la compagnie aérienne <airline_id> opère des vols
- `show-airlines <port_id>` : affiche les compagnies aériens qui ont des vols qui partent de l'aéroport <port_id>
- `show-flights <port_id> <date> [<time>] [limit=<xx>]` : affiche les vols qui partent de l'aéroport à la date, avec optionnellement une heure de début, et limité à xx vols
- `most-delayed-flights` : donne les 5 vols qui ont subis les plus longs retards à l'arrivée
- `most-delayed-airlines` : donne les 5 compagnies aériennes qui ont, en moyenne, le plus de retards
- `delayed-airline <airline_id>` : donne le retard moyen de la compagnie aérienne passée en paramètre
- `most-delayed-airlines-at-airport <airport_id>` : donne les 3 compagnies aériennes avec le plus de retard d'arrivé à l'aéroport passée en paramètre
- `changed-flights <date>` : les vols annulés ou déviés à la date  (format M-D)
- `avg-flight-duration <port_id> <port_id>` : calcule le temps de vol moyen entre deux aéroports
- `find-itinerary <port_id> <port_id> <date> [<time>] [limit=<xx>]` : trouve un ou plusieurs itinéraires entre deux aéroports à une date donnée (l'heure est optionnel, requête peut être limité à xx propositions, il peut y avoir des escales)
- `help` : affiche la liste des requêtes valides
- `quit` : quitte le programme

Pour information, les paramètres entre crochets `[ ]` sont optionnels et les paramètres entre `< >` indiquent une valeur à renseigner.
Les dates sont au format `M-J` et l'heure `HHMM`.

Le programme est permissif en cas de commande invalide. Cependant, dès qu'une commande valide est rensignée, il faut veiller à entrer les arguments dans le même ordre que celui indiqué ci-dessus.
Chaque fichier `.txt` utilisé dans la redirection de l'entrée standard doit se terminer par la requête `quit` (permet d'assurer une exécution conforme).





    

     

 
