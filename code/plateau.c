//fonction create_plateau à faire
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "globales.h"
#include "pile.h"
#include "plateau.h"

plateau create_plateau(void){
        srand( time( NULL ) );
    Case** new_plateau = malloc(nb_lignes*sizeof(Case*));
    for (int i=0;i<nb_lignes;i++){
        new_plateau[i] = malloc(nb_colonnes*sizeof(Case));
        for(int j=0;j<nb_colonnes;j++){//initialisation
            new_plateau[i][j].est_piegee = false;
            new_plateau[i][j].nb_herisson = 0;
            new_plateau[i][j].pile_herisson =create_pile(nb_herisson * nb_joueurs);
        }
    }
    for(int k = 0; k<nb_herisson;k++){
        for(int q=0;q<nb_joueurs;q++){//placement des herissons en colonne0
            int ligne_placement = rand()%nb_lignes;
            new_plateau[ligne_placement][0].nb_herisson++;
            push(new_plateau[ligne_placement][0].pile_herisson ,q);
        }
    }
    for(int k =0;k<taille_pos_piegee;k++){//position piegees
        if(pos_piegee[k].ligne <nb_lignes && pos_piegee[k].colonne <nb_colonnes){
            new_plateau[pos_piegee[k].ligne][pos_piegee[k].colonne].est_piegee = true;
        }
    }
return(new_plateau);
}

void libere_plateau(plateau p){
    for(int i = 0 ; i<nb_lignes; i++){
        for(int j =0;j<nb_colonnes;j++){
            libere_pile(p[i][j].pile_herisson);
        }
        free(p[i]);
    }
    free(p);
}