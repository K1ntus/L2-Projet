CC=gcc
AR=ar r
LIBDIR =./include/
INCLUDES=-I $(LIBDIR)
CFLAGS=-Wall -std=c99 $(INCLUDES)
LDFLAGS=-L. -lgame
#LDFLAGS : mettre les librairy à inclure dedans

all: undead_text

undead_text: undead_text.o libgame.a
	$(CC) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o

game_test: game_test.o libgame.a
	$(CC) -o game_test game_test.o $(LDFLAGS)

game_test.o: game_test.c
	$(CC) $(CFLAGS) -c game_test.c 

.PHONY : clean
clean:
	rm undead_text
	rm *.a
	rm undead_text.o
	rm test.o
	rm test
# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)

