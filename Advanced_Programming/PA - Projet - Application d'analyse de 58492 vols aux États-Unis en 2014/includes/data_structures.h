/*
 * This header file is made by Clément KOPERSKI & Sami AGGAR,
 * two students at Polytech Lille,
 * for their Advanced Programming's project in bachelor's degree.
 *
 * @name    "data_structures.h"
 * @brief   Header file which contains all the necessary
 *          includes, the constant definitions' & data structures
 *          used in all files.
 * @date    Q2 2021
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1500
#define MAX_IATA_CODE_AL 3
#define MAX_IATA_CODE_AP 4
#define MAX_AL_AP_NAME 100
#define MAX_CSC_NAME 50

#define DATE 1
#define AIRLINE 2
#define DEST_AIRPORT 3
#define DEP_AIRPORT 4

#define YES 1
#define NO 0


// Definition of struct airlines (by a linked list) which groups all airlines with their information :
struct airline
{
    char iata_code[MAX_IATA_CODE_AL];
    char airline_name[MAX_AL_AP_NAME];
};

struct airline_cell
{
    struct airline       val;
    struct airline_cell *next;
};


// Definition of struct airports (by a linked list) which groups all airports with their information :
struct airport
{
    char  iata_code[MAX_IATA_CODE_AP];
    char  airport_name[MAX_AL_AP_NAME];
    char  city[MAX_CSC_NAME];
    char  state[MAX_CSC_NAME];
    char  country[MAX_CSC_NAME];
    float latitude;
    float longitude;
};

struct airport_cell
{
    struct airport       val;
    struct airport_cell *next;
};


// Definition of struct flights (by a hash table of linked lists) which groups all flights with their information :
struct flight
{
    unsigned char month;
    unsigned char day;
    unsigned char weekday;
    char          airline[MAX_AL_AP_NAME];
    char          org_air[MAX_IATA_CODE_AP];
    char          dest_air[MAX_IATA_CODE_AP];
    int           sched_dep;
    float         dep_delay;
    float         air_time;
    int           dist;
    int           sched_arr;
    float         arr_delay;
    char          diverted;
    char          cancelled;
};

struct flight_cell
{
    struct flight       val;
    struct flight_cell *next_date;
    struct flight_cell *next_airline;
    struct flight_cell *next_dest_airport;
    struct flight_cell *next_dep_airport;
};
typedef struct flight_cell *Hashtab_ptr_flightcell[SIZE];


// Definition of struct airline_with_delay which will help for coding some requests :
struct airline_with_delay
{
    struct airline airline;
    int            delay;
};
