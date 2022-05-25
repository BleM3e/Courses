/*
 * This header file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "requests.h"
 * @brief   Header file of "requests.c" which contains
 *          all requests functions prototypes.
 * @date    Q2 2021
 * */


#include "read_data.h"


void erase_flights_list (struct flight_cell **, int);
void erase_airlines_list (struct airline_cell **);
void erase_airports_list (struct airport_cell **);
void erase_data (Hashtab_ptr_flightcell hashtab_date,
                 Hashtab_ptr_flightcell hashtab_airline,
                 Hashtab_ptr_flightcell hashtab_dest_airport,
                 Hashtab_ptr_flightcell hashtab_dep_airport,
                 struct airline_cell **,
                 struct airport_cell **);

void adding_head_flights (struct flight_cell **, struct flight, int);
int  adding_airports_withoutduplicate (struct airport_cell **, struct airport);
void show_airports (char iata_airline[], Hashtab_ptr_flightcell, struct airport_cell *, int);

int  adding_airline_without_duplicate (struct airline_cell **, struct airline);
void show_airlines (char iata[], Hashtab_ptr_flightcell, struct airline_cell *, int);

void show_flights (char dap[], unsigned char month, unsigned char day, Hashtab_ptr_flightcell, int, int);

void adding_ordonate (struct flight_cell **, struct flight);
void most_delayed_flights (Hashtab_ptr_flightcell);

int delayed_airline (char iata[], Hashtab_ptr_flightcell hashtab_airline, struct airline_cell *, int);
void changed_flights (unsigned char, unsigned char, Hashtab_ptr_flightcell);

void sort_delayed_airlines (struct airline_with_delay tab[], int size);
void most_delayed_airlines (Hashtab_ptr_flightcell, struct airline_cell *, int nb_flights);

void most_delayed_airlines_by_airport (char                   dest[],
                                       Hashtab_ptr_flightcell hashtab_dest,
                                       struct airline_cell *  airline_list,
                                       int                    nb_airlines);

void avg_flight_duration (char ap1[], char ap2[], Hashtab_ptr_flightcell);
void find_itinerary (char                   org[],
                     char                   dest[],
                     int                    month,
                     int                    day,
                     Hashtab_ptr_flightcell hashtab_date,
                     int                    time,
                     struct airport_cell *  airport_list,
                     int                    limit);
