#ifndef PLATEAU
#define PLATEAU

#include <stdbool.h>
#include "pile.h"

typedef struct case_c {
    bool   est_piegee;
    int    nb_herisson;
    pile_c *pile_herisson;
} Case; 

typedef struct plateau_c {
    Case **plateau;
    int    nb_herisson;
    int    nb_joueurs;
} plateau;

#endif
