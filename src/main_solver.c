#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_display.h"
#include "../header/game_fun.h"

#include "undead_solve.c"


int main(int argc,char* argv[]){
	if(argc != 4){	//If wrong number of args from launch
		fprintf(stderr, "Unvalid number of parameters\n");
		return EXIT_FAILURE;
	}


	game * res= (game*) malloc(sizeof(game) *50);	//We create an array which will contain (maximum) 50 solution board
	result_array_init(res);	//Init. it with few things


	solve_mode solving_result = get_which_solve_mode_is_asked(argv[1]);	//Get the solving mode wanted (ie. NB_SOL, FIND_ONE, *_ALL,)


	game g1 = load_game(argv[2]);	//We try to load the file from parameters
	if(g1 == NULL){	//If doesnt load well or something bad happens
		free(res);
		return EXIT_FAILURE;
	}

	int nb_solution = 0;	//Integer which will contain the number of solution board find by the prog.

	is_valid(g1, 0, res, &nb_solution, solving_result);

	delete_game(g1);	//We dont need anymore the game_board

	//printf("INFO: Prog. stopped after %d iterations!\n",nb_iterations);	//Debug purpose


	//display(res[0]);
	//printf("There's %d solutions! \n",nb_solution);
	saving_data_from_the_solver(solving_result, nb_solution, res, argv[3]);


	int i = 0;
	while(res[i] != NULL){
		if(res[i] != NULL){
			delete_game(res[i]);
			i++;
		}
	}

  	free(res);

  	return EXIT_SUCCESS;
  }
