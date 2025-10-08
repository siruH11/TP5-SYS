#include "include/affiche_plateau.h"

/*
Récupère le k-ième hérisson depuis le sommet de la pile (0 = sommet),
et renvoie le caractère correspondant (A, B, C, ... ou chiffre si > 26).
Retourne ' ' si aucun hérisson à cet emplacement.
 */
static char get_token_char(plateau *P, int i, int j, int k) {
    if (!P || !P->plateau || !P->plateau[i][j].pile_herisson) return ' ';
    if (k < 0 || k >= P->plateau[i][j].pile_herisson->taille) return ' ';
    int e = peek(P->plateau[i][j].pile_herisson, k);
    if (e < 0) return ' ';
    if (e < 26) return 'A' + e;
    if (e < 36) return '0' + (e - 26);
    return '*';
}

/*
Affiche la ligne d'entêtes des colonnes : row a, row b, ...
 */
static void print_column_headers(int C) {
    printf("      ");
    for (int j = 0; j < C; j++) {
        printf("row %c ", (char)('a' + j));
    }
    putchar('\n');
}

/*
Affiche une ligne de séparation horizontale +---+---+...
 */
static void print_horizontal_separator(int C) {
    printf("      ");
    for (int j = 0; j < C; j++) {
        printf("+---+");
    }
    putchar('\n');
}

/**-
Affiche la première sous-ligne : les 3 premiers hérissons empilés dans chaque case.
 */
static void print_hedgehog_rows(plateau *P, int i, int C) {
    for (int j = 0; j < C; j++) {
        int h = P->plateau[i][j].nb_herisson;
        char a = ' ', b = ' ', c = ' ';
        if (h > 0) a = get_token_char(P, i, j, 0);
        if (h > 1) b = get_token_char(P, i, j, 1);
        if (h > 2) c = get_token_char(P, i, j, 2);
        printf("|%c%c%c|", a, b, c);
    }
    putchar('\n');
}

/*
Affiche la deuxième sous-ligne : "vvv" pour les cases piégées, "   " sinon.
 */
static void print_trap_rows(plateau *P, int i, int C) {
    for (int j = 0; j < C; j++) {
        if (P->plateau[i][j].est_piegee)
            printf("|vvv|");
        else
            printf("|   |");
    }
    putchar('\n');
}

/*
Affiche la troisième sous-ligne : le nombre de hérissons empilés, format "-n-".
 */
static void print_stack_counts(plateau *P, int i, int C) {
    for (int j = 0; j < C; j++) {
        int h = P->plateau[i][j].nb_herisson;
        if (h > 9) h = 9;
        printf("|-%d-|", h);
    }
    putchar('\n');
}

/**
 Fonction principale d'affichage du plateau :
 - Entêtes en haut et en bas
 - Pour chaque ligne : hérissons, pièges, compteurs
 */
void affiche_plateau_ex(plateau *P, int L, int C, int dice_line) {
    (void)dice_line; // ignoré pour l'instant
    if (!P || !P->plateau || L <= 0 || C <= 0) {
        puts("(plateau vide)");
        return;
    }

    print_column_headers(C);
    for (int i = 0; i < L; i++) {
        print_horizontal_separator(C);
        printf("line %-2d ", i + 1);
        print_hedgehog_rows(P, i, C);
        printf("       ");
        print_trap_rows(P, i, C);
        printf("       ");
        print_stack_counts(P, i, C);
    }
    print_horizontal_separator(C);
    print_column_headers(C);
}
