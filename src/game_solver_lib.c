#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_fun.h"

//typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode;

bool next_pos_is_viable(game g, int pos, content mstr){
	int x = pos%game_width(g), y=pos/game_width(g);
	if(get_content(g, x, y) != EMPTY){
		return false;
	}
	if((x == 0 && y == 0)){
		if((required_nb_seen(g, W, 0) - current_nb_seen(g, W, 0) <= 0) && (required_nb_seen(g, S, 0) - current_nb_seen(g, S, 0) <= 0) ){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}
	}else if (x ==0 && y==game_height(g)-1){
		if(required_nb_seen(g, W, game_height(g) -1) - current_nb_seen(g, W, game_height(g) -1) <= 0 && required_nb_seen(g, N, 0) - current_nb_seen(g, N,0) <= 0 ){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}
	}else if (x ==0 && y==game_height(g)-1){
		if(required_nb_seen(g, W, game_height(g) -1) - current_nb_seen(g, W, game_height(g) -1) <= 0 && required_nb_seen(g, N, 0) - current_nb_seen(g, N,0) <= 0 ){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}
	}else if (x ==game_width(g)-1 && y==game_height(g) -1){
		if(required_nb_seen(g, E, game_height(g) -1) - current_nb_seen(g, E, game_height(g) -1) <= 0 && required_nb_seen(g, S, game_width(g)-1) - current_nb_seen(g, S,game_width(g)-1) <= 0 ){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}
	}else	if(x%game_width(g) == 0){
		if(required_nb_seen(g, W, y) - current_nb_seen(g, W, y) <= 0){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}

	} else if((x+1)%game_width(g)+1 == 0){
		if(required_nb_seen(g, E, y) - current_nb_seen(g, E, y) <= 0){
			switch (mstr) {
				case ZOMBIE:
				return false;
				case VAMPIRE:
				return false;
				default:
				return true;
			}
		}else{
			switch (mstr) {
				case ZOMBIE:
				return true;
				case VAMPIRE:
				return true;
				default:
				return false;
			}
		}
	}
	return true;
}

void copy_string(char *target, char *source) {
   while (*source) {
      *target = *source;
      source++;
      target++;
   }
   *target = '\0';
}

bool board_already_saved_as_solution(game g1, game * array){

	for(unsigned int i = 0; i < 50; i ++){
		int nb_identical_cells=0;
		if(array[i] == NULL){
			return false;
		}

		for( int x = 0; x < game_width(g1); x++){
			for( int y = 0; y < game_height(g1); y++){

				if(get_content(g1,x,y) == get_content(array[i],x,y)){
					nb_identical_cells +=1;
				}else{
					return false;
				}
				if(nb_identical_cells == (game_width(g1)*game_height(g1) -1))
					return true;

			}
		}

	}

	return false;
}


bool potential_invalid_game(game g){
	for(int x = 0; x < game_width(g);x++){
		if(required_nb_seen(g, N, x) - current_nb_seen(g,N,x) < 0)
			return false;
		if(required_nb_seen(g,S,x) - current_nb_seen(g,S,x) < 0)
			return false;
	}


	for(int x = 0; x < game_height(g);x++){
		if(required_nb_seen(g, E, x) - current_nb_seen(g, E,x) < 0)
		return false;
		if(required_nb_seen(g,W,x) - current_nb_seen(g,W,x) < 0)
		return false;
	}

	return true;
}


void append_game_array(game g, game * res){
	for(unsigned int i = 0; i < 25; i++){
		if(res[i] == NULL){
			res[i] = copy_game(g);
			break;
		}
	}
}


void result_array_init(game * res){
	for(unsigned int i = 0; i < 25; i++)	//5 parce qu'après c chiant pour les files
		res[i] = NULL;
}

solve_mode get_which_solve_mode_is_asked (char * argv){
	if(strcmp(argv, "FIND_ONE") == 0) {
		//printf("Solver will only return one solution !\n");
		return FIND_ONE;
	}else if(strcmp(argv, "NB_SOL") == 0) {
		//printf("Solver will only return the number of solutions ! \n");
		return NB_SOL;
	}else if(strcmp(argv, "FIND_ALL") == 0) {
		//printf("Solver will look for all solutions!\n");
		return FIND_ALL;
	}else{
		printf("Unable to understand the solving mode asked !\n");
	}
	return FIND_ONE;

}
void save_one_solution (game * resArray, char * prefix, int n){


  char * savePrefix = (char*) malloc(sizeof(char) * (strlen(prefix)+strlen(".sol") +strlen("\n")) );

	copy_string(savePrefix, prefix);
	strcat(savePrefix, ".sol");

	if(resArray[0]!= NULL)
		save_game(resArray[n], savePrefix);
	else{
		FILE * f = fopen(prefix, "w");
		fprintf(f,"NO SOLUTION\n");
		fclose(f);
	}

	free(savePrefix);
}

void save_all_solutions(game * res, char*prefix, int nbSol){

	char * suffix = (char*) malloc(sizeof(char) * (strlen(".sol")) *100);

	for(int i = 0; i < 50; i++){
		if(res[i] == NULL){
			free(suffix);
			return;
		}

		char * savePrefix = (char*) malloc(sizeof(char) * strlen(prefix)*100);
		char * suffixRes = (char*) malloc(sizeof(char) * (strlen(".sol") + 10)*5);
		char * filename_res = (char*) malloc(sizeof(char) * (strlen(prefix) + 10 + strlen(".sol") +1) * 25);

		strcpy(savePrefix,prefix);

		strcat(savePrefix, ".sol");

		sprintf(filename_res, "%s%d",savePrefix,i+1);

		printf("Saving...\n");

		if(res[i]!= NULL){
			save_game(res[i], filename_res);
		}else{
			free(suffix);
			free(suffixRes);
			free(savePrefix);
			free(filename_res);
			return;
		}

		free(suffixRes);
		free(savePrefix);
		free(filename_res);

	}
	free(suffix);
}


void save_nb_sol(int nbSol, char * prefix){
	printf("Saving the number of solutions !\n");

	char suffix[]=".nbsol";

	strcat(prefix, suffix);
	printf("%s !\n", prefix);
	FILE * f = fopen(prefix, "w");

	fprintf(f,"NB_SOL = %d\n",nbSol);

	fclose(f);
}


void saving_data_from_the_solver (solve_mode s, int nbSol, game * res, char * prefix){
	switch(s){
		case FIND_ONE:
			if(res[0] != NULL)
				save_one_solution(res, prefix,0);
			break;
		case NB_SOL:
			save_nb_sol(nbSol, prefix);
			break;
		case FIND_ALL:
			save_all_solutions(res, prefix, nbSol);
			break;
		default:
			break;
	}
}
