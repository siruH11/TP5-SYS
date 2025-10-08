#ifndef AFFICHE_PLATEAU_H
#define AFFICHE_PLATEAU_H

#include <stdio.h>
#include "pile.h"
#include "plateau.h"

void affiche_plateau_ex(plateau *P, int L, int C, int dice_line);
static inline void affiche_plateau(plateau *P, int L, int C){
    affiche_plateau_ex(P, L, C, -1);
}

#endif
