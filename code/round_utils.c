#include "round_utils.h"
#include "globales.h"
#include "affiche_plateau.h"
#include "pile.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int roll_dice() {
    static int seeded = 0;
    if (!seeded) { srand((unsigned)time(NULL)); seeded = 1; }
    return (rand() % nb_lignes) + 1;
}

/* Y a-t-il un hérisson quelque part à gauche de (i,j) ? */
int anyone_on_left(plateau P, int i, int j) {
    if (!P || i < 0 || j <= 0) return 0;
    for (int x = 0; x < j; ++x) {
        if (P[i][x].nb_herisson > 0) return 1;
    }
    return 0;
}

bool can_move_right(plateau P, int i, int j) {
    if (!P) return false;
    if (i < 0 || i >= nb_lignes || j < 0 || j >= nb_colonnes) return false; /* pas de case à droite */
    if (P[i][j].nb_herisson == 0) return false;                                  /* case vide */
    if (P[i][j].est_piegee && anyone_on_left(P, i, j)) return false;             /* règle du piège */
    return true;
}

void do_move_right(plateau P, int i, int j) {
    if (!P) return;
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    if(!doping_variant || !(j+1 == nb_colonnes -1)){//ajout doping variant,
    //on verifie que l'on est pas dans le cas du 1er herisson arrivé
    push(P[i][j+1].pile_herisson, tok);
    P[i][j+1].nb_herisson++;
    }
    else{
        doping_variant =false;//si c'est le cas, on fait disparaitre le herisson de la partie
        printf("\n!!herisson dopé, disqualification!!\n\n");
    }
}

bool can_move_vertical(plateau P, int i, int j, int di, int player_id) {
    if (!P) return false;
    if (i < 0 || i >= nb_lignes || j < 0 || j >= nb_colonnes) return false;
    if (di != -1 && di != +1) return false;
    int ni = i + di;
    if (tube_variant){
        if (ni < -1 || ni > nb_lignes) return false; //on rajoute les cas
        //ou on est au bord
    }
    else{
    if (ni < 0 || ni >= nb_lignes) return false;
    }
    if (P[i][j].nb_herisson == 0) return false;

    /* Le sommet doit appartenir au joueur */
    if (!anarchohedgehog){
        int top_c = top(P[i][j].pile_herisson);
        if (top_c < 0 || top_c != player_id) return false;
    }

    /* Pas de sortie de piège si hérissons à gauche */
    if (P[i][j].est_piegee && anyone_on_left(P, i, j)) return false;

    return true;
}

void do_move_vertical(plateau P, int i, int j, int di) {
    if (!P) return;
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    if(tube_variant && i + di == -1){
        i = nb_lignes -1 -di ;//met i+di à nb_lignes -1
    }
    if (tube_variant && i + di == nb_lignes){
        i = 0 -di ;// met i + di à 0
    }
    push(P[i+di][j].pile_herisson, tok);
    P[i+di][j].nb_herisson++;
}

int list_right_moves(plateau P, int line, int cols_out[], int cap) {
    if (!P || !cols_out || cap <= 0 || line < 0 || line >= nb_lignes) return 0;
    int n = 0;
    for (int j = 0; j < nb_colonnes - 1; ++j) {
        if (can_move_right(P, line, j)) {
            if (n < cap) cols_out[n] = j;
            n++;
        }
    }
    return n;
}

int count_arrivals_player(plateau P, int player_id) {
    if (!P || nb_colonnes <= 0) return 0;
    int count = 0;
    int last = nb_colonnes - 1;
    for (int i = 0; i < nb_lignes; ++i) {
        int h = P[i][last].nb_herisson;
        for (int k = 0; k < h; ++k) {
            int tok = peek(P[i][last].pile_herisson, k); /* k=0 sommet */
            if (tok == player_id) count++;
        }
    }
    return count;
}

/* Lecture/flush ligne standard (évite mélanges scanf/getchar) */
void flush_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}