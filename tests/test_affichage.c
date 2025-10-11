#include "pile.h"
#include "plateau.h"
#include "affiche_plateau.h"
#include "globales.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static pile_c* mk(int cap){ return create_pile(cap); }

int test_affiche_plateau(void){
    plateau P;
    P = malloc(nb_lignes*sizeof(plateau));
    for(int i=0;i<nb_lignes;i++){
        P[i]=malloc(nb_colonnes*sizeof(**P));
        for(int j=0;j<nb_colonnes;j++){
            P[i][j].est_piegee = ((i+j)%4==0);
            P[i][j].nb_herisson=0;
            P[i][j].pile_herisson=mk(32);
        }
    }

    for(int k=0;k<4;k++){ push(P[0][0].pile_herisson,3); P[0][0].nb_herisson++; }
    push(P[0][0].pile_herisson,1); P[0][0].nb_herisson++;
    push(P[0][0].pile_herisson,2); P[0][0].nb_herisson++;

    push(P[1][0].pile_herisson,1); P[1][0].nb_herisson++;
    push(P[2][2].pile_herisson,0); P[2][2].nb_herisson++;
    push(P[2][1].pile_herisson,3); P[2][1].nb_herisson++;
    push(P[2][0].pile_herisson,1); P[2][0].nb_herisson++;

    printf("affichage pour test_affichage_plateau: \n");
    affiche_plateau(P);
    printf("\n");

    for(int i=0;i<nb_lignes;i++){
        for(int j=0;j<nb_colonnes;j++) libere_pile(P[i][j].pile_herisson);
        free(P[i]);
    }
    free(P);
    return 0;
}