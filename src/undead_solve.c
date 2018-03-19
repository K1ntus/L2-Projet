#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_display.h"
#include "../header/game_fun.h"

#include "game_solver_lib.c"

#define NB_MONSTERS 4

content monster[4] = {ZOMBIE, GHOST, VAMPIRE,SPIRIT};
//int nb_iterations = 0;

bool cell_is_mirror(game g, int x, int y){
	content cell = get_content(g, x, y);
	if(cell == MIRROR || cell == ANTIMIRROR || cell == VMIRROR || cell == HMIRROR)
		return true;
	return false;
}


game is_valid(game g, int pos, game * res, int * nb_sol, solve_mode solve_type){
	//nb_iterations +=1;

	if(g == NULL)
		return NULL;

	if(solve_type == FIND_ONE && *nb_sol>0)
		return NULL;

	int x = pos%game_width(g), y=pos/game_width(g);


	if(is_game_over(g)){
		res[*nb_sol] = copy_game(g);
		*nb_sol +=1;
		return NULL;
	}

	if(potential_invalid_game(g))
		return NULL;

	if(x >= game_width(g) || y >= game_height(g))
		return NULL;

	if(get_content(g, x, y) != EMPTY)
		return is_valid(g, pos+1, res, nb_sol, solve_type);



	for(unsigned int i = 0; i < NB_MONSTERS; i++){
		game solution;

		if(g != NULL){
			solution = copy_game(g);
			if(!solution)
				return NULL;
		}else{
			solution = NULL;
			return NULL;
		}


		if(required_nb_monsters(solution, monster[i]) - current_nb_monsters(solution, monster[i]) > 0){
				if(next_pos_is_viable(g, pos, monster[i])){
						add_monster(solution, monster[i], x, y);	//Then we place a monster
				}else{
					delete_game(solution);
					continue;
				}
		}else{
			delete_game(solution);
			continue;
		}

		if(solution != NULL)
			solution = is_valid(solution, pos+1, res, nb_sol, solve_type);

	}

	return NULL;
}



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
