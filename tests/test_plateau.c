#include "pile.h"
#include "plateau.h"
#include "affiche_plateau.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void test_plateau(void){
    plateau P = create_plateau();
    printf("\n");
    printf("affichage pour test_plateau: \n");
    affiche_plateau(P);
    printf("\n");
    libere_plateau(P);

}