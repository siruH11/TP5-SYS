#ifndef UTILS
#define UTILS

#include <stdbool.h>
typedef int equipe;

typedef struct pile{
    int taille;
    int prochain_ajout;
    equipe* tab_stockage;
    int capacite;
}pile_c;

pile_c* create_pile(int capacite);
void push(pile_c* p,int x);
equipe pop(pile_c* p);
int taille(pile_c* p);
equipe top(pile_c* p);
equipe peek(pile_c *p ,int pos);//renvoie le pos-ieme elem de la pile
void libere_pile(pile_c* p);
bool is_empty(pile_c* p);

#endif