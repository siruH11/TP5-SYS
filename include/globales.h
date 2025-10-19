#ifndef GLOBALES
#define GLOBALES

#include <stdlib.h>
#include <stdbool.h>
typedef struct pos_c{
    int ligne;
    int colonne;
}pos;

extern bool joueur_assez_herisson ;
extern pos pos_piegee[6];
extern int taille_pos_piegee;
extern int nb_lignes;
extern int nb_colonnes;
extern int nb_herisson ;
extern int nb_joueurs;

extern bool* gagnants;
void init_gagnants(void);

extern bool doping_variant;
extern bool tube_variant;
extern bool anarchohedgehog;



#endif