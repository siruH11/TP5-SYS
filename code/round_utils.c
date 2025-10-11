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
    return (rand() % 6) + 1;    
}

/* Y a-t-il un hérisson quelque part à gauche de (i,j) ? */
static int anyone_on_left(const plateau P, int C, int i, int j) {
    if (!P || i < 0 || j <= 0 || C <= 0) return 0;
    for (int x = 0; x < j; ++x) {
        if (P[i][x].nb_herisson > 0) return 1;
    }
    return 0;
}

/* Mouvement horizontal */
bool can_move_right(const plateau P, int L, int C, int i, int j) {
    (void)L;
    if (!P) return false;
    if (i < 0 || j < 0 || j >= C-1) return false;          /* pas de case à droite */
    if (P[i][j].nb_herisson == 0) return false;            /* case vide */
    if (P[i][j].est_piegee && anyone_on_left(P, C, i, j))  /* règle du piège */
        return false;
    return true;
}

void do_move_right(plateau P, int i, int j) {
    if (!P) return;
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    push(P[i][j+1].pile_herisson, tok);
    P[i][j+1].nb_herisson++;
}

/* Mouvement vertical */
bool can_move_vertical(const plateau P, int L, int C, int i, int j, int di, int player_id) {
    if (!P) return false;
    if (i < 0 || i >= L || j < 0 || j >= C) return false;
    if (di != -1 && di != +1) return false;
    int ni = i + di;
    if (ni < 0 || ni >= L) return false;
    if (P[i][j].nb_herisson == 0) return false;

    /* Le sommet doit appartenir au joueur */
    int top = peek(P[i][j].pile_herisson, 0);
    if (top < 0 || top != player_id) return false;

    /* Pas de sortie de piège si hérissons à gauche */
    if (P[i][j].est_piegee && anyone_on_left(P, C, i, j)) return false;

    return true;
}

void do_move_vertical(plateau P, int i, int j, int di) {
    if (!P) return;
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    push(P[i+di][j].pile_herisson, tok);
    P[i+di][j].nb_herisson++;
}

/*Utilitaires de tour*/
static int list_right_moves(const plateau P, int L, int C, int line, int cols_out[], int cap) {
    (void)L;
    if (!P || !cols_out || cap <= 0 || line < 0 || line >= L) return 0;
    int n = 0;
    for (int j = 0; j < C-1; ++j) {
        if (can_move_right(P, L, C, line, j)) {
            if (n < cap) cols_out[n] = j;
            n++;
        }
    }
    return n;
}

static int count_arrivals_player(const plateau P, int L, int C, int player_id) {
    (void)L;
    if (!P || C <= 0) return 0;
    int count = 0;
    int last = C - 1;
    for (int i = 0; i < L; ++i) {
        int h = P[i][last].nb_herisson;
        for (int k = 0; k < h; ++k) {
            int tok = peek(P[i][last].pile_herisson, k); /* k=0 sommet */
            if (tok == player_id) count++;
        }
    }
    return count;
}

/* Lecture/flush ligne standard (évite mélanges scanf/getchar) */
static void flush_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

/*Un tour de jeu interactif*/
bool play_round(plateau P, int L, int C, int player_id) {
    if (!P) return false;

    int dice = roll_dice();
    int line = dice - 1;

    printf("\n=== Tour du joueur %c ===\n", 'A' + player_id);
    printf("Dé: %d", dice);
    affiche_plateau_ex(P, L, C, line);

    /* Déplacement vertical optionnel (un seul hérisson du joueur) */
    printf("Déplacement vertical (optionnel) ? (o/N) ");
    int c = getchar();
    if (c != '\n') flush_line();
    if (c=='o'||c=='O'||c=='y'||c=='Y') {
        while (1) {
            int i, j; char d;
            printf("Saisis: i j d (u=up, d=down), ou -1 pour passer: ");
            if (scanf("%d", &i) != 1) { flush_line(); break; }
            if (i < 0) { flush_line(); break; }
            if (scanf("%d %c", &j, &d) != 2) { flush_line(); continue; }
            flush_line();
            int di = (d=='u'||d=='U') ? -1 : (d=='d'||d=='D') ? +1 : 0;
            if (can_move_vertical(P, L, C, i, j, di, player_id)) {
                do_move_vertical(P, i, j, di);
                break;
            } else {
                printf("Mouvement vertical invalide, réessaie.\n");
            }
        }
        affiche_plateau_ex(P, L, C, line);
    }

    /* Déplacement horizontal obligatoire sur la ligne tirée */
    int cols[128];
    int n = list_right_moves(P, L, C, line, cols, (int)(sizeof cols / sizeof *cols));
    if (n == 0) {
        printf("Aucun hérisson ne peut avancer sur la ligne %d. Tour terminé.\n", line);
        return false;
    }

    printf("Choisis une colonne à avancer vers la droite parmi: ");
    for (int k = 0; k < n; ++k) {
        printf("%c  ", 'a' + cols[k]);
    }
    printf("\nEntre l'indice 0..%d: ", n-1);

    int idx = -1;
    while (scanf("%d", &idx) != 1 || idx < 0 || idx >= n) {
        flush_line();
        printf("Indice invalide, recommence: ");
    }
    flush_line();

    do_move_right(P, line, cols[idx]);

    /* Affiche et teste condition de fin */
    affiche_plateau_ex(P, L, C, -1);

    int arrived = count_arrivals_player(P, L, C, player_id);
    if (arrived >= 3) {
        printf(">>> L'équipe %c a %d hérissons en dernière colonne. Fin de partie !\n",
               'A'+player_id, arrived);
        return true;
    }
    return false;
}
