#ifndef ROUND_UTILS_H
#define ROUND_UTILS_H

#include <stdbool.h>
#include "plateau.h"

/* Tirage du dé (1..nb_lignes) */
int  roll_die(void);

/* Déplacements horizontaux */
bool can_move_right(const plateau P, int i, int j);
void do_move_right(plateau P, int i, int j);

/* Déplacements verticaux pour un hérisson au sommet appartenant à player_id */
bool can_move_vertical(const plateau P, int i, int j, int di, int player_id);
void do_move_vertical(plateau P, int i, int j, int di);

/* Lance un round et retourne true si la partie se termine pour player_id) */
bool play_round(plateau P, int player_id);

#endif /* ROUND_UTILS_H */
