CC=gcc
AR=ar r
CFLAGS=-Wall -std=c99 -g
LDFLAGS=-L. -lgame
TEST_EXEC=test0 test1 test2 test3 undead_text
OBJ_TEST= $(.c=.o)
#LDFLAGS : mettre les librairy à inclure dedans

all: $(TEST_EXEC)

libgame.a: game.o game_io.o
	$(AR) libgame.a game_io.o game.o
	
undead_text: undead_text.o libgame.a
	$(CC) $(CFLAGS) -o undead_text undead_text.o $(LDFLAGS)

undead_text.o: undead_text.c
	$(CC) $(CFLAGS) -c undead_text.c

test0: test.o $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test0 $< game.o 

test1: test.o $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test1 $< game10.o 

test2: test.o $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test2 $< game11.o 

test3: test.o $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test3 $< game12.o 

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: $(TEST_EXEC)
	sh script.sh

.PHONY : clean
clean:
	ls | grep -v "\." | grep -v Makefile | xargs rm
	rm *.a
	rm *.txt

# /!\ NE PAS CLEAR LES .O DE /OBJ (ie pas de rm *.o)
