#include "test_round_utils.h"

#include "round_utils.h"
#include "affiche_plateau.h"
#include "plateau.h"
#include "pile.h"
#include "globales.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*plateau indépendant de create_plateau pour les tests */
static plateau make_plateau(int L, int C, int cap) {
    Case **P = malloc((size_t)L * sizeof *P);
    assert(P && "malloc lignes");
    for (int i = 0; i < L; ++i) {
        P[i] = malloc((size_t)C * sizeof *P[i]);
        assert(P[i] && "malloc colonnes");
        for (int j = 0; j < C; ++j) {
            P[i][j].est_piegee    = false;
            P[i][j].nb_herisson   = 0;
            P[i][j].pile_herisson = create_pile(cap);
            assert(P[i][j].pile_herisson && "create_pile");
        }
    }
    return P;
}

static void destroy_plateau_local(plateau P) {
    if (!P) return;
    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            if (P[i][j].pile_herisson) libere_pile(P[i][j].pile_herisson);
        }
        free(P[i]);
    }
    free(P);
}

int test_round_utils(void) {

    plateau P = make_plateau(nb_lignes, nb_colonnes, /*cap pile*/16);

    puts(">>> Plateau initial");
    affiche_plateau(P);

    /* --- can_move_right: case vide -> false --- */
    assert(!can_move_right(P, 1, 1));

    /* On place un hérisson (joueur 0) sur (1,1) -> possible */
    push(P[1][1].pile_herisson, 0);
    P[1][1].nb_herisson++;
    assert(can_move_right(P, 1, 1));

    /* Piège + quelqu’un à gauche -> interdit */
    P[1][1].est_piegee = true;
    push(P[1][0].pile_herisson, 2);
    P[1][0].nb_herisson++;
    assert(!can_move_right(P, 1, 1));

    /* Enlève le hérisson de gauche -> redevient possible */
    (void)pop(P[1][0].pile_herisson); P[1][0].nb_herisson--;
    assert(can_move_right(P, 1, 1));

    puts("\n>>> Après placements initiaux (avant déplacement →)");
    affiche_plateau(P);

    /* --- do_move_right: déplace bien et MAJ compteurs --- */
    int before_src = P[1][1].nb_herisson;
    int before_dst = P[1][2].nb_herisson;
    do_move_right(P, 1, 1);
    assert(P[1][1].nb_herisson == before_src - 1);
    assert(P[1][2].nb_herisson == before_dst + 1);
    assert(peek(P[1][2].pile_herisson, 0) == 0);

    puts("\n>>> Après do_move_right(1,1)");
    affiche_plateau(P);

    /* --- can_move_vertical: ownership sommet --- */
    /* Place un sommet joueur 1 en (2,1) */
    push(P[2][1].pile_herisson, 1);
    P[2][1].nb_herisson++;
    /* Joueur 0 ne peut pas bouger ce sommet */
    assert(!can_move_vertical(P, 2, 1, -1, /*player=*/0));
    /* Joueur 1 peut bouger vers le haut */
    assert(can_move_vertical(P, 2, 1, -1, /*player=*/1));

    /* Piège + quelqu’un à gauche bloque la sortie verticale */
    P[2][1].est_piegee = true;
    push(P[2][0].pile_herisson, 3);
    P[2][0].nb_herisson++;
    assert(!can_move_vertical(P, 2, 1, -1, 1));

    /* Autorise le move en retirant la condition bloquante */
    P[2][1].est_piegee = false;
    int v_before_src = P[2][1].nb_herisson;
    int v_before_dst = P[1][1].nb_herisson;
    do_move_vertical(P, 2, 1, -1);
    assert(P[2][1].nb_herisson == v_before_src - 1);
    assert(P[1][1].nb_herisson == v_before_dst + 1);
    assert(peek(P[1][1].pile_herisson, 0) == 1);

    puts("\n>>> Après do_move_vertical(2,1,-1)");
    affiche_plateau(P);

    destroy_plateau_local(P);
    printf("✅ test_round_utils: OK\n");
    return 0;
}
