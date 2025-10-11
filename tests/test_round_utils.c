#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "round_utils.h"
#include "test_round_utils.h"
#include "plateau.h"
#include "pile.h"
#include "globales.h"

/* Libère proprement un plateau (si tu n'as pas de destroy_plateau) */
static void destroy_plateau_local(plateau P, int L, int C) {
    if (!P) return;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            if (P[i][j].pile_herisson) {
                libere_pile(P[i][j].pile_herisson);
            }
        }
        free(P[i]);
    }
    free(P);
}

int test_round_utils(void) {

    plateau P = create_plateau();
    assert(P && "create_plateau() a renvoyé NULL");

    /* --- can_move_right: case vide -> false --- */
    assert(!can_move_right(P, nb_lignes, nb_colonnes, 1, 1));

    /* On place un hérisson (joueur 0) sur (1,1) */
    push(P[1][1].pile_herisson, 0);
    P[1][1].nb_herisson++;
    assert(can_move_right(P, nb_lignes, nb_colonnes, 1, 1));

    /* Règle du piège: si (1,1) est piégée et quelqu'un à gauche, alors false */
    P[1][1].est_piegee = true;
    push(P[1][0].pile_herisson, 2); /* n'importe quel joueur */
    P[1][0].nb_herisson++;
    assert(!can_move_right(P, nb_lignes, nb_colonnes, 1, 1));

    /* Si on enlève le hérisson de gauche, alors ça redevient possible */
    (void)pop(P[1][0].pile_herisson); P[1][0].nb_herisson--;
    assert(can_move_right(P, nb_lignes, nb_colonnes, 1, 1));

    /* --- do_move_right: déplace bien le sommet et met à jour les compteurs --- */
    int before_src = P[1][1].nb_herisson;
    int before_dst = P[1][2].nb_herisson;
    do_move_right(P, 1, 1);
    assert(P[1][1].nb_herisson == before_src - 1);
    assert(P[1][2].nb_herisson == before_dst + 1);
    /* Le jeton déplacé était 0; il doit être au sommet sur (1,2) */
    assert(peek(P[1][2].pile_herisson, 0) == 0);

    /* --- can_move_vertical: le sommet doit appartenir au joueur --- */
    /* Place un sommet joueur 1 en (2,0) */
    push(P[2][0].pile_herisson, 1);
    P[2][0].nb_herisson++;
    /* Joueur 0 ne peut pas bouger ce sommet */
    assert(!can_move_vertical(P, nb_lignes, nb_colonnes, 2, 0, -1, /*player=*/0));
    /* Joueur 1 peut bouger vers le haut */
    assert(can_move_vertical(P, nb_lignes, nb_colonnes, 2, 0, -1, /*player=*/1));

    /* Piège + hérisson à gauche bloque la sortie verticale */
    P[2][0].est_piegee = true;
    /* Mettre un hérisson à gauche de (2,0) n’est pas possible (bord gauche),
       on teste donc sur (2,1) pour valider la règle. */
    push(P[2][1].pile_herisson, 1); P[2][1].nb_herisson++;
    P[2][1].est_piegee = true;
    push(P[2][0].pile_herisson, 3); P[2][0].nb_herisson++; /* un hérisson à gauche de (2,1) */
    /* Le sommet de (2,1) est 1 (joueur 1), mais piège + qqn à gauche => interdit */
    assert(!can_move_vertical(P, nb_lignes, nb_colonnes, 2, 1, -1, 1));

    /* --- do_move_vertical: déplace bien le sommet et MAJ compteurs --- */
    /* On autorise le move en nettoyant la condition de piège */
    P[2][1].est_piegee = false;
    int v_before_src = P[2][1].nb_herisson;
    int v_before_dst = P[1][1].nb_herisson;
    do_move_vertical(P, 2, 1, -1);
    assert(P[2][1].nb_herisson == v_before_src - 1);
    assert(P[1][1].nb_herisson == v_before_dst + 1);
    assert(peek(P[1][1].pile_herisson, 0) == 1);

    /* Nettoyage et restauration */
    destroy_plateau_local(P, nb_lignes, nb_colonnes);
    nb_lignes = oldL;
    nb_colonnes = oldC;

    printf("✅ test_round_utils: OK\n");
    return 0;
}
