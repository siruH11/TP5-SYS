#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_pile.h"
#include "test_affichage.h"

int main() {
    test_pile();
    test_affiche_plateau();
    test_plateau();

    return 0;
}
