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


typedef struct {
	game * res;
	int size;
} result_array;



void realloc_game_solve_array(result_array s_solve){
	if(s_solve.res != NULL){
		s_solve.res = realloc(s_solve.res, sizeof(s_solve.res)*2);
		s_solve.size *=2;
	}
}

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
