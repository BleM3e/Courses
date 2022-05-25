/*
 * This file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "read_data.c"
 * @brief   Source file which contains all procedures for
 *          reading the data files ("*.csv"), storing
 *          these datas in our own structures & printing
 *          these datas in the same format than CSV files.
 * @date    Q2 2021
 * */


#include "../includes/read_data.h"


void adding_head_airline (struct airline_cell **ptr_airlines_list, struct airline elem)
{
    struct airline_cell *newcell = malloc (sizeof (struct airline_cell));
    if (newcell == NULL) /* Testing if memory is full */
        return exit (EXIT_FAILURE);

    newcell->val       = elem;
    newcell->next      = *ptr_airlines_list;
    *ptr_airlines_list = newcell;
}


/*This procedure read the datas relative to airports in csv file airports.csv using fscanf with regex, because some fields contain spaces or other characters not readed by fscanf*/
int read_airlines (struct airline_cell **ptr_airlines_list, FILE *fp)
{
    if (fp == NULL) return 0;
    int            cpt = 0;
    struct airline al;

    if (fscanf (fp, "%*[^\n]\n") != 0) exit (EXIT_FAILURE); /* Skip the first row of the csv file */
    while (fscanf (fp, "%2s,", al.iata_code) == 1)
    {
        if (fscanf (fp, "%[^\n]s\n", al.airline_name) != 1) strcpy (al.airline_name, "default");
        adding_head_airline (ptr_airlines_list, al);
        cpt++;
    }
    return cpt;
}


void print_airlines (struct airline_cell *airlines_list)
{
    if (airlines_list == NULL)
    {
        printf ("No flights found\n");
        return;
    }
    while (airlines_list != NULL)
    {
        printf ("%s,", airlines_list->val.iata_code);
        printf ("%s\n", airlines_list->val.airline_name);
        airlines_list = airlines_list->next;
    }
}


// Three procedures to treat the datas in "airports.csv" file:
void adding_head_airport (struct airport_cell **ptr_airports_list, struct airport elem)
{
    struct airport_cell *newcell = malloc (sizeof (struct airport_cell));
    if (newcell == NULL) /* Testing if memory is full */
        return exit (EXIT_FAILURE);

    newcell->val       = elem;
    newcell->next      = *ptr_airports_list;
    *ptr_airports_list = newcell;
}

/*This procedure read the datas relative to airports in csv file airports.csv using fscanf with regex, because some fields contain spaces or other characters not readed by fscanf*/
int read_airports (struct airport_cell **ptr_airports_list, FILE *fp)
{
    if (fp == NULL) return 0;

    int            cpt = 0;
    struct airport ap;

    if (fscanf (fp, "%*[^\n]\n") != 0) exit (EXIT_FAILURE); /* Skip the first row of the csv file */

    char longitudetmp[50] = { '\0' };
    char latitudetmp[50]  = { '\0' };
    while (fscanf (fp, "%3s,", ap.iata_code) == 1)
    {
        if (fscanf (fp, "%[^,]s,", ap.airport_name) != 1)
            strcpy (ap.airport_name, "default"); /*the expression %[^,]s, means that fscanf read everything until it finds a coma*/
        if (fscanf (fp, ",%[^,]s,", ap.city) != 1) strcpy (ap.city, "default");
        if (fscanf (fp, ",%[^,]s,", ap.state) != 1) strcpy (ap.state, "default");
        if (fscanf (fp, ",%[^,]s,", ap.country) != 1) strcpy (ap.country, "default");
        if (fscanf (fp, ",%[^,]s,", latitudetmp) != 1)
        {
            latitudetmp[0] = '0';
            latitudetmp[1] = '\0';
        }
        ap.latitude = atof (latitudetmp);
        if (fscanf (fp, ",%[^\n]s\n", longitudetmp) !=
            1) /*the expression %[^\n]s, means that fscanf read everything until it finds a carriage return*/
        {
            longitudetmp[0] = '0';
            longitudetmp[1] = '\0';
        }
        ap.longitude = atof (longitudetmp);

        adding_head_airport (ptr_airports_list, ap);
        cpt++;
    }

    return cpt;
}


void print_airports (struct airport_cell *airports_list)
{
    if (airports_list == NULL)
    {
        printf ("No Airports found\n");
        return;
    }

    while (airports_list != NULL)
    {
        printf ("%s,", airports_list->val.iata_code);
        printf ("%s,", airports_list->val.airport_name);
        printf ("%s,", airports_list->val.city);
        printf ("%s,", airports_list->val.state);
        printf ("%s,", airports_list->val.country);
        printf ("%f,", airports_list->val.latitude);
        printf ("%f\n", airports_list->val.longitude);
        airports_list = airports_list->next;
    }
}


// Three procedures to treat the datas in "flights.csv" file and a procedure that initializes flight_cell:
void init_flight_cell (struct flight_cell **ptr_flight_list)
{
    if (*ptr_flight_list == NULL) return;
    (*ptr_flight_list)->next_date         = NULL;
    (*ptr_flight_list)->next_airline      = NULL;
    (*ptr_flight_list)->next_dest_airport = NULL;
    (*ptr_flight_list)->next_dep_airport  = NULL;
}

/*The following procedure add a flight to a flight linked list by following a certain path specified by an int named type*/

