#include "round_utils.h"
#include "globales.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int roll_die(int L) {
    static int seeded = 0;
    if (!seeded) { srand((unsigned)time(NULL)); seeded = 1; }
    return (rand() % L) + 1; // 1..L
}

static int anyone_on_left(const plateau P, int C, int i, int j) {
    for (int x = 0; x < j; ++x) if (P[i][x].nb_herisson > 0) return 1;
    return 0;
}

bool can_move_right(const plateau P, int L, int C, int i, int j) {
    (void)L;
    if (i < 0 || j < 0 || j >= C-1) return false;              // pas de case à droite
    if (P[i][j].nb_herisson == 0) return false;       // vide
    if (P[i][j].est_piegee && anyone_on_left(P, C, i, j)) return false; // bloqué par la règle du piège
    return true;
}

void do_move_right(plateau P, int i, int j) {
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    push(P[i][j+1].pile_herisson, tok);
    P[i][j+1].nb_herisson++;
}

bool can_move_vertical(const plateau P, int L, int C, int i, int j, int di, int player_id) {
    (void)C;
    if (i < 0 || i >= L || j < 0) return false;
    if (di != -1 && di != +1) return false;
    int ni = i + di;
    if (ni < 0 || ni >= L) return false;
    if (P[i][j].nb_herisson == 0) return false;

    // sommet doit appartenir au joueur
    int top = peek(P[i][j].pile_herisson, 0);
    if (top < 0) return false;
    if (top != player_id) return false; // 0->A, 1->B, ... (tes entiers 0..25)

    // pas de sortie de piège si des hérissons à gauche
    if (P[i][j].est_piegee && anyone_on_left(P, C, i, j)) return false;

    return true;
}

void do_move_vertical(plateau P, int i, int j, int di) {
    int tok = pop(P[i][j].pile_herisson);
    if (tok < 0) return;
    P[i][j].nb_herisson--;
    push(P[i+di][j].pile_herisson, tok);
    P[i+di][j].nb_herisson++;
}

static int list_right_moves(const plateau P, int L, int C, int line, int cols_out[], int cap) {
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
    int count = 0;
    int last = C - 1;
    for (int i = 0; i < L; ++i) {
        int h = P[i][last].nb_herisson;
        for (int k = 0; k < h; ++k) {
            int tok = peek(P[i][last].pile_herisson, k); // k=0 sommet, k=h-1 fond
            if (tok == player_id) count++;
        }
    }
    return count;
}

bool play_round(plateau P, int L, int C, int player_id) {
    int dice = roll_die(L);
    int line = dice - 1;

    printf("\n=== Tour du joueur %c ===\n", 'A' + player_id);
    printf("Dé: %d  -> ligne %d\n", dice, line);
    affiche_plateau_ex(P, L, C, line);

    // — Déplacement vertical optionnel d'UN hérisson du joueur (±1)
    printf("Déplacement vertical (optionnel) ? (o/N) ");
    int c = getchar(); if (c != '\n') { int t; while ((t=getchar())!='\n' && t!=EOF){} }
    if (c=='o'||c=='O'||c=='y'||c=='Y') {
        while (1) {
            int i,j; char d;
            printf("Saisis: i j d (d=u pour up, d pour down), ou -1 pour passer: ");
            if (scanf("%d", &i) != 1) { while ((c=getchar())!='\n'&&c!=EOF){} break; }
            if (i < 0) { while ((c=getchar())!='\n'&&c!=EOF){} break; }
            if (scanf("%d %c", &j, &d) != 2) { while ((c=getchar())!='\n'&&c!=EOF){} continue; }
            while ((c=getchar())!='\n'&&c!=EOF){} // flush
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

    // — Déplacement horizontal OBLIGATOIRE sur la ligne tirée, si possible
    int cols[128];
    int n = list_right_moves(P, L, C, line, cols, 128);
    if (n == 0) {
        printf("Aucun hérisson ne peut avancer sur la ligne %d. Tour terminé.\n", line);
        return false;
    }

    printf("Choisis une colonne à avancer vers la droite parmi: ");
    for (int k = 0; k < n; ++k) {
        printf("%c  ", 'a' + cols[k]); // affichage lisible
    }
    printf("\nEntre l'indice 0..%d: ", n-1);

    int idx=-1;
    while (scanf("%d", &idx) != 1 || idx < 0 || idx >= n) {
        while ((c=getchar())!='\n'&&c!=EOF){}; printf("Indice invalide, recommence: ");
    }
    while ((c=getchar())!='\n'&&c!=EOF){} // flush

    do_move_right(P, line, cols[idx]);

    // — Affiche et teste condition de fin
    affiche_plateau_ex(P, L, C, -1);

    int arrived = count_arrivals_player(P, L, C, player_id);
    if (arrived >= 3) {
        printf(">>> L'équipe %c a %d hérissons en dernière colonne. Fin de partie !\n",
               'A'+player_id, arrived);
        return true;
    }
    return false;
}
