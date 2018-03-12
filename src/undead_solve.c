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
int nb_iterations = 0;


bool is_solution(game g2, game*res, int*nb_sol){
	if(board_is_full(g2)){	//We check if the generated board is full of monsters (ie. no empty cells)
		//printf("INFO: board is full\n");
		if(is_game_over(g2)){	//Then if the game is over
			//printf("INFO:board is over\n");
			if(!board_already_saved_as_solution(g2, res)){	//We check if this board hasnt already been saved
				if(*nb_sol < 5)	//And if the number of board saved dont exceed 5 (too much files after LOL)
					append_game_array(g2,res);	//Then we add the game board to the res array
				*nb_sol +=1;	//We increment the total number of solutions
				return true;
			}
		}
	}
	return false;
}

bool cell_is_mirror(game g, int x, int y){
	content cell = get_content(g, x, y);
	if(cell == MIRROR || cell == ANTIMIRROR || cell == VMIRROR || cell == HMIRROR)
		return true;
	return false;
}

game is_valid(game g, int pos, game * res, int * nb_sol){
	nb_iterations +=1;



	int x = pos%game_width(g), y=pos/game_width(g);


	if(g == NULL)
		return NULL;


	if(is_game_over(g)){
		if(!board_already_saved_as_solution(g,res)){
			res[*nb_sol] = copy_game(g);
			*nb_sol +=1;
		}
		return NULL;
	}

	if(pos >= game_height(g)*game_width(g)){
		if(is_game_over(g)){
			return g;
		}else{
			delete_game(g);
			return NULL;
		}
	}

	if(is_game_over(g)){
		is_solution(g, res, nb_sol);
		return g;
	}

	if(x >= game_width(g) || y >= game_height(g))
		return NULL;

	if(get_content(g, x, y) != EMPTY){
		return is_valid(g, pos+1, res, nb_sol);
	}

	if(nb_iterations >= 3000000){
		return NULL;
	}


	for(unsigned int i = 0; i < NB_MONSTERS; i++){
		game solution;

		if(g != NULL){
			solution = copy_game(g);
		}else{
			return NULL;
		}

		if(solution == NULL)
			continue;

		if(required_nb_monsters(solution, monster[i]) - current_nb_monsters(solution, monster[i]) > 0){
				if(next_pos_is_viable(g, pos, monster[i])){
					if(!solution)
						continue;
					else
						add_monster(solution, monster[i], x, y);	//Then we place a monster
				}else{
					delete_game(solution);
					continue;
				}
		}else{
			delete_game(solution);
			continue;
		}

		solution = is_valid(solution, pos+1, res, nb_sol);

		if(solution != NULL){
			is_solution(solution, res, nb_sol);
			return solution;
		}else{
			continue;
		}


	}

	return NULL;
}



int main(int argc,char* argv[]){

	if (argc != 4){
		fprintf(stderr,"wrong parameters!\n");
		exit(EXIT_FAILURE);
	}


	game * res= (game*) malloc(sizeof(game) *25);	//We create an array which will contain (at maximum) 5 solution board
	result_array_init(res);	//Init. it with few things

	if(argc != 4){	//If wrong number of args from launch
		fprintf(stderr, "Unvalid number of parameters\n");
		free(res);
		return EXIT_FAILURE;
	}

	printf("params: %s; %s; %s; %s\n",argv[0], argv[1],argv[2],argv[3]);	//Just informative
	solve_mode solving_result = get_which_solve_mode_is_asked(argv[1]);	//Get the solving mode wanted (ie. NB_SOL, FIND_ONE, *_ALL,)


	game g1 = load_game(argv[2]);	//We try to load the file from parameters
	if(g1 == NULL){	//If doesnt load well or something bad happens
		free(res);
		return EXIT_FAILURE;
	}

	printf("zombie:%d, ghost:%d, vampire:%d, spirit:%d\n",required_nb_monsters(g1,ZOMBIE),required_nb_monsters(g1,GHOST),required_nb_monsters(g1,VAMPIRE),required_nb_monsters(g1,SPIRIT));
	int nb_solution = 0;	//Integer which will contain the number of solution board find by the prog.

	is_valid(g1, 0, res, &nb_solution);

	delete_game(g1);	//We dont need anymore the game_board

	printf("INFO: Prog. stopped after %d iterations!\n",nb_iterations);	//Debug purpose

	if(res[0] == NULL){
		printf("No solution has been found\n");
	}
		printf("There's %d solutions! \n",nb_solution);
		saving_data_from_the_solver(solving_result, nb_solution, res, argv[3]);



	for(unsigned int i = 0; i < 5; i++){
		if(res[i] != NULL)
		delete_game(res[i]);
	}
	free(res);

	return EXIT_SUCCESS;
}
