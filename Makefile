CC       = gcc 
CFLAGS   = -Wall -Wextra -Wno-unused-parameter -Werror -Iinclude
LDFLAGS  = -g

SRC      = code/pile.c code/plateau.c code/affiche_plateau.c code/globales.c 
TEST = tests/test_affichage.c tests/test_pile.c tests/test.c
#fichier c dont on veut le.o
OBJ_SRC     = $(SRC:.c=.o)
OBJ_TEST = $(TEST:.c=.o)

test: $(TEST)

$(TEST): $(OBJ_SRC) $(OBJ_TEST)
	$(CC) $(LDFLAGS) $(OBJ_SRC) $(OBJ_TEST) -o test

# règle générique pour compiler n'importe quel .c -> .o (où qu'il soit)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
