/*
 * This file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "hash_functions.c"
 * @brief   Source file which contains all procedures for
 *          hashing the flights with four different primary
 *          keys : departure's date, iata_code of the airline,
 *          iata_code of the destination airport & origine airport.
 * @date    Q2 2021
 * */


#include "../includes/hash_functions.h"


void init_hash_table (Hashtab_ptr_flightcell hashtab)
{
    for (int i = 0; i < SIZE; i++) hashtab[i] = NULL;
}


int hash_function_date (unsigned char month, unsigned char day)
{
    int index = 0;

    if (day < 10)
        index = month * 10 + day;
    else
        index = month * 100 + day;

    return index % SIZE;
}


int hash_function_airline (char iata_code_airline[])
{
    int index = 0;
    int i     = 0;

    while (iata_code_airline[i] != '\0')
    {
        index += iata_code_airline[i];
        if (i == 0) index += iata_code_airline[i];
        if (i == 1) index *= iata_code_airline[i];
        i++;
    }

    return index % SIZE;
}


int hash_function_dest_and_dep (char iata_code_airport[])
{
    int index = 0;
    int i     = 0;

    while (iata_code_airport[i] != '\0')
    {
        index += iata_code_airport[i];
        if (i == 0) index += iata_code_airport[i];
        if (i == 1) index *= iata_code_airport[i];
        if (i == 2) index += iata_code_airport[i];
        i++;
    }

    return index % SIZE;
}


int nb_flights (struct flight_cell *flight_list, int type)
{
    int cpt = 0;

    while (flight_list != NULL)
    {
        cpt++;
        switch (type)
        {
        case DATE:
            flight_list = flight_list->next_date;
            break;

        case AIRLINE:
            flight_list = flight_list->next_airline;
            break;

        case DEST_AIRPORT:
            flight_list = flight_list->next_dest_airport;
            break;

        case DEP_AIRPORT:
            flight_list = flight_list->next_dep_airport;
            break;
        }
    }

    return cpt;
}


// BONUS procedure for testing the effeciency of our hash tables:
void hash_tests (struct airline_cell *  al_list,
                 struct airport_cell *  ap_list,
                 Hashtab_ptr_flightcell hashtab_date,
                 Hashtab_ptr_flightcell hashtab_airline,
                 Hashtab_ptr_flightcell hashtab_dest,
                 Hashtab_ptr_flightcell hashtab_dep)
{
    printf ("\nNumber of flights grouped by the indexes of the 4 hash tables (date, airline, dest "
            "& dep):\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf ("====== INDEX N°%d ======\n", i);
        printf ("DATE: %d\n", nb_flights (hashtab_date[i], 1));
        printf ("AIRLINE: %d\n", nb_flights (hashtab_airline[i], 2));
        printf ("DEST: %d\n", nb_flights (hashtab_dest[i], 3));
        printf ("DEP: %d\n\n", nb_flights (hashtab_dep[i], 4));
    }


    // Initialisation of the 2 arrays which contain all the indexes returned by the 2 hash functions airline, dest & dep:
    int L1[SIZE];
    int L2[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        L1[i] = -1;
        L2[i] = -1;
    }

    // Test of the date hash function (with approximately all days in a year):
    printf ("\nHere are all the indexes occuped in the hash table hashed by date of departure of "
            "flights:\n");
    for (int month = 1; month <= 12; month++)
    {
        for (int day = 1; day <= 31; day++) printf ("%d\n", hash_function_date (month, day));
    }

    // Test of the iata_code_airline & iata_code_dest_and_dep_airport hash functions:
    int i = 0;
    while (ap_list != NULL)
    {
        if (al_list != NULL)
        {
            L1[i]   = hash_function_airline (al_list->val.iata_code);
            al_list = al_list->next;
        }

        L2[i]   = hash_function_dest_and_dep (ap_list->val.iata_code);
        ap_list = ap_list->next;

        i++;
    }

    printf ("\nHere are all the iata_codes for airlines & airports grouped by the indexes of the "
            "hash tables:\n");
    int T1[SIZE];
    int T2[SIZE];
    int cpt1 = 0;
    int cpt2 = 0;
    for (int i = 0; i < SIZE; i++)
    {
        printf ("Index n°%d: ", i);
        for (int j = 0; j < SIZE; j++)
        {
            if (i == L1[j]) cpt1++;
            if (i == L2[j]) cpt2++;
        }
        printf ("%d iata_code for airlines & ", cpt1);
        printf ("%d iata_code for airports\n", cpt2);
        T1[i] = cpt1;
        T2[i] = cpt2;
        cpt1  = 0;
        cpt2  = 0;
    }

    for (int i = 0; i < SIZE; i++)
    {
        cpt1 += T1[i];
        cpt2 += T2[i];
    }
    printf ("\nNumber of airlines (check): %d\n", cpt1);
    printf ("Number of airports (check): %d\n\n", cpt2);

    int nb_empty                = 0;
    int nb_simple               = 0;
    int nb_collisions           = 0;
    int nb_double_collisions    = 0;
    int nb_triple_collisions    = 0;
    int nb_quadruple_collisions = 0;
    int nb_airline_simple       = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (T1[i] == 1) nb_airline_simple++;
        if (T2[i] == 0) nb_empty++;
        if (T2[i] == 1) nb_simple++;
        if (T2[i] == 2) nb_collisions++;
        if (T2[i] == 3) nb_double_collisions++;
        if (T2[i] == 4) nb_triple_collisions++;
        if (T2[i] == 5) nb_quadruple_collisions++;
    }
    printf ("Number of simple occuped spaces in the hashtable of flights hashed by "
            "iata_code_airline: %d\n",
            nb_airline_simple);
    printf (
    "Number of empty spaces (0), simple occuped spaces (1), simple collisions (2) & multiple "
    "collisions (3, 4, 5) in the hashtable of flights hashed by iata_code_dest_airport:\n");
    printf ("0: %d, 1: %d, 2: %d, 3: %d, 4: %d, 5: %d\n\n", nb_empty, nb_simple, nb_collisions,
            nb_double_collisions, nb_triple_collisions, nb_quadruple_collisions);
}
