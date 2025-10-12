#include "round.h"
#include "round_utils.h"
#include "plateau.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int test_round() {
    plateau P = create_plateau();
    play_round(P,0);
    return 0;
}