CC=gcc
AR=ar r
LIBDIR =./include/
INCLUDES=-I $(LIBDIR)
CFLAGS=-Wall -std=c99 $(INCLUDES)
LDFLAGS=-L. -lgame
#LDFLAGS : mettre les librairy à inclure dedans

all: undead_text

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o

undead_text: undead_text.o libgame.a
	$(CC) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c


a_test: a_test.o libgame.a
	$(CC) -o a_test a_test.o $(LDFLAGS)

a_test.o: a_test.c
	$(CC) $(CFLAGS) -c a_test.c


.PHONY : clean
clean:
	rm undead_text
	rm *.a
	rm undead_text.o
	rm a_test.o
	rm a_test
# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)
