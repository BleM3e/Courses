/*
 * This main source file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "main.c"
 * @brief   Main file which executes all procedures
 *          defined in "read_data.c", "hash_functions.c",
 *          "requests.c" & "menu.c" via the header file "menu.h"
 *          which contains the other header files :
 *          "data_structures.h", "hash_functions.h",
 *          "read_data.h" & "requests.h"
 * @date    Q2 2021
 * */


#include "../includes/menu.h"


int main ()
{
    printf ("\nOpening data files...\n");
    FILE *fp_airlines = fopen ("data/airlines.csv", "r");
    FILE *fp_airports = fopen ("data/airports.csv", "r");
    FILE *fp_flights  = fopen ("data/flights.csv", "r");

    if (fp_airlines == NULL || fp_airports == NULL || fp_flights == NULL)
    {
        printf ("\nERROR: program couldn't load the files !\n");
        printf ("Execution aborted...\n");
        exit (EXIT_FAILURE);
    }
    printf ("Opening done !\n\n");

    printf ("Initialization of data structures...\n");
    struct airline_cell *  al_list = NULL;
    struct airport_cell *  ap_list = NULL;
    Hashtab_ptr_flightcell hashtab_date;
    Hashtab_ptr_flightcell hashtab_airline;
    Hashtab_ptr_flightcell hashtab_dest;
    Hashtab_ptr_flightcell hashtab_dep;

    int nb_airlines = read_airlines (&al_list, fp_airlines);
    printf ("Number of airlines read: %d\n", nb_airlines);
    int nb_airports = read_airports (&ap_list, fp_airports);
    printf ("Number of airports read: %d\n", nb_airports);
    int nb_flights = read_flights (hashtab_date, hashtab_airline, hashtab_dest, hashtab_dep, fp_flights);
    printf ("Number of flights read: %d\n", nb_flights);
    printf ("Data structures are correctly initialized !\n\n");

    printf ("Closing data files...\n");
    fclose (fp_airlines);
    fclose (fp_airports);
    fclose (fp_flights);
    printf ("Data files are correctly closed !\n\n");

    print_airports (ap_list);

    init_message ();
    char *user_request = malloc (SIZE * sizeof (char));
    do
    {
        printf ("> ");
        while (scanf ("%[^\n]s", user_request) != 1)
        {
            empty_buffer ();
            printf ("> ");
        }
        reading_interpreting_request (user_request, al_list, ap_list, hashtab_date, hashtab_airline,
                                      hashtab_dest, hashtab_dep, nb_airlines, nb_airports, nb_flights);
        empty_buffer ();
    } while (strcmp (user_request, "quit") != 0);


    printf ("Erasing all data allocated by the program in RAM...\n");
    free (user_request);
    erase_data (hashtab_date, hashtab_airline, hashtab_dest, hashtab_dep, &al_list, &ap_list);
    printf ("All data allocated by the program in RAM have been successfully erased !\n\n");

    return 0;
}
