#include "game.h"
#include <assert.h>

#define COLONNE 4
#define LINE 4

#define nbVampire 2;
#define nbGhost 2;
#define nbZombie 5;

const NB_DIR 4;


struct game_s{
 int ** matrice;
 int vampires;
 int ghosts;
 int zombies;
 int valuesNorth[4];
 int valuesSouth[4];
 int valuesEast[4];
 int valuesWest[4];
}

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

		game g = malloc(sizeof(struct game_s));
    if(g==NULL){
      fprintf(stderr,"Not enough memory!\n");
      return EXIT_FAILURE;
    }
		g->matrice = initmatrice(COLONNE,LINE);
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
    g->valuesSouth[4] = labels[1][i]; // ..    ..   .. 1      ..    . valueSouth
    g->valuesEast[4] = labelt[2][i]; //  ..    ..   .. 2      ..    . valueEast
    g->valuesWest[4] = labels[3][i]; //  ..    ..   .. 3      ..    . valueWest
  }
  for(int i=0 ; i<LINE ; i++){
    for (int j=0 ; j<COLONNE ; j++){
      g->matrice
    }
  }

}
