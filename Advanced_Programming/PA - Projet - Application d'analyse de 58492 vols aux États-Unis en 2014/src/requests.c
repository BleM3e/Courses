/*
 * This source file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "requests.c"
 * @brief   Source file which contains all procedures
 *          for the requests of our small flights datas scanning app
 *          via the header files: "data_structures.h"
 *          "read_data.h", "hash_functions.h" & "requests.h".
 * @date    Q2 2021
 * */


#include "../includes/requests.h"


/*The procedures below are necessary/useful for the majority of the requests*/
void adding_head_flight (struct flight_cell **ptr_flights_list, struct flight elem, int type)
{
    struct flight_cell *newcell = malloc (sizeof (struct flight_cell));
    init_flight_cell (&newcell);
    if (newcell == NULL) /* Testing if memory is full */
        return exit (EXIT_FAILURE);

    newcell->val = elem;
    switch (type)
    {
    case DATE:
        newcell->next_date = *ptr_flights_list;
        break;

    case AIRLINE:
        newcell->next_airline = *ptr_flights_list;
        break;

    case DEST_AIRPORT:
        newcell->next_dest_airport = *ptr_flights_list;
        break;

    case DEP_AIRPORT:
        newcell->next_dep_airport = *ptr_flights_list;
        break;
    }

    *ptr_flights_list = newcell;
}


void erase_flights_list (struct flight_cell **ptr_flights_list, int type)
{
    if (*ptr_flights_list == NULL) return;
    struct flight_cell *tmp = *ptr_flights_list;
    switch (type)
    {
    case DATE:
        while ((*ptr_flights_list) != NULL)
        {
            tmp               = *ptr_flights_list;
            *ptr_flights_list = ((*ptr_flights_list)->next_date);
            free (tmp);
        }
        break;

    case AIRLINE:
        while ((*ptr_flights_list) != NULL)
        {
            tmp               = *ptr_flights_list;
            *ptr_flights_list = ((*ptr_flights_list)->next_airline);
            free (tmp);
        }
        break;

    case DEST_AIRPORT:
        while ((*ptr_flights_list) != NULL)
        {
            tmp               = *ptr_flights_list;
            *ptr_flights_list = ((*ptr_flights_list)->next_dest_airport);
            free (tmp);
        }
        break;

    case DEP_AIRPORT:
        while ((*ptr_flights_list) != NULL)
        {
            tmp               = *ptr_flights_list;
            *ptr_flights_list = ((*ptr_flights_list)->next_dep_airport);
            free (tmp);
        }
        break;
    }
}


void erase_airlines_list (struct airline_cell **ptr_airlines_list)
{
    if (*ptr_airlines_list == NULL) return;
    struct airline_cell *tmp = *ptr_airlines_list;
    while ((*ptr_airlines_list) != NULL)
    {
        tmp                = *ptr_airlines_list;
        *ptr_airlines_list = ((*ptr_airlines_list)->next);
        free (tmp);
    }
}


void erase_airports_list (struct airport_cell **ptr_airports_list)
{
    if (*ptr_airports_list == NULL) return;
    struct airport_cell *tmp = *ptr_airports_list;
    while ((*ptr_airports_list) != NULL)
    {
        tmp                = *ptr_airports_list;
        *ptr_airports_list = ((*ptr_airports_list)->next);
        free (tmp);
    }
}


void erase_data (Hashtab_ptr_flightcell hashtab_date,
                 Hashtab_ptr_flightcell hashtab_airline,
                 Hashtab_ptr_flightcell hashtab_dest_airport,
                 Hashtab_ptr_flightcell hashtab_dep_airport,
                 struct airline_cell ** ptr_airlines_list,
                 struct airport_cell ** ptr_airports_list)
{
    for (int i = 0; i < SIZE; i++)
    {
        struct flight_cell *tmp = hashtab_airline[i];
        erase_flights_list (&tmp, AIRLINE);
    }
    init_hash_table (hashtab_date);
    init_hash_table (hashtab_airline);
    init_hash_table (hashtab_dest_airport);
    init_hash_table (hashtab_dep_airport);

    erase_airlines_list (ptr_airlines_list);
    erase_airports_list (ptr_airports_list);
}


