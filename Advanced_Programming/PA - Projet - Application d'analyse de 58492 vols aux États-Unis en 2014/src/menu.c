/*
 * This source file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "menu.c"
 * @brief   Source file which contains all procedures
 *          for the menu of our small flights datas scanning app
 *          via the header files: "data_structures.h"
 *          "read_data.h", "hash_functions.h" & "requests.h" &
 *          "menu.h".
 * @date    Q2 2021
 * */


#include "../includes/menu.h"


void init_message ()
{
    printf ("\n\n"
            "------------------------------------------------------------\n"
            "||          WELCOME TO OUR DATABASE APPLICATION           ||\n"
            "||                                                        ||\n"
            "||  which lists the 58492 flights that took place in the  ||\n"
            "||            United States of America in 2014            ||\n"
            "------------------------------------------------------------\n\n\n");

    help_message ();
}


void help_message ()
{
    printf ("Here are the valid requests that you can enter:\n"
            "> show-airports <airline_id>\n"
            "> show-airlines <airport_id>\n"
            "> show-flights <airport_id> <date> [<time>] [limit=<xx>]\n"
            "> most-delayed-flights\n"
            "> most-delayed-airlines\n"
            "> delayed-airline <airline_id>\n"
            "> most-delayed-airlines-at-airport <airport_id>\n"
            "> changed-flights <date>\n"
            "> avg-flight-duration <airport_id> <airport_id>\n"
            "> find-itinerary <airport_id> <airport_id> <date> [<time>] [limit=<xx>]\n"
            "> help\n"
            "> quit\n\n"
            "Note 1: the parameters between square brackets '[]' are optional and the parameters "
            "between rafters '<>' indicate a value that the user must fill\n"
            "Note 2: Dates are in MONTH-DAY format and time is in HHMM format\n\n");
}


// Action necessary to be called before some scanf(), in order to empty the buffer and allow the normal execution of scanf(). Often useful in loops 'while':
void empty_buffer ()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar ();
    }
}


// Function which returns the first word of a string (all characters before the FIRST 'space') & which moves the character pointer to the second word:
char *isolate_first_word (char **ptr_str)
{
    if (*ptr_str == NULL) return NULL;

    int   i          = 1;
    char *first_word = malloc (i * sizeof (char));
    while (*ptr_str != NULL && **ptr_str != '\0' && **ptr_str != ' ')
    {
        i++;
        first_word        = realloc (first_word, i * sizeof (char));
        first_word[i - 2] = **ptr_str;
        (*ptr_str)++;
    }
    first_word[i - 1] = '\0';

    while (**ptr_str == ' ') (*ptr_str)++;

    return first_word;
}


// Procedure which creates two strings : month (MM) & day (DD) from the date in format MM-DD or MM_DD:
void date_decomposition (char **ptr_month, char **ptr_day, char *date)
{
    if (date == NULL) return;

    int i = 0;
    while (date != NULL && *date != '\0' && *date != '-' && *date != '_')
    {
        (*ptr_month)[i] = *date;
        i++;
        date++;
    }
    (*ptr_month)[i] = '\0';
    date++;

    i = 0;
    while (date != NULL && *date != '\0')
    {
        (*ptr_day)[i] = *date;
        i++;
        date++;
    }
    (*ptr_day)[i] = '\0';
}


