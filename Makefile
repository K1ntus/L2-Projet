CC=gcc
AR=ar r
CFLAGS=-Wall -std=c99 -g
LDFLAGS=-L. -lgame
TEST_EXEC=test undead_text 
OBJ_TEST= $(.c=.o)
#LDFLAGS : mettre les librairy Ã  inclure dedans

all: $(TEST_EXEC)

libgame.a: game_lib.o game_io.o
	$(AR) libgame.a game_io.o game_lib.o
	
undead_text: undead_text.o game_lib.o game_io.o
	$(CC) $(CFLAGS) -o undead_text undead_text.o game_lib.o game_io.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c

game_lib.o: game_lib.c
	$(CC) $(CFLAGS) -c game_lib.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: test.o game_lib.o
	$(CC) $(CFLAGS) -o test test.o game_lib.o

.PHONY : clean
clean:
	rm test
	rm test.o
	rm undead_text
	rm undead_text.o
	rm game_jordan.o
	rm *.a
	rm *.txt

# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)

