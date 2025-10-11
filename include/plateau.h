#ifndef PLATEAU
#define PLATEAU

#include <stdbool.h>
#include "pile.h"

typedef struct case_c {
    bool   est_piegee;
    int    nb_herisson;
    pile_c *pile_herisson;
} Case; 

typedef Case** plateau;
plateau create_plateau(void);

#endif