/*The procedures below are necessary for the majority of the request show-airports*/
int adding_airports_withoutduplicate (struct airport_cell **ptr_airports_list, struct airport elem) /*This procedure add airport to an airport linked list without any duplication*/
{

    struct airport_cell *newcell = malloc (sizeof (struct airport_cell));
    if (newcell == NULL) /* Testing if memory is full */
        exit (EXIT_FAILURE);
    struct airport_cell *tmp = *ptr_airports_list;
    if (tmp == NULL)
    {
        adding_head_airport (ptr_airports_list, elem);
        free (newcell);
        return 0;
    }
    int cpt = 0;
    while (tmp != NULL)
    {
        cpt++;
        tmp = tmp->next;
    }
    tmp = *ptr_airports_list;
    while (tmp->next != NULL && strcmp (tmp->val.iata_code, elem.iata_code) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp (tmp->val.iata_code, elem.iata_code) == 0)
    {
        free (newcell);
        return cpt;
    }
    newcell->val  = elem;
    newcell->next = NULL;
    tmp->next     = newcell;
    return cpt;
}


void show_airports (char iata_airline[], Hashtab_ptr_flightcell hashtab_airline, struct airport_cell *apl, int nb_airports)
{
    struct airport_cell *dep_airports = NULL;
    struct flight_cell * fl           = hashtab_airline[hash_function_airline (iata_airline)];
    struct airport_cell *tmp          = apl;
    int                  cpt          = 0;
    if (fl == NULL || apl == NULL)
    {
        printf ("No flight or airport found !\n\n"); /*Checking if the flight list and the airport list are empty*/
        return;
    }
    while (fl != NULL) /*Adding each airport from where the airline choosed by the user has plane taking off*/
    {

        // if (strcmp (fl->val.airline, iata_airline) == 0){
        while (tmp != NULL)
        {
            if (strcmp (tmp->val.iata_code, fl->val.org_air) == 0 ||
                strcmp (tmp->val.iata_code, fl->val.dest_air) == 0)
            {
                cpt = adding_airports_withoutduplicate (&(dep_airports), tmp->val); /*the variable cpt ables to stop the research when all the airport have been found*/
                if (cpt == nb_airports) break;
            }
            tmp = tmp->next;
        }

        if (cpt == nb_airports) break;
        tmp = apl;
        fl  = fl->next_airline;
    }

    print_airports (dep_airports); /*printing and erasing the linked list that contains the result*/
    printf ("\n");
    erase_airports_list (&dep_airports);
}


/*The procedures below are necessary for the request: show-airlines*/
int adding_airline_without_duplicate (struct airline_cell **airline_list_result, struct airline elem) /*this procedure add an airline to an airline linked list without duplication*/
{
    if (*airline_list_result == NULL)
    {
        adding_head_airline (airline_list_result, elem);
        return 1;
    }
    int                  cpt = 0;
    struct airline_cell *tmp = *airline_list_result;
    while (tmp != NULL)
    {
        cpt++;
        tmp = tmp->next;
    }
    tmp = *airline_list_result;
    while (tmp->next != NULL && strcmp (tmp->val.iata_code, elem.iata_code) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp (tmp->val.iata_code, elem.iata_code) == 0) return cpt;
    struct airline_cell *newcell = malloc (sizeof (struct airline_cell));
    newcell->val                 = elem;
    newcell->next                = tmp->next;
    tmp->next                    = newcell;
    return cpt;
}


void show_airlines (char dep[], Hashtab_ptr_flightcell hashtab_dep, struct airline_cell *airline_list, int nb_airlines)
{
    struct flight_cell * tmp    = hashtab_dep[hash_function_dest_and_dep (dep)];
    struct airline_cell *result = NULL;
    struct airline_cell *search = NULL;
    int                  cpt    = 0;
    /*Verifyin if the flight list and the airline list are empty*/
    if (tmp == NULL || airline_list == NULL)
    {
        printf ("No flight or airline found !\n\n");
        return;
    }
    /*Adding to a airline linked list all the airline that have flights taking off from the airport entered by the user*/
    while (tmp != NULL)
    {
        if (nb_airlines == cpt) break;
        search = airline_list;
        while (search != NULL)
        {
            if (strcmp (tmp->val.airline, search->val.iata_code) == 0)
            {
                cpt = adding_airline_without_duplicate (&result, search->val); /*the var cpt is used to check if all the airports have been found, if it is the case the research will stop*/
            }
            search = search->next;
        }
        tmp = tmp->next_dep_airport;
    }

    print_airlines (result); /*printing then erasing the airline linked list that contains the result*/
    printf ("\n");
    erase_airlines_list (&result);
}


