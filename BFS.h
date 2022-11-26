#ifndef ECE_CITY_2_I_BFS_H
#define ECE_CITY_2_I_BFS_H


#include <stdio.h>
#include <stdlib.h>

typedef struct maillon{
    //numéro du sommet
    int num;
//pointeur sur la maillon suivant
    struct maillon*suiv;
}t_maillon;

typedef struct file{
    t_maillon*tete; //pointeur sur le premier maillon
    t_maillon*fin; //pointeur sur le dernier maillon
}t_file;


#endif //ECE_CITY_2_I_BFS_H
