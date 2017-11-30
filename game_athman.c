#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include <assert.h>

#define COLONNE 4
#define LINE 4

#define nbVampire 2;
#define nbGhost 2;
#define nbZombie 5;

typedef struct game_s* game;

struct game_s{
 int ** matrice;
 int vampires;
 int ghosts;
 int zombies;
 int valuesNorth[4];
 int valuesSouth[4];
 int valuesEast[4];
 int valuesWest[4];
};

int ** initmatrice(int x,int y){
 int ** t = (int **)malloc(x*sizeof(int*));
 assert(t);
 int i;
 for(i=0 ; i<x ; i++){
   t[i]= (int *)calloc(y,sizeof(int));
   assert(t[i]);
   for(int j=0 ; j<y ; j++){
     t[i][j]=EMPTY;
   }
 }
 return t;
}

game new_game(){

		game g = malloc(sizeof(game));
    if(g==NULL){
      fprintf(stderr,"Not enough memory!\n");
      return 1;
    }
		g->matrice = initmatricc(COLONNE,LINE);
		g->vampires = 0;
		g->ghosts = 0;
		g->zombies = 0;

		return g;
}

game setup_new_game(int *labels[NB_DIR], content * board, int required_nb_ghosts,  int required_nb_vampires, int required_nb_zombies){
  game g = new_game();
  g->vampires = required_nb_vampires;
  g->ghosts = required_nb_ghosts;
  g->zombies = required_nb_zombies;
  for(int i=0 ; i<4 ; i++){
    g->valuesNorth[i] = labels[0][i]; // on supose que 0 equivalent a valueNorth
    g->valuesSouth[i] = labels[1][i]; // ..    ..   .. 1      ..    . valueSouth
    g->valuesEast[i] = labels[2][i]; //  ..    ..   .. 2      ..    . valueEast
    g->valuesWest[i] = labels[3][i]; //  ..    ..   .. 3      ..    . valueWest
  }

  int caze = 0; // caze parce que case c'est un reserver au switch case
  for(int i=0 ; i<LINE ; i++){
    for (int j=COLONNE-1 ; j>0 ; j--){
      g->matrice[i][j] = board[caze];
      caze ++;
    }
  }

  return g;

}

void add_mirror(game g, int dir, int col, int line){
  assert(g);
  if( dir=0 )
    g->matrice[line][col] = ANTIMIRROR ;
  else
    g->matrice[line][col] = MIRROR ;
}

delete_game (game g){
  assert(g);
  free(g->matrice);
  free(g);
}
