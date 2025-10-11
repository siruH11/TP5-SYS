#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_pile.h"
#include "test_affichage.h"
#include "test_round_utils.h"

int main() {
    test_pile();
    test_plateau();
    test_round_utils();
    return 0;
}
