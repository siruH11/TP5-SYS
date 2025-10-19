#include "round_utils.h"
#include "globales.h"
#include "affiche_plateau.h"
#include "pile.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* un round , renvoie true si un joueur a gagné false sinon*/
bool play_round(plateau P, int player_id) {
    if (!P) return false;

    int dice = roll_dice();
    int line = dice - 1;

    printf("\n=== Tour du joueur %c ===\n", 'A' + player_id);
    printf("Dé: %d", dice);
    putchar('\n');
    affiche_plateau_ex(P, line);

    /* Déplacement vertical optionnel (un seul hérisson du joueur) */
    printf("Déplacement vertical (optionnel) ? (o/N) ");
    int c = getchar();
    if (c != '\n') flush_line();
    if (c=='o'||c=='O'||c=='y'||c=='Y') {
        while (1) {
            int i, j; char d;
            printf("Saisis: i j puis (u=up, d=down), ou -1 pour passer: ");
            if (scanf("%d", &i) != 1) { flush_line(); break; }
            if (i < 0) { flush_line(); break; }
            if (scanf("%d %c", &j, &d) != 2) { flush_line(); continue; }
            flush_line();
            int di = (d=='u'||d=='U') ? -1 : (d=='d'||d=='D') ? +1 : 0;
            if (can_move_vertical(P, i, j, di, player_id)) {
                do_move_vertical(P, i, j, di);
                break;
            } else {
                printf("Mouvement vertical invalide, réessaie.\n");
            }
        }
        printf("Dé: %d", dice);
        putchar('\n');
        affiche_plateau_ex(P, line);
    }

    /* Déplacement horizontal obligatoire sur la ligne tirée */
    int cols[128];
    int n = list_right_moves(P, line, cols, (int)(sizeof cols / sizeof *cols));
    if (n == 0) {
        printf("Aucun hérisson ne peut avancer sur la ligne %d. Tour terminé.\n", line+1);
        return false;
    }

    printf("Choisis une colonne à avancer vers la droite parmi: ");
    for (int k = 0; k < n; ++k) printf("%c  ", 'a' + cols[k]);
    printf("\nEntre l'indice 0 et %d: ", n-1);

    int idx = -1;
    while (scanf("%d", &idx) != 1 || idx < 0 || idx >= n) {
        flush_line();
        printf("Indice invalide, recommence: ");
    }
    flush_line();

    do_move_right(P, line, cols[idx]);

    /* Affiche et teste condition de fin */
    affiche_plateau_ex(P, -1);

    if(player_id == nb_joueurs-1){
        for(int l = 0 ; l< nb_joueurs;l++){
            if (count_arrivals_player(P, l) >= nb_herisson -1){
                joueur_assez_herisson = true;
                printf("\n %d \n", l);
                gagnants[l] =true;
            }
        }
    }
    if (joueur_assez_herisson) {
        printf(">>>partie terminée, les equipes ");
        for(int l = 0 ; l<nb_joueurs;l++){
            if(gagnants[l]){printf("%c ",'A'+l);}
        }
        printf("ont gagnées, BRAVO!\n");
        return true;
    }
    return false;
}
