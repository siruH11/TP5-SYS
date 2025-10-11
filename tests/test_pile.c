#include "include/pile.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test_pile(void){
    pile_c* p = create_pile(nb_herisson*nb_joueurs);
    push(p,1);
    assert(p->prochain_ajout==1);
    assert(top(p)==1);
    push(p,2);push(p,3);push(p,4);
    assert(top(p)==4);
    assert(peek(p,1)==3 && peek(p,2)==2);
    free(p);

}