/*The procedures below are necessary for the request: show-flights*/
void show_flights (char dep[], unsigned char month, unsigned char day, Hashtab_ptr_flightcell hashtab_date, int time, int limit)
{
    struct flight_cell *flight_list = hashtab_date[hash_function_date (month, day)];
    if (flight_list == NULL)
    {
        printf ("No flight found !\n\n");
        return;
    }
    int                 cpt    = 0;
    struct flight_cell *result = NULL;

    /*The following test are made to cover all the possibilities offered to the user in term of parameters that he has to enter (limit or not, time or not)*/
    if (limit > 0 && time >= 0)
    {
        while (flight_list != NULL && cpt < limit)
        {
            if (strcmp (flight_list->val.org_air, dep) == 0 && flight_list->val.sched_dep > time)
            {
                adding_head_flight (&result, flight_list->val, DATE);
                cpt++;
            }
            flight_list = flight_list->next_date;
        }
    }
    if (limit <= 0 && time >= 0)
    {
        while (flight_list != NULL)
        {
            if (strcmp (flight_list->val.org_air, dep) == 0 && flight_list->val.sched_dep > time)
            {
                adding_head_flight (&result, flight_list->val, DATE);
            }
            flight_list = flight_list->next_date;
        }
    }
    if (limit > 0 && time < 0)
    {
        while (flight_list != NULL && cpt < limit)
        {
            if (strcmp (flight_list->val.org_air, dep) == 0)
            {
                adding_head_flight (&result, flight_list->val, DATE);
                cpt++;
            }
            flight_list = flight_list->next_date;
        }
    }
    if (limit <= 0 && time < 0)
    {
        while (flight_list != NULL)
        {
            if (strcmp (flight_list->val.org_air, dep) == 0)
            {
                adding_head_flight (&result, flight_list->val, DATE);
            }
            flight_list = flight_list->next_date;
        }
    }

    print_flights (result, DATE);
    printf ("\n");
    erase_flights_list (&result, DATE);
}


/*The procedures below are necessary for the request: most-delayed-flights*/
void adding_ordonate (struct flight_cell **ptr_flights_list, struct flight elem)
{
    if (*ptr_flights_list == NULL)
    {
        adding_head_flight (ptr_flights_list, elem, 2);
        return;
    }
    int                 max = 0;
    struct flight_cell *tmp = *ptr_flights_list;
    while (tmp != NULL)
    {
        max++;
        tmp = tmp->next_airline;
    }
    tmp = *ptr_flights_list;
    if (max < 5)
    {
        if (tmp->val.arr_delay > elem.arr_delay)
        {
            adding_head_flight (ptr_flights_list, elem, 2);
            return;
        }
        while (tmp->next_airline != NULL && (tmp->next_airline->val.arr_delay < elem.arr_delay))
        {
            tmp = tmp->next_airline;
        }

        struct flight_cell *new = malloc (sizeof (struct flight_cell));
        init_flight_cell (&new);
        new->val = elem;
        if (tmp->next_airline == NULL && tmp->val.arr_delay < elem.arr_delay)
        {
            new->next_airline = NULL;
            tmp->next_airline = new;
            return;
        }
        new->next_airline = tmp->next_airline;
        tmp->next_airline = new;
        return;
    }
    else
    {
        if (tmp->val.arr_delay > elem.arr_delay) return;
        while (tmp->next_airline != NULL && (tmp->next_airline->val.arr_delay < elem.arr_delay))
        {
            tmp = tmp->next_airline;
        }
        struct flight_cell *new = malloc (sizeof (struct flight_cell));
        init_flight_cell (&new);
        new->val = elem;
        if (tmp->next_airline == NULL) // && tmp->val.arr_delay < elem.arr_delay)
        {
            new->next_airline = NULL;
            tmp->next_airline = new;
        }
        else
        {
            new->next_airline = tmp->next_airline;
            tmp->next_airline = new;
        }
        struct flight_cell *erase = *ptr_flights_list;
        *ptr_flights_list         = (*ptr_flights_list)->next_airline;
        free (erase);
        return;
    }
}


