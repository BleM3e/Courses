/*
 * This header file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "read_data.h"
 * @brief   Header file of "read_data.c" which contains
 *          all procedures' prototypes for reading, storing
 *          & printing the datas of the CSV files :
 *          "airlines.csv", "airports.csv" & "flights.csv".
 * @date    Q2 2021
 * */


#include "hash_functions.h"


void adding_head_airline (struct airline_cell **, struct airline);
int  read_airlines (struct airline_cell **, FILE *);
void print_airlines (struct airline_cell *);

void adding_head_airport (struct airport_cell **, struct airport);
int  read_airports (struct airport_cell **, FILE *);
void print_airports (struct airport_cell *);

void init_flight_cell (struct flight_cell **);
void adding_head_flight_read (struct flight_cell **,
                              struct flight_cell **,
                              struct flight_cell **,
                              struct flight_cell **,
                              struct flight);
int  read_flights (Hashtab_ptr_flightcell hashtab_date,
                   Hashtab_ptr_flightcell hastab_airline,
                   Hashtab_ptr_flightcell hashtab_dest,
                   Hashtab_ptr_flightcell hashtab_dep,
                   FILE *);
void print_flights (struct flight_cell *, int);