void adding_head_flight_read (struct flight_cell **ptr_flights_list_date,
                              struct flight_cell **ptr_flights_list_airline,
                              struct flight_cell **ptr_flights_list_dest_airport,
                              struct flight_cell **ptr_flights_list_dep_airport,
                              struct flight        elem)
{
    struct flight_cell *newcell = malloc (sizeof (struct flight_cell));
    init_flight_cell (&newcell);
    if (newcell == NULL) /* Testing if memory is full */
        return exit (EXIT_FAILURE);

    newcell->val               = elem;
    newcell->next_date         = *ptr_flights_list_date;
    newcell->next_airline      = *ptr_flights_list_airline;
    newcell->next_dest_airport = *ptr_flights_list_dest_airport;
    newcell->next_dep_airport  = *ptr_flights_list_dep_airport;

    *ptr_flights_list_date         = newcell;
    *ptr_flights_list_airline      = newcell;
    *ptr_flights_list_dest_airport = newcell;
    *ptr_flights_list_dep_airport  = newcell;
}


/*This procedure read the datas relative to flights in csv file flights.csv using fscanf with regex, because some fields contain spaces or other characters not readed by fscanf*/
int read_flights (Hashtab_ptr_flightcell hashtab_date,
                  Hashtab_ptr_flightcell hashtab_airline,
                  Hashtab_ptr_flightcell hashtab_dest,
                  Hashtab_ptr_flightcell hashtab_dep,
                  FILE *                 fp)
{
    if (fp == NULL) return 0;
    int cpt = 0;
    init_hash_table (hashtab_date);
    init_hash_table (hashtab_airline);
    init_hash_table (hashtab_dest);
    init_hash_table (hashtab_dep);
    struct flight f;

    if (fscanf (fp, "%*[^\n]\n") != 0) exit (EXIT_FAILURE); /* Skip the first row of the csv file */
    char tmp[50] = { '\0' };
    while (fscanf (fp, "%hhd,", &f.month) == 1)
    {
        if (fscanf (fp, "%hhd,", &(f.day)) != 1) f.day = -1;
        if (fscanf (fp, "%hhd,", &(f.weekday)) != 1) f.weekday = -1;
        if (fscanf (fp, "%2s,", f.airline) != 1) strcpy (f.airline, "def");
        if (fscanf (fp, "%3s,", f.org_air) != 1) strcpy (f.org_air, "def");
        if (fscanf (fp, "%3s,", f.dest_air) != 1) strcpy (f.dest_air, "def");
        if (fscanf (fp, "%d,", &(f.sched_dep)) != 1) f.sched_dep = -1;
        if (fscanf (fp, "%[^,]s,", tmp) != 1)
        {
            tmp[0] = '0';
            tmp[1] = '\0';
        }
        f.dep_delay = atof (tmp);
        if (fscanf (fp, ",%[^,]s,", tmp) != 1)
        {
            tmp[0] = '0';
            tmp[1] = '\0';
        }
        f.air_time = atof (tmp);
        if (fscanf (fp, ",%d,", &f.dist) != 1) f.dist = -1;
        if (fscanf (fp, "%d,", &f.sched_arr) != 1) f.sched_arr = -1;
        if (fscanf (fp, "%[^,]s,", tmp) != 1)
        {
            tmp[0] = '0';
            tmp[1] = '\0';
        }
        f.arr_delay = atof (tmp);
        if (fscanf (fp, ",%hhd,", &(f.diverted)) != 1) f.diverted = -1;
        if (fscanf (fp, "%hhd\n", &(f.cancelled)) != 1) f.diverted = -1;

        adding_head_flight_read (&(hashtab_date[hash_function_date (f.month, f.day)]),
                                 &(hashtab_airline[hash_function_airline (f.airline)]),
                                 &(hashtab_dest[hash_function_dest_and_dep (f.dest_air)]),
                                 &(hashtab_dep[hash_function_dest_and_dep (f.org_air)]), f);
        cpt++;
    }
    return cpt;
}


/*The following procedure print a flight linked list by following a certain path specified by an int named type*/
void print_flights (struct flight_cell *flights_list, int type)
{
    if (flights_list == NULL)
    {
        printf ("No Flights found!\n");
        return;
    }

    while (flights_list != NULL)
    {
        printf ("%d,", flights_list->val.month);
        printf ("%d,", flights_list->val.day);
        printf ("%d,", flights_list->val.weekday);
        printf ("%s,", flights_list->val.airline);
        printf ("%s,", flights_list->val.org_air);
        printf ("%s,", flights_list->val.dest_air);
        printf ("%d,", flights_list->val.sched_dep);
        printf ("%f,", flights_list->val.dep_delay);
        printf ("%f,", flights_list->val.air_time);
        printf ("%d,", flights_list->val.dist);
        printf ("%d,", flights_list->val.sched_arr);
        printf ("%f,", flights_list->val.arr_delay);
        printf ("%d,", flights_list->val.diverted);
        printf ("%d\n", flights_list->val.cancelled);

        switch (type)
        {
        case DATE:
            flights_list = flights_list->next_date;
            break;
        case AIRLINE:
            flights_list = flights_list->next_airline;
            break;
        case DEST_AIRPORT:
            flights_list = flights_list->next_dest_airport;
            break;
        case DEP_AIRPORT:
            flights_list = flights_list->next_dep_airport;
        }
    }
}