void most_delayed_flights (Hashtab_ptr_flightcell hashtab_airline)
{
    struct flight_cell *result = NULL;
    struct flight_cell *tmp    = NULL;
    for (int i = 0; i < SIZE; i++)
    {
        tmp = hashtab_airline[i];
        while (tmp != NULL)
        {
            adding_ordonate (&result, tmp->val);
            tmp = tmp->next_airline;
        }
        i++;
    }

    print_flights (result, 2);
    printf ("\n");
    erase_flights_list (&result, 2);
}


/*The procedures below are necessary for the requests: delayed-airline & most-delayed-airlines*/
int delayed_airline (char iata_airline[], Hashtab_ptr_flightcell hashtab_airline, struct airline_cell *all, int print)
{
    int                 delay = 0;
    char                airline_name[50];
    int                 nb_flights = 0;
    struct flight_cell *fl         = hashtab_airline[hash_function_airline (iata_airline)];

    if (fl == NULL || all == NULL)
    {
        exit (EXIT_FAILURE);
    }

    while (fl != NULL)
    {
        if (strcmp (iata_airline, fl->val.airline) == 0) //&& //(fl->val.arr_delay >= 0))
        {
            delay += fl->val.arr_delay;
            nb_flights++;
        }

        fl = fl->next_airline;
    }
    if (print == 1)
    {
        while (all != NULL)
        {
            if (strcmp (iata_airline, all->val.iata_code) == 0)
            {
                strcpy (airline_name, all->val.airline_name);
            }
            all = all->next;
        }

        printf ("%s(%s) has approximately %dmin of delay on each flight.\n\n", airline_name,
                iata_airline, delay / nb_flights);
    }
    return (int)(delay / nb_flights);
}


void sort_delayed_airlines (struct airline_with_delay tab[], int size)
{
    struct airline_with_delay tmp;
    // for (int i = size; i > 1; i--)
    for (int i = 1; i <= size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (tab[j + 1].delay > tab[j].delay)
            {
                tmp        = tab[j + 1];
                tab[j + 1] = tab[j];
                tab[j]     = tmp;
            }
        }
    }
}


void most_delayed_airlines (Hashtab_ptr_flightcell hash_airline, struct airline_cell *airline_list, int nb_airlines)
{
    struct airline_cell *     result = NULL;
    struct airline_with_delay post_result[nb_airlines];
    int                       indice = 0;

    while (airline_list != NULL)
    {
        post_result[indice].airline = airline_list->val;
        post_result[indice].delay =
        delayed_airline (airline_list->val.iata_code, hash_airline, airline_list, NO);
        airline_list = airline_list->next;
        indice++;
    }

    sort_delayed_airlines (post_result, nb_airlines);
    for (int i = 0; i < 5; i++)
    {
        adding_head_airline (&result, post_result[i].airline);
    }

    print_airlines (result);
    printf ("\n");
    erase_airlines_list (&result);
    return;
}


/*The procedures below are necessary for the requests: most-delayed-airlines-at-airport*/
void most_delayed_airlines_by_airport (char                   dest[],
                                       Hashtab_ptr_flightcell hashtab_dest,
                                       struct airline_cell *  airline_list,
                                       int                    nb_airlines)
{
    struct flight_cell * f_list    = hashtab_dest[hash_function_dest_and_dep (dest)];
    struct flight_cell * tmp_f     = f_list;
    struct airline_cell *tmp_a     = airline_list;
    struct airline_cell *al_result = NULL;
    int                  cpt       = 0;
    if (tmp_f == NULL || tmp_a == NULL)
    {
        printf ("No flight or airline found!\n");
        return;
    }
    /*on stocke dans une liste chainée toutes les airlines opérant des vols à dest de dest*/
    while (tmp_f != NULL)
    {
        tmp_a = airline_list;
        while (tmp_a != NULL)
        {
            if (strcmp (tmp_f->val.airline, tmp_a->val.iata_code) == 0)
            {
                cpt = adding_airline_without_duplicate (&al_result, tmp_a->val);
            }
            if (cpt == nb_airlines) break;
            tmp_a = tmp_a->next;
        }
        if (nb_airlines == cpt) break;
        tmp_f = tmp_f->next_dest_airport;
    }

    printf ("\n");
    /*on calcule et on range dans un tableau les airlines selon le retad d'arrivée à dest*/
    int                       delay = 0, nbpa = 0;
    struct airline_with_delay post_result[cpt];
    int                       indice = 0;
    tmp_a                            = al_result;
    while (tmp_a != NULL)
    {
        tmp_f = f_list;
        delay = 0;
        nbpa  = 0;
        while (tmp_f != NULL)
        {
            if (strcmp (tmp_f->val.airline, tmp_a->val.iata_code) == 0)
            {
                delay += tmp_f->val.arr_delay;
                nbpa++;
            }
            tmp_f = tmp_f->next_dest_airport;
        }
        post_result[indice].airline = tmp_a->val;
        post_result[indice].delay   = delay / nbpa;
        indice++;
        tmp_a = tmp_a->next;
    }


    sort_delayed_airlines (post_result, cpt);
    struct airline_cell *result = NULL;
    if (cpt > 3)
    {
        for (int i = cpt - 4; i < cpt - 1; i++)
        {
            adding_head_airline (&result, post_result[i].airline);
        }
    }
    else
    {
        for (int m = 0; m < cpt; m++)
        {
            adding_head_airline (&result, post_result[m].airline);
        }
    }

    print_airlines (result);
    printf ("\n");
    erase_airlines_list (&result);
    erase_airlines_list (&al_result);
    return;
}


