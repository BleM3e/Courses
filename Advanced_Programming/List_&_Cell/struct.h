#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef int element;    //Pour pouvoir échanger rapidement le type de element

struct cell{
    element val;
    struct cell * suiv;
};

struct list{
    struct cell * t;    //tete
    struct cell * q;    //queue
}



#endif