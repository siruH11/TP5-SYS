#include "include/affiche_plateau.h"
#include <ctype.h>

/*idée on va faire 4 fonctions pour print les 4 lignes de chaque colonne*/

/*
Récupère le k-ième hérisson depuis le sommet de la pile (0 = sommet),
et renvoie le caractère correspondant (A, B, C, ... ou chiffre si > 26).
Retourne ' ' si aucun hérisson à cet emplacement.
 */
static char get_token_char(plateau P, int i, int j, int k) {
    if (!P || !P[i][j].pile_herisson) return ' ';
    if (k < 0 || k >= P[i][j].pile_herisson->taille) return ' ';
    int e = peek(P[i][j].pile_herisson, k);
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
        printf(" row   ");
    }
    putchar('\n');
    printf("     ");
    for (int j=0; j < C; j++) {
        printf("   %c   ",'a'+j);
    }
}

static void print_firstline_rows(plateau P, int i, int C) {
    printf("     ");  // petit décalage initial
    for (int j = 0; j < C; j++) {
        if (P[i][j].est_piegee) {
            printf("  vvv  ");
        } else {
            printf("  ---  ");
        }
    }
    putchar('\n');
}

/**
Affiche le lignes 2 et 3 d'une case : le premier  hérisson empilés dans dans les premieres cases puis les autres..
 */
static void print_hedgehog_rows(plateau P, int i, int C) {
    /*ligne 2*/
    printf("line ");
    for (int j = 0; j < C; j++) {
        /*récupération du premier hérisson sur la case*/
        int h = P-[i][j].nb_herisson;
        char a = get_token_char(P, i, j, 0);

        /*la case est-elle infectée ?*/
        char z1 = '|', z2 = '|';
        if (P[i][j].est_piegee) z1 = '>', z2 = '<';

        if (h >= 1) {
            printf(" %c%c%c%c%c ", z1, a, a, a, z2);
        } else {
            printf(" %c   %c ", z1, z2);
        }
    }
    putchar('\n');

    /*ligne 3*/
    printf("  %d  ",i);
    for (int j = 0; j < C; j++) {
        /*récupération des hérissons sur la case*/
        int h = P[i][j].nb_herisson;
        char b = ' ', c = ' ', d = ' ', z1 = '|', z2 = '|';
        if (h > 1) b = tolower(get_token_char(P, i, j, 1));
        if (h > 2) c = tolower(get_token_char(P, i, j, 2));
        if (h > 3) d = tolower(get_token_char(P, i, j, 3));

        /*la case est-elle infectée ?*/
        if (P[i][j].est_piegee) z1 = '>', z2 = '<';

        if (h==1) {
            printf(" %c   %c ",z1,z2);
        }
        else if (h==2) {
            printf(" %c%c%c%c%c ",z1,b,b,b,z2);
        }
        else if (h==3) {
            printf(" %c%c  %c%c ",z1,b,c,z2);
        }
        else if (h>3) {
            printf(" %c%c%c%c%c ",z1,b,c,d,z2);
        }
        else {
            printf(" %c   %c ",z1,z2);
        }
    }
    putchar('\n');
}

/*
Affiche la 4eme ligne : le nombre de hérissons empilés, format "-n-".
 */
static void print_stack_counts(plateau *P, int i, int C) {
    printf("     ");
    for (int j = 0; j < C; j++) {
        if (P[i][j].est_piegee) {
            printf("  ^^^  ");
        }
        else {
            int h = P[i][j].nb_herisson;
            if (h > 9) h = 9;
            if (h>0) printf("  -%d-  ", h);
            else printf("  ---  ");
        }
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
    if (!P || L <= 0 || C <= 0) {
        puts("(plateau vide)");
        return;
    }

    print_column_headers(C);
    for (int i = 0; i < L; i++) {
        putchar('\n');
        print_firstline_rows(P, i, C);
        print_hedgehog_rows(P, i, C);
        print_stack_counts(P, i, C);
    }
    putchar('\n');
    print_column_headers(C);
}
