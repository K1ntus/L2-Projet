#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_display.h"
#include "../header/game_fun.h"

#include "./game_solver_lib.c"
#include "./game_util.c"

int nb_iterations = 0;

//game is_valid(game g, int pos, content monster, int *nb_sol){
game is_valid(game g, int pos, content monster, game * res, int * nb_sol){
	nb_iterations+=1;

	int x = pos%game_width(g);//Convert pos parameters to x and y in order to use on some game.c functions
	int y = pos/game_width(g);


	if(g == NULL)//We check if the game from parameters is OK
		return NULL;


	if(x >= game_width(g) || y >= game_height(g)){ //We check if pos are valid
		return NULL;
	}



	game g2 = (game) malloc(sizeof(game));

	if(g2 == NULL){//if new board g2 doesnt allocate well
		g2 =(game) realloc(g2, sizeof(g2) *2);//We retry to allocate him with double size
		printf("pew pew pew\n");
		if(g2 == NULL)//Else we go back to previous recurrency call
			return NULL;
	}
	g2 = copy_game(g);//If g2 well allocated, pouf, we copy the game from parameters on this new one




	if(get_content(g2,x,y) == EMPTY){	//If the cells is empty
		add_monster(g2, monster, x, y);	//Then we place a monster
	}

	if(board_is_full(g2)){	//We check if the generated board is full of monsters (ie. no empty cells)
		if(is_game_over(g2)){	//Then if the game is over
			if(!board_already_saved_as_solution(g2, res)){	//We check if this board hasnt already been saved
				if(*nb_sol < 5)	//And if the number of board saved dont exceed 5 (too much files after LOL)
					append_game_array(g2,res);	//Then we add the game board to the res array
				*nb_sol +=1;	//We increment the total number of solutions
			}
		}
		delete_game(g2);	//We can delete this board and "go down of a layer" on the recurrence
		return NULL;
	}

	int nb_null=0;//Not used yet
	if(required_nb_monsters(g2,ZOMBIE) - current_nb_monsters(g2, ZOMBIE) > 0){	//If the max number of this monster type isnt already reached
			if(is_valid(g2, pos+1, ZOMBIE,res,nb_sol) == NULL){
				nb_null +=1;
			}
	}

	if(required_nb_monsters(g2,GHOST) - current_nb_monsters(g2, GHOST) > 0){//If the max number of this monster type isnt already reached
		if(is_valid(g2, pos+1, GHOST,res,nb_sol) == NULL){
			nb_null +=1;
		}
	}

	if(required_nb_monsters(g2,VAMPIRE) - current_nb_monsters(g2, VAMPIRE) > 0){//If the max number of this monster type isnt already reached
		if(is_valid(g2, pos+1, VAMPIRE,res,nb_sol) == NULL){
			nb_null +=1;
		}
	}

	if(required_nb_monsters(g2,SPIRIT) - current_nb_monsters(g2, SPIRIT) > 0){//If the max number of this monster type isnt already reached
		if(is_valid(g2, pos+1, SPIRIT,res,nb_sol) == NULL){
			nb_null +=1;
		}
	}

	if(nb_null == 4){	//All the board from this pos are bullshit :s
		printf("Olalala\n");
	}

	return NULL;
}

int main(int argc, char * argv[]) {
	game * res= (game*) malloc(sizeof(game) *5);	//We create an array which will contain (at maximum) 5 solution board
	result_array_init(res);	//Init. it with few things

	if(argc != 4){	//If wrong number of args from launch
		fprintf(stderr, "Unvalid number of parameters\n");
		return EXIT_FAILURE;
	}

	printf("params: %s; %s; %s; %s\n",argv[0], argv[1],argv[2],argv[3]);	//Just informative
	solve_mode solving_result = get_which_solve_mode_is_asked(argv[1]);	//Get the solving mode wanted (ie. NB_SOL, FIND_ONE, *_ALL,)



	game g1 = load_game(argv[2]);	//We try to load the file from parameters
	if(g1 == NULL)	//If doesnt load well or something bad happens
		return EXIT_FAILURE;

	int nb_solution = 0;	//Integer which will contain the number of solution board find by the prog.

	is_valid(g1,0,EMPTY, res, &nb_solution);

	delete_game(g1);	//We dont need anymore the game_board

	printf("Prog. stopped after %d iterations!\n",nb_iterations);	//Debug purpose

	if(res[0] == NULL){
		printf("No solution has been found\n");
	} else{
		printf("There's %d solutions! \n",nb_solution);
		saving_data_from_the_solver(solving_result, nb_solution, res, argv[3]);
	}

	free(res);

	return EXIT_SUCCESS;
}
