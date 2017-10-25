CC=gcc
AR=ar r
LIBDIR =./include/
INCLUDES=-I $(LIBDIR)
CFLAGS=-Wall -std=c99 $(INCLUDES)
LDFLAGS=-L. -lgame
TESTS_EXECS=./test
#LDFLAGS : mettre les librairy à inclure dedans

all: undead_text tests

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o
	
undead_text: undead_text.o libgame.a
	$(CC) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c


tests: test.o game12.o
	$(CC) -o test test.o $(LDFLAGS)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: tests
	valgrind --log-file=log.txt --leak-check=full --error-exitcode=2 $(TESTS_EXECS)


.PHONY : clean
clean:
	rm undead_text
	rm *.a
	rm undead_text.o
	rm test.o
	rm test
# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)
