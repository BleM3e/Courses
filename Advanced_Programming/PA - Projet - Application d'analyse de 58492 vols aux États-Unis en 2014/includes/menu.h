/*
 * This header file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "menu.h"
 * @brief   Header file of "menu.c" which contains
 *          all string manipulations & print functions prototypes.
 * @date    Q2 2021
 * */


#include "requests.h"


void init_message ();
void help_message ();

void  empty_buffer ();
char *isolate_first_word (char **ptr_str);
void  date_decomposition (char **ptr_month, char **ptr_day, char *date);
void  reading_interpreting_request (char *                 user_request,
                                    struct airline_cell *  al_list,
                                    struct airport_cell *  ap_list,
                                    Hashtab_ptr_flightcell hastab_date,
                                    Hashtab_ptr_flightcell hashtab_airline,
                                    Hashtab_ptr_flightcell hashtab_dest,
                                    Hashtab_ptr_flightcell hashtab_dep,
                                    int                    nb_airlines,
                                    int                    nb_airports,
                                    int                    nb_flights);
