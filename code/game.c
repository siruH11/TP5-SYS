#include "game.h"
#include "round.h"
#include "plateau.h"
#include "globales.h"
#include <stdbool.h>

void play_game() {
    init_gagnants();
    int joueur_actuel = 0;
    plateau P = create_plateau();
    bool game_finished = play_round(P,0);
    while (!(game_finished)) {
        joueur_actuel += 1;
        game_finished = play_round(P,joueur_actuel%nb_joueurs);
    }
    libere_plateau(P);
}