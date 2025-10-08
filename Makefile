CC       = gcc
CFLAGS   = -Wall -Wextra -Wno-unused-parameter -Werror -Iinclude
LDFLAGS  = -g

SRC      = include/pile.c include/plateau.c affiche_plateau.c test.c
OBJ      = $(SRC:.c=.o)
EXEC     = prog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXEC)

# règle générique pour compiler n'importe quel .c -> .o (où qu'il soit)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
