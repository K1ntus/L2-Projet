CC=gcc
AR=ar r
CFLAGS=-Wall -std=c99 -g
LDFLAGS=-L. -lgame
TEST_EXEC=test undead_text 
OBJ_TEST= $(.c=.o)
#LDFLAGS : mettre les librairy Ã  inclure dedans

all: $(TEST_EXEC)

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o
	
undead_text: undead_text.o libgame.a
	$(CC) $(CFLAGS) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c

game_jordan.o: game_jordan.c
	$(CC) $(CFLAGS) -c game_jordan.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: test.o game_jordan.o game.o
	$(CC) $(CFLAGS) -o test test.o $(LDFLAGS)

.PHONY : clean
clean:
	ls | grep -v Makefile | xargs rm
	rm *.a
	rm *.txt

# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)

