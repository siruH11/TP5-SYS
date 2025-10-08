#ifndef PLATEAU
#define PLATEAU
#include "pile.h"

typedef struct case_c{
    bool est_piegee;
    int nb_herisson;
    pile_c* pile_herisson;
}case;

typedef struct plateau_c{
    case** plateau;
    int nb_herisson;
    int nb_joueurs;
}plateau;

#endif
