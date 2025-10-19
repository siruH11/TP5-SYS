#include "globales.h"
#include <stdlib.h>
#include <stdbool.h>


pos pos_piegee[6] = {{.ligne =0 ,.colonne =2},{.ligne =1 , .colonne =6},
                    {.ligne =2 ,.colonne =4},{.ligne =3 , .colonne =5},
                    {.ligne =4 ,.colonne =3},{.ligne =5 ,.colonne =7}};
int taille_pos_piegee = 6;
bool joueur_assez_herisson = false;

//param de plateau
int nb_lignes = 6;
int nb_colonnes = 7;
int nb_herisson = 4;
int nb_joueurs = 2;

bool* gagnants = NULL;
void init_gagnants(void){
gagnants = malloc(nb_joueurs*sizeof(bool));
for (int k = 0 ; k < nb_joueurs; k++){
    gagnants[k] = false;
}
}

bool doping_variant = false;
bool tube_variant = true;
bool anarchohedgehog = true;
