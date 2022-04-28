/*
 * Source Code From Laure Gonnord, 2012
 * Adapted from Bernard Carre, 2011
 * Re-adapted by Walter Rudametkin in 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 *List library : reminder, the word have maximal size  MAXSIZE
 */
#include "listechaines.h"

/*
 *Size of the hashtables
 */
#define TABLE_SIZE 308

/*
 * Hash function
 */
int asciis(char *word)
{
	int i=0;
	int h=0;
	while(word[i]!='\0')
	{
		h=h+(word[i]-96);
		i++;
	}
	return h;
}

/*
 * Index function: hashes the word and returns a valid index
 */
int get_hashed_index(char *word)
{
	return (asciis(word) % TABLE_SIZE);
}



/****************************************
 *
 * TODO : write the following functions
 *
 ****************************************/

/*
 * Declaration of type Hashtable
 */
//!!! TODO: Wrong type, used only for compiling, please FIX!
typedef struct hash_t {
	Liste cell[TABLE_SIZE];
} *Hashtable;


/*
 * Initialisation of a given Hashtable
 */
void init_ht(Hashtable ht)
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		ht->cell[i] = NULL;
	}
}

/*
 * Update of the hashtable : add the given word in the table!
 */
void update_ht(char *word, Hashtable ht)
{
	ajout_alphab(&(ht->cell[get_hashed_index(word)]), word);
}

/*
 * Load the file in the internal structure ht
 */
void load_ht(FILE *fp, Hashtable ht)
{
    char word[MAXSIZE];

    // Count of element to read for each fscanf
    const int NB_TO_READ = 1;

    while (fscanf(fp ,"%s", word) == NB_TO_READ)
    {
        update_ht(word, ht);
    }

    //if (feof(fp))   printf("End of file, everything is fine\n");
    //if(ferror(fp))  printf("READING ERROR!\n");
}

/*
 * Count the collisions
 */
void collisions(Hashtable ht)
{
	Liste p_tmp = NULL;
	int count;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		p_tmp = ht->cell[i];
		count = 0;
		while (NULL != p_tmp)
		{
			count++;
			p_tmp = p_tmp->suiv;
		}
		printf("%d %d\n",i,count);
	}
}

void free_ht(Hashtable h)
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		detruire_liste(&(h->cell[i]));
	}
}

/*
 * Maximal hash of the words of the given file
 * returns max_word such that get_hashed_index(max_word)=hmax
 */
void max_hash(FILE *fp, char *max_word, int *hmax)
{
	char word[MAXSIZE];
	int tmp_h;

    // Count of element to read for each fscanf
    const int NB_TO_READ = 1;

    while (fscanf(fp ,"%s", word) == NB_TO_READ)
    {
		tmp_h = asciis(word);
        if (tmp_h > (*hmax))
		{
			*hmax = tmp_h;
			strcpy(max_word,word);
		}
    }
}



/*
 * Main function
 */
int main(int argc, char *argv[])
{
	//Guard clause: is text file is missing from parameter ?
	if (argc < 2)
	{
		fprintf(stderr, "usage: hash <file_name>\n");
		return EXIT_FAILURE;
	}

	FILE *fp, *a_fp;
	fp=fopen(argv[1], "r");
	a_fp=fopen(argv[1], "r");
	if (fp==NULL)
	{
		fprintf(stderr, "no such file, or unreachable: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	/*
	 * File is open, continue processing
	 */

	//Initial load using linked lists !
	/*Liste mylist = NULL;
	charge_fichier(fp,&mylist);
	afficher_liste(mylist); //For testing, print list
	detruire_liste(&mylist);*/


	//TODO !
	//replace by declaration and use of hashtables!

	Hashtable myHash = malloc(sizeof(struct hash_t));
	init_ht(myHash);
	load_ht(fp, myHash);
	collisions(myHash);
	free_ht(myHash);
	free(myHash);
	//TODO !
	char max_word[MAXSIZE];
	int hmax = 0;
	max_hash(a_fp, max_word, &hmax);
	printf("M_word : %s\thmax : %d\n", max_word, hmax);

	fclose(fp);
	fclose(a_fp);

	//printf("Finished\n");

	return EXIT_SUCCESS;
}

