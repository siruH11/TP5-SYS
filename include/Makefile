LDFLAGS = -g
CFLAGS = -Wall -Wextra -Wno-unused-parameter -Werror

prog: test.o pile.o
	gcc $(LDFLAGS) $^ -o $@

test.o: test.c pile.h
	gcc $(CFLAGS) -c $<

pile.o: pile.c pile.h
	gcc $(CFLAGS) -c $<

plateau.o: plateau.c plateau.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f test.o pile.o prog

.PHONY: clean 