/*The procedure below is necessary for the request changed-flight*/
void changed_flights (unsigned char month, unsigned char day, Hashtab_ptr_flightcell hashtab_date)
{
    struct flight_cell *fl     = hashtab_date[hash_function_date (month, day)];
    struct flight_cell *result = NULL;
    while (fl != NULL)
    {
        if (fl->val.month == month && fl->val.day == day && (fl->val.diverted == 1 || fl->val.cancelled == 1))
        {
            adding_head_flight (&result, fl->val, 1);
        }

        fl = fl->next_date;
    }
    print_flights (result, 1);
    printf ("\n");
    erase_flights_list (&result, 1);
}


/*The procedure below is necessary for the request avg-flight-duration*/
void avg_flight_duration (char org[], char dest[], Hashtab_ptr_flightcell hashtab_airport)
{
    struct flight_cell *flap = hashtab_airport[hash_function_dest_and_dep (org)];
    if (flap == NULL)
    {
        printf ("No flight found\n\n");
        return;
    }
    float avg_airtime = 0;
    int   cpt         = 0;
    while (flap != NULL)
    {
        if (strcmp (flap->val.dest_air, dest) == 0 && strcmp (flap->val.org_air, org) == 0)
        {
            avg_airtime += flap->val.air_time;
            cpt++;
        }
        flap = flap->next_dep_airport;
    }

    printf ("Average: %.2f minutes (%d flights)\n\n", avg_airtime / cpt, cpt);
}


