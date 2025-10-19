#ifndef ROUND_UTILS_H
#define ROUND_UTILS_H

#include <stdbool.h>
#include "plateau.h"

/* Tirage du dé (1..nb_lignes) */
int  roll_dice(void);

/* Déplacements horizontaux */
bool can_move_right(const plateau P, int i, int j);
void do_move_right(plateau P, int i, int j);

/* Déplacements verticaux pour un hérisson au sommet appartenant à player_id */
bool can_move_vertical(const plateau P, int i, int j, int di, int player_id);
void do_move_vertical(plateau P, int i, int j, int di);
int list_right_moves(plateau P, int line, int cols_out[], int cap);
int count_arrivals_player(plateau P, int player_id);
void flush_line(void);

#endif /* ROUND_UTILS_H */
