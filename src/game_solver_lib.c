#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_fun.h"

//typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode;



bool board_already_saved_as_solution(game g1, game * array){
	int nb_identical_cells=0;
	for(unsigned int i = 0; i < 5; i ++){
		nb_identical_cells=0;
		if(array[i] == NULL){
			return false;
		}

		for( int x = 0; x < game_width(g1); x++){
			for( int y = 0; y < game_height(g1); y++){

				if(get_content(g1,x,y) == get_content(array[i],x,y)){
					nb_identical_cells +=1;
				}
				if(nb_identical_cells == (game_height(g1)*game_height(g1) -1))
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
	for(unsigned int i = 0; i < 5; i++){
		if(res[i] == NULL){
			res[i] = copy_game(g);
			break;
		}
	}
}


void result_array_init(game * res){
	for(unsigned int i = 0; i < 5; i++)	//5 parce qu'après c chiant pour les files
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

  char * savePrefix = (char*) malloc(sizeof(char) * strlen(prefix));
	char * suffixRes = (char*) malloc(sizeof(char) * (strlen(".sol") + n/10));
	char * res = (char*) malloc(sizeof(char) * (strlen(prefix) + n/10 + strlen(".sol") +1));
	char * suffix = (char*) malloc(sizeof(char) * (strlen(".sol")));


	strcpy(suffix,".sol");
	strcpy(savePrefix,prefix);


	if(n == 0){
		strcpy(savePrefix,prefix);

	  strcat(savePrefix, suffix);
	}else{
		convert_int_to_string(suffixRes, suffix,n);
			res = concat(prefix,suffixRes);
				if(resArray[n]!= NULL)
			  	save_game(resArray[n], res);


	}


	if(resArray[n]!= NULL)
  	save_game(resArray[n], savePrefix);

	free(savePrefix);
}

void save_all_solutions(game * res, char*prefix, int nbSol){
	save_one_solution(res, prefix,0);

	char * suffix = (char*) malloc(sizeof(char) * (strlen(".sol")));

	for(int i = 1; i < 5; i++){
		if(res[i] == NULL)
			return;

		char * savePrefix = (char*) malloc(sizeof(char) * strlen(prefix));
		char * suffixRes = (char*) malloc(sizeof(char) * (strlen(".sol") + 10));
		char * filename_res = (char*) malloc(sizeof(char) * (strlen(prefix) + 10 + strlen(".sol") +1));

		strcpy(savePrefix,prefix);
		strcpy(suffix,".sol");

		strcat(savePrefix, suffix);

		strcpy(filename_res, savePrefix);

		sprintf(filename_res, "%s%d",filename_res,i);
		if(res[i]!= NULL)
			save_game(res[i+1], filename_res);


		free(suffixRes);
		free(savePrefix);
		free(filename_res);
	}
}


void save_nb_sol(int nbSol, char * prefix){
	printf("Saving the number of solutions !\n");

	char suffix[]=".nbsol";

	strcat(prefix, suffix);
	printf("%s !\n", prefix);
	FILE * f = fopen(prefix, "w");

	fprintf(f,"%d",nbSol);

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
			//printf("ET OUAIS IL EST PAS FAIT ENCORE\n");
			break;
		default:
			break;
	}
}
