#ifndef ROUND_H
#define ROUND_H

#include <stdbool.h>
#include "plateau.h"
#include "round_utils.h"

/* Lance un round et retourne true si la partie se termine pour player_id) */
bool play_round(plateau P, int player_id);

#endif