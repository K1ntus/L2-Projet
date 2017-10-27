CC=gcc
AR=ar r
CFLAGS=-Wall -std=c99 -g
LDFLAGS=-L. -lgame
TEST_EXEC=test0 test1 test2 test3

#LDFLAGS : mettre les librairy à inclure dedans

all: undead_text

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o
	
undead_text: undead_text.o libgame.a
	$(CC) $(CFLAGS) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c

test0: test.o game.o
	$(CC) $(CFLAGS) -o test0 test.o game.o 

test1: test.o game10.o
	$(CC) $(CFLAGS) -o test1 test.o game10.o 

test2: test.o game11.o
	$(CC) $(CFLAGS) -o test2 test.o game11.o 

test3: test.o game12.o
	$(CC) $(CFLAGS) -o test3 test.o game12.o 

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: $(TEST_EXEC)
	sh script.sh

.PHONY : clean
clean_test:
	rm test*.o
	rm test0
	rm test1
	rm test2
	rm test3
clean:
	rm undead_text
	rm *.a
	rm undead_text.o
	rm test.o

# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)
