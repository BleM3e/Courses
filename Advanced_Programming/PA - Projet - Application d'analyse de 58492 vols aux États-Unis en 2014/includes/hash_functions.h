/*
 * This header file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "hash_functions.h"
 * @brief   Header file of "hash_functions.c" which contains
 *          all hash functions & tests' prototypes.
 * @date    Q2 2021
 * */


#include "data_structures.h"


void init_hash_table (Hashtab_ptr_flightcell);

int hash_function_date (unsigned char month, unsigned char day);
int hash_function_airline (char iata_code_airline[]);
int hash_function_dest_and_dep (char iata_code_airport[]);

int  nb_flights (struct flight_cell *flight_list, int type);
void hash_tests (struct airline_cell *  al_list,
                 struct airport_cell *  ap_list,
                 Hashtab_ptr_flightcell hashtab_date,
                 Hashtab_ptr_flightcell hashtab_airline,
                 Hashtab_ptr_flightcell hashtab_dest,
                 Hashtab_ptr_flightcell hashtab_dep);
