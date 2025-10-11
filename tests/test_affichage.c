#include "pile.h"
#include "plateau.h"
#include "affiche_plateau.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static pile_c* mk(int cap){ return create_pile(cap); }

int test_plateau(void){
    int L=6, C=9;
    plateau P;
    P.nb_herisson=0; P.nb_joueurs=4;
    P.plateau = malloc(L*sizeof(*P.plateau));
    for(int i=0;i<L;i++){
        P.plateau[i]=malloc(C*sizeof(**P.plateau));
        for(int j=0;j<C;j++){
            P.plateau[i][j].est_piegee = ((i+j)%4==0);
            P.plateau[i][j].nb_herisson=0;
            P.plateau[i][j].pile_herisson=mk(32);
        }
    }

    for(int k=0;k<4;k++){ push(P.plateau[0][0].pile_herisson,3); P.plateau[0][0].nb_herisson++; }
    push(P.plateau[0][0].pile_herisson,1); P.plateau[0][0].nb_herisson++;
    push(P.plateau[0][0].pile_herisson,2); P.plateau[0][0].nb_herisson++;

    push(P.plateau[1][0].pile_herisson,1); P.plateau[1][0].nb_herisson++;
    push(P.plateau[2][2].pile_herisson,0); P.plateau[2][2].nb_herisson++;
    push(P.plateau[2][3].pile_herisson,3); P.plateau[2][3].nb_herisson++;
    push(P.plateau[2][3].pile_herisson,1); P.plateau[2][3].nb_herisson++;

    affiche_plateau(&P,L,C);

    for(int i=0;i<L;i++){
        for(int j=0;j<C;j++) libere_pile(P.plateau[i][j].pile_herisson);
        free(P.plateau[i]);
    }
    free(P.plateau);
    return 0;
}