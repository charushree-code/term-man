HEADERS = std_objects.h ghost.h map.h pacman.h ghost_ai.h level_defs.h

all: term_man

term_man: term_man.o
	gcc map.o ghost.o ghost_ai.o std_objects.o pacman.o term_man.o -o term-man -std=c99 -lcurses

term_man.o: ghost.o ghost_ai.o std_objects.o pacman.o map.o term_man.c $(HEADERS)
	gcc term_man.c -c -std=c99
	
ghost_ai.o: ghost_ai.c $(HEADERS)
	gcc ghost_ai.c -c -std=c99

ghost.o: ghost.c $(HEADERS)
	gcc ghost.c -c -std=c99
	
pacman.o: pacman.c $(HEADERS)
	gcc pacman.c -c -std=c99
	
map.o: map.c $(HEADERS)
	gcc map.c -c -std=c99
	
std_objects.o: std_objects.c $(HEADERS)
	gcc std_objects.c -c -std=c99
	
clean:
	rm -f test2 *.o
