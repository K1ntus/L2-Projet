#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "game_display.c"
#include "game_io.h"
#include "game_solver_lib.c"




//game is_valid(game g, int pos, content monster, int *nb_sol){
game is_valid(game g, int pos, content monster, game * res, int * nb_sol){
	int x = pos%game_width(g);
	int y = pos/game_width(g);

	if(g == NULL)
		return NULL;


	if(x >= game_width(g) || y >= game_height(g)){
		//delete_game(g);
		return NULL;
	}



	game g2 = malloc(sizeof(game));
	g2 = copy_game(g);

	if(g2 == NULL){
		g2 =realloc(g2, sizeof(g2) *2);
	if(g2 == NULL)
		return NULL;
	}



	if(get_content(g2,x,y) == EMPTY){
		add_monster(g2, monster, x, y);
	}

	if(board_is_full(g2)){
		if(is_game_over(g2)){
			if(!board_already_saved_as_solution(g2, res)){
				if(*nb_sol < 5)
					append_game_array(g2,res);
				*nb_sol +=1;
			}
		}
		delete_game(g2);
		return NULL;
	}

	int nb_null=0;
	if(required_nb_monsters(g2,ZOMBIE) - current_nb_monsters(g2, ZOMBIE) > 0){
			if(is_valid(g2, pos+1, ZOMBIE,res,nb_sol) == NULL){
				nb_null +=1;
			}
	}

	if(required_nb_monsters(g2,GHOST) - current_nb_monsters(g2, GHOST) > 0){
			if(is_valid(g2, pos+1, GHOST,res,nb_sol) == NULL){
				nb_null +=1;
			}
		}

	if(required_nb_monsters(g2,VAMPIRE) - current_nb_monsters(g2, VAMPIRE) > 0){
			if(is_valid(g2, pos+1, VAMPIRE,res,nb_sol) == NULL){
				nb_null +=1;
			}
		}

	if(required_nb_monsters(g2,SPIRIT) - current_nb_monsters(g2, SPIRIT) > 0){
			if(is_valid(g2, pos+1, SPIRIT,res,nb_sol) == NULL){
				nb_null +=1;
			}
		}

	if(nb_null == 4){
		printf("Olalala\n");
	}

	delete_game(g2);
	return NULL;
}

int main(int argc, char * argv[]) {
	game * res= malloc(sizeof(game) *5);
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
	delete_game(g1);

	if(res[0] == NULL){
		printf("No solution has been found\n");
	} else{
		printf("There's %d solutions! \n",nb_solution);
		saving_data_from_the_solver(solving_result, nb_solution, res, argv[3]);
	}

	free(res);

	return EXIT_SUCCESS;
}
