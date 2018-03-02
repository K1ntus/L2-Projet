#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "game_display.c"
#include "game_io.h"

#include "game_solver_lib.c"

//game is_valid(game g, int pos, content monster, int *nb_sol){
void is_valid(game g, int pos, content monster, game * res, int * nb_sol){
	int x = pos%game_width(g);
	int y = pos/game_width(g);

	//display(g);
	if(res[0] != NULL){
		free(g);
		return;
	}

	if(g == NULL){
		return;
	}
	game g2 = copy_game(g);


			if(g2 == NULL){
				return;
			}


	if(get_content(g2,x,y) == EMPTY){
		add_monster(g2, monster, x, y);
	}

	if(is_game_over(g2)){
		//printf("A solution has been found !\n");
		append_game_array(g2,res);
		*nb_sol +=1;
		free(g);
		//sleep(1);
		return ;
	}
	if(board_is_full(g2)){
		//free(g2);
		return ;
	}

	if(required_nb_monsters(g2,ZOMBIE) - current_nb_monsters(g2, ZOMBIE) > 0)
		is_valid(g2, pos+1, ZOMBIE,res,nb_sol);

	if(required_nb_monsters(g2,GHOST) - current_nb_monsters(g2, GHOST) > 0)
		is_valid(g2, pos+1, GHOST,res,nb_sol);

	if(required_nb_monsters(g2,SPIRIT) - current_nb_monsters(g2, SPIRIT) > 0)
		is_valid(g2, pos+1, SPIRIT,res,nb_sol);

	if(required_nb_monsters(g2,VAMPIRE) - current_nb_monsters(g2, VAMPIRE) > 0)
		is_valid(g2, pos+1, VAMPIRE,res,nb_sol);

}

int main(int argc, char * argv[]) {
	game * res= malloc(sizeof(game) *500);
	result_array_init(res);

	if(argc != 4){
		fprintf(stderr, "Unvalid number of parameters\n");
		return EXIT_FAILURE;
	}

		printf("params: %s; %s; %s; %s\n",argv[0], argv[1],argv[2],argv[3]);
	solve_mode solving_result = get_which_solve_mode_is_asked(argv[1]);



	game g1 = load_game(argv[2]);

	int nb_solution = 0;

	is_valid(g1,0,EMPTY, res, &nb_solution);
	//is_valid(g1,0,EMPTY,res);
	free(g1);

	saving_data_from_the_solver(solving_result, nb_solution, res, argv[3]);

/*
	if(res[0] == NULL){
		printf("No solution has been find\n");
	} else{
		printf("There's %d solutions! \n",nb_solution);
		save_game(res[0], "this_is_the_solution_dude");
	}
*/
	free(res);

	return EXIT_SUCCESS;
}
