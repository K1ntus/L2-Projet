#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "../header/game.h"
#include "../header/game_io.h"

#include "./game_util.c"

#define NB_MIRROR 4


content convert_int_to_mirror(int val){
	switch(val){
		case 0:	return MIRROR; break;
		case 1:	return ANTIMIRROR; break;
		case 2:	return HMIRROR; break;
		case 3:	return VMIRROR; break;
		default:	return EMPTY; break;
	}
	return EMPTY;//Error case ?
}


int random_between_x_and_y(int nMin, int nMax){
	int res = 0;
 	res = rand()%((nMax+1)-nMin) + nMin;
	return res;
}


game new_game_generation(void){

  srand(time(NULL));

  int width = random_between_x_and_y(4,7), height = random_between_x_and_y(4,8);
  int nb_cells = width*(height)-1;
  int nb_mirror = 0;

  game g = new_game_ext(width,height);

  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      if(random_between_x_and_y(0,1) == 0){
        add_mirror_ext(g, convert_int_to_mirror(random_between_x_and_y(0,NB_MIRROR)),x,y);
        nb_mirror +=1;
      }
    }
  }

  int nb_monsters = nb_cells - nb_mirror;
    set_required_nb_monsters(g, ZOMBIE, random_between_x_and_y(0,nb_monsters));

    set_required_nb_monsters(g, GHOST, random_between_x_and_y(0,nb_monsters - required_nb_monsters(g,ZOMBIE)));
    set_required_nb_monsters(g, VAMPIRE, random_between_x_and_y(0,nb_monsters - (required_nb_monsters(g,ZOMBIE) + required_nb_monsters(g,GHOST))));
    set_required_nb_monsters(g, SPIRIT, nb_monsters - (required_nb_monsters(g,ZOMBIE) + required_nb_monsters(g,GHOST) + required_nb_monsters(g,SPIRIT)));

  for(unsigned int i = 0; i < game_width(g); i++){
    int val1 = random_between_x_and_y(0,game_width(g)-1), val2 = random_between_x_and_y(0,game_width(g)-1);
    set_required_nb_seen(g,N,i, val1);
    set_required_nb_seen(g,S,i, val2);
  }

  for(unsigned int i = 0; i < game_height(g); i++){
    int val1 = random_between_x_and_y(0,game_height(g)-1), val2 = random_between_x_and_y(0,game_height(g)-1);
    set_required_nb_seen(g,E,i, val1);
    set_required_nb_seen(g,W,i, val2);
  }

  return g;
}



















  /*  ***   Check is the generated board is possible    *** */

/*
	int nb_solution = 0;	//Integer which will contain the number of solution board find by the prog.

  game * res= (game*) malloc(sizeof(game) *50);	//We create an array which will contain (maximum) 50 solution board
  result_array_init(res);	//Init. it with few things


  solve_mode solving_result = NB_SOL;	//Get the solving mode wanted (ie. NB_SOL, FIND_ONE, *_ALL,)

  int i = 0;
  while(nb_solution == 0 && i < 100){

    game g = load_game("../executable/saves/autosave");

  	is_valid(g, 0, res, &nb_solution, solving_result);

    if(nb_solution != 0){
      free(res);
      return g;
    }else{
      i+=1;
      g = new_game_generation();
    }
  }
  return NULL;
}
*/
