#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

pile_c* create_pile(int capacite){  
    equipe* tab_stock = malloc(capacite*sizeof(equipe));
    pile_c* new_pile = malloc(sizeof(pile_c));
    new_pile->taille = 0;new_pile->prochain_ajout = 0;
    new_pile->tab_stockage = tab_stock;new_pile->capacite = capacite;
    return(new_pile);
}

void push(pile_c* p,int x){
    p->tab_stockage[p->prochain_ajout]=x;
    p->prochain_ajout = (p->prochain_ajout+1)%p->capacite;//tableau cyclique
    p->taille++;
}

equipe pop(pile_c* p){
    if (p->taille == 0) {perror("pile vide"); exit(EXIT_FAILURE);}
    if (p->prochain_ajout ==0){p->prochain_ajout = p->capacite -1;}
    else{p->prochain_ajout--;}
    return(p->tab_stockage[p->prochain_ajout]); //comme on a decrementé 
    //ajout, on pointe le premeir elemeent de la pile
}

int taille(pile_c* p){return(p->taille);}

equipe top(pile_c* p){
    if (p->taille == 0) {perror("pile vide"); exit(EXIT_FAILURE);}
    if (p->prochain_ajout ==0){return(p->tab_stockage[p->capacite -1]);}
    else{return(p->tab_stockage[p->prochain_ajout-1]);}
}

equipe peek(pile_c *p ,int pos){
    if (p->taille <= pos) {perror("la pile ne contient pas assez d'elements"); exit(EXIT_FAILURE);}
    if (p->prochain_ajout <= pos){return(p->tab_stockage[p->capacite -1 -(pos - p->prochain_ajout)]);}
    //revenir à cap-1 prend pos - p->prochain_ajout etapes
    else{return(p->tab_stockage[p->prochain_ajout-(pos+1)]);}
}

void libere_pile(pile_c* p){
    free(p->tab_stockage);
    free(p);
}

bool is_empty(pile_c* p){
    return(p->taille == 0);
}