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
    P = malloc(L*sizeof(plateau));
    for(int i=0;i<L;i++){
        P[i]=malloc(C*sizeof(**P));
        for(int j=0;j<C;j++){
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
    push(P[2][3].pile_herisson,3); P[2][3].nb_herisson++;
    push(P[2][3].pile_herisson,1); P[2][3].nb_herisson++;

    affiche_plateau(P,L,C);

    for(int i=0;i<L;i++){
        for(int j=0;j<C;j++) libere_pile(P[i][j].pile_herisson);
        free(P[i]);
    }
    free(P);
    return 0;
}