void reading_interpreting_request (char *                 user_request,
                                   struct airline_cell *  al_list,
                                   struct airport_cell *  ap_list,
                                   Hashtab_ptr_flightcell hashtab_date,
                                   Hashtab_ptr_flightcell hashtab_airline,
                                   Hashtab_ptr_flightcell hashtab_dest,
                                   Hashtab_ptr_flightcell hashtab_dep,
                                   int                    nb_airlines,
                                   int                    nb_airports,
                                   int                    nb_flights)
{
    if (user_request == NULL || strlen (user_request) < 4)
    {
        printf ("Invalid input ! Please try with a valid command (tip: enter 'help' for the "
                "requests list)\n\n");
        return;
    }

    if (strcmp (user_request, "quit") == 0)
    {
        printf ("Exiting the program...\n\n");
        return;
    }

    if (strcmp (user_request, "help") == 0)
    {
        help_message ();
        return;
    }

    if (strcmp (user_request, "most-delayed-flights") == 0)
    {
        most_delayed_flights (hashtab_airline);
        return;
    }

    if (strcmp (user_request, "most-delayed-airlines") == 0)
    {
        most_delayed_airlines (hashtab_airline, al_list, nb_airlines);
        return;
    }


    char *command        = isolate_first_word (&user_request);
    char *airline_id     = NULL;
    char *airport_id     = NULL;
    char *airport_id_bis = NULL;
    char *date           = NULL;
    char *month_str      = malloc (3 * sizeof (char));
    char *day_str        = malloc (3 * sizeof (char));
    int   month, day;
    char *time_str  = NULL;
    int   time      = 0;
    char *limit_str = NULL;
    char *limit_tmp = NULL;
    int   limit     = nb_flights;

    if (*user_request == '\0')
        printf ("Invalid input ! Please try with a valid command (tip: enter 'help' for the "
                "requests list)\n\n");

    else if (strcmp (command, "show-airports") == 0)
    {
        airline_id = isolate_first_word (&user_request);
        show_airports (airline_id, hashtab_airline, ap_list, nb_airports);
    }

    else if (strcmp (command, "show-airlines") == 0)
    {
        airport_id = isolate_first_word (&user_request);
        show_airlines (airport_id, hashtab_dep, al_list, nb_airlines);
    }

    else if (strcmp (command, "show-flights") == 0)
    {
        airport_id = isolate_first_word (&user_request);
        date       = isolate_first_word (&user_request);
        date_decomposition (&month_str, &day_str, date);
        month = atoi (month_str);
        day   = atoi (day_str);
        if (*user_request != '\0')
        {
            time_str = isolate_first_word (&user_request);
            time     = atoi (time_str);
        }
        if (*user_request != '\0')
        {
            limit_str = isolate_first_word (&user_request);
            limit_tmp = strchr (limit_str, '=') + sizeof (char); // Skip 'limit=' to only keep the limitation number
            limit     = atoi (limit_tmp);
        }
        show_flights (airport_id, month, day, hashtab_date, time, limit);
    }

    else if (strcmp (command, "delayed-airline") == 0)
    {
        airline_id = isolate_first_word (&user_request);
        delayed_airline (airline_id, hashtab_airline, al_list, YES);
    }

    else if (strcmp (command, "most-delayed-airlines-at-airport") == 0)
    {
        airport_id = isolate_first_word (&user_request);
        most_delayed_airlines_by_airport (airport_id, hashtab_dest, al_list, nb_airlines);
    }

    else if (strcmp (command, "changed-flights") == 0)
    {
        date = isolate_first_word (&user_request);
        date_decomposition (&month_str, &day_str, date);
        month = atoi (month_str);
        day   = atoi (day_str);
        changed_flights (month, day, hashtab_date);
    }

    else if (strcmp (command, "avg-flight-duration") == 0)
    {
        airport_id     = isolate_first_word (&user_request);
        airport_id_bis = isolate_first_word (&user_request);
        avg_flight_duration (airport_id, airport_id_bis, hashtab_dep);
    }

    else if (strcmp (command, "find-itinerary") == 0)
    {
        airport_id     = isolate_first_word (&user_request);
        airport_id_bis = isolate_first_word (&user_request);
        date           = isolate_first_word (&user_request);
        date_decomposition (&month_str, &day_str, date);
        month = atoi (month_str);
        day   = atoi (day_str);
        if (*user_request != '\0')
        {
            time_str = isolate_first_word (&user_request);
            time     = atoi (time_str);
        }
        if (*user_request != '\0' && *user_request == 'l')
        {
            limit_str = isolate_first_word (&user_request);
            limit_tmp = strchr (limit_str, '=') + sizeof (char); // Skip 'limit=' to only keep the limitation number
            limit     = atoi (limit_tmp);
        }
        find_itinerary (airport_id, airport_id_bis, month, day, hashtab_date, time, ap_list, limit);
    }

    else
        printf ("Invalid input ! Please try with a valid command (tip: enter 'help' for the "
                "requests list)\n\n");

    free (command);
    free (airline_id);
    free (airport_id);
    free (airport_id_bis);
    free (date);
    free (month_str);
    free (day_str);
    free (time_str);
    free (limit_str);
}
