#ifndef ROUNDS_H
#define ROUNDS_H

#include "affiche_plateau.h"
#include <stdbool.h>

// Lancer de dé 1..L
int roll_die(int L);

// Joue un tour complet pour le joueur `player_id` (0→A, 1→B, ...).
// Retourne true si la partie s'arrête (≥3 hérissons du joueur en dernière colonne).
bool play_round(plateau *P, int L, int C, int player_id);

// Helpers utiles si tu veux tester
bool can_move_right(const plateau *P, int L, int C, int i, int j);
void do_move_right(plateau *P, int i, int j);

bool can_move_vertical(const plateau *P, int L, int C, int i, int j, int di, int player_id);
void do_move_vertical(plateau *P, int i, int j, int di);

#endif
#endif