/*The procedure below is necessary for the request avg-flight-duration*/
void find_itinerary (char                   org[],
                     char                   dest[],
                     int                    month,
                     int                    day,
                     Hashtab_ptr_flightcell hashtab_date,
                     int                    time,
                     struct airport_cell *  airport_list,
                     int                    limit)
{
    struct airport_cell *tmpa  = airport_list;
    int                  verif = 0;
    if (limit <= 0) limit = 10000;
    int max = 0;
    /*Verify if airports entered by the user exist*/
    while (tmpa != NULL)
    {
        if (strcmp (tmpa->val.iata_code, dest) == 0 || strcmp (tmpa->val.iata_code, org) == 0)
        {
            verif++;
        }
        tmpa = tmpa->next;
    }
    if (verif != 2)
    {
        printf ("\n  %i Departure or arrival airport does not exist in our database !\n\n", verif);
        return;
    }
    struct flight_cell *flap = hashtab_date[hash_function_date (month, day)];
    if (flap == NULL) return;

    struct flight_cell *tmp = flap;
    verif                   = 0;

    /*Checking for itinerary without stop*/
    printf ("\nTravels without stop:\n");
    while (tmp != NULL)
    {
        if (tmp->val.sched_dep > time && strcmp (tmp->val.org_air, org) == 0 &&
            strcmp (tmp->val.dest_air, dest) == 0 && max < limit)
        {
            printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp->val.month, tmp->val.day, tmp->val.weekday,
                    tmp->val.airline, tmp->val.org_air, tmp->val.dest_air, tmp->val.sched_dep,
                    tmp->val.dist, tmp->val.sched_arr);
            verif++;
            max++;
        }
        tmp = tmp->next_date;
    }
    if (verif == 0)
    {
        printf ("No direct flights found !\n");
    }

    /*Checking for itineraries with one stop*/
    if (max < limit)
    {
        tmp                      = flap;
        verif                    = 0;
        struct flight_cell *tmp2 = flap;
        printf ("\nTravels with one stop:\n");
        while (tmp != NULL)
        {
            if (tmp->val.sched_dep > time && strcmp (tmp->val.org_air, org) == 0 &&
                strcmp (tmp->val.dest_air, dest) != 0)
            {
                while (tmp2 != NULL)
                {
                    if ((strcmp (tmp2->val.org_air, org) != 0) &&
                        (tmp2->val.sched_dep > tmp->val.sched_arr + 100) &&
                        (strcmp (tmp->val.dest_air, tmp2->val.org_air) == 0) &&
                        (strcmp (tmp2->val.dest_air, dest) == 0) && max < limit)
                    {
                        printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp->val.month, tmp->val.day,
                                tmp->val.weekday, tmp->val.airline, tmp->val.org_air, tmp->val.dest_air,
                                tmp->val.sched_dep, tmp->val.dist, tmp->val.sched_arr);
                        printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp2->val.month, tmp2->val.day,
                                tmp2->val.weekday, tmp2->val.airline, tmp2->val.org_air, tmp2->val.dest_air,
                                tmp2->val.sched_dep, tmp2->val.dist, tmp2->val.sched_arr);
                        verif++;
                        max++;
                    }
                    tmp2 = tmp2->next_date;
                }
            }
            tmp  = tmp->next_date;
            tmp2 = flap;
        }
        if (verif == 0)
        {
            printf ("No travels with one stop found !\n");
        }
    }
    /*Checking for itineraries with two stops*/
    if (max < limit)
    {
        tmp                      = flap;
        verif                    = 0;
        struct flight_cell *tmp2 = flap;
        struct flight_cell *tmp3 = flap;
        printf ("\nTravels with two stops:\n");
        while (tmp != NULL)
        {
            if (tmp->val.sched_dep > time && strcmp (tmp->val.org_air, org) == 0 &&
                strcmp (tmp->val.dest_air, dest) != 0 && (tmp->val.sched_arr > tmp->val.sched_dep))
            {
                while (tmp2 != NULL)
                {
                    if ((strcmp (tmp2->val.org_air, org) != 0) &&
                        (tmp2->val.sched_dep > tmp->val.sched_arr + 100) &&
                        (strcmp (tmp->val.dest_air, tmp2->val.org_air) == 0) &&
                        (strcmp (tmp2->val.dest_air, dest) != 0) && max < limit &&
                        (tmp2->val.sched_arr > tmp2->val.sched_dep))
                    {
                        while (tmp3 != NULL)
                        {
                            if ((strcmp (tmp3->val.org_air, org) != 0) &&
                                (strcmp (tmp3->val.org_air, tmp2->val.dest_air) == 0) &&
                                (strcmp (tmp2->val.dest_air, dest) != 0) &&
                                (strcmp (tmp3->val.dest_air, dest) == 0) &&
                                (tmp3->val.sched_dep > tmp2->val.sched_arr + 100) && max < limit)
                            {
                                printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp->val.month,
                                        tmp->val.day, tmp->val.weekday, tmp->val.airline,
                                        tmp->val.org_air, tmp->val.dest_air, tmp->val.sched_dep,
                                        tmp->val.dist, tmp->val.sched_arr);
                                printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp2->val.month,
                                        tmp2->val.day, tmp2->val.weekday, tmp2->val.airline,
                                        tmp2->val.org_air, tmp2->val.dest_air, tmp2->val.sched_dep,
                                        tmp2->val.dist, tmp2->val.sched_arr);
                                printf ("%d,%d,%d,%s,%s,%s,%d,%d,%d\n", tmp2->val.month,
                                        tmp2->val.day, tmp3->val.weekday, tmp3->val.airline,
                                        tmp3->val.org_air, tmp3->val.dest_air, tmp3->val.sched_dep,
                                        tmp3->val.dist, tmp3->val.sched_arr);

                                verif++;
                                max++;
                            }
                            tmp3 = tmp3->next_date;
                        }
                    }
                    tmp2 = tmp2->next_date;
                    tmp3 = flap;
                }
            }
            tmp  = tmp->next_date;
            tmp2 = flap;
        }
        if (verif == 0)
        {
            printf ("No travels with two stops found !\n");
        }
    }


    printf ("\n");
}
