
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "game_io.h"

typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode;



bool potential_invalid_game(game g){
	for(unsigned int x = 0; x < game_width(g);x++){
		if(required_nb_seen(g, N, x) - current_nb_seen(g,N,x) < 0)
			return false;
		if(required_nb_seen(g,S,x) - current_nb_seen(g,S,x) < 0)
			return false;
	}


	for(unsigned int x = 0; x < game_height(g);x++){
		if(required_nb_seen(g, E, x) - current_nb_seen(g, E,x) < 0)
		return false;
		if(required_nb_seen(g,W,x) - current_nb_seen(g,W,x) < 0)
		return false;
	}

	return true;
}

bool board_is_full(game g){
	for (unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(get_content(g,x,y) == EMPTY)
				return false;
		}
	}
	return true;
}

void append_game_array(game g, game * res){
	for(unsigned int i = 0; i < 50; i++){
		if(res[i] == NULL){
			res[i] = copy_game(g);
			break;
		}
	}
}


void result_array_init(game * res){
	for(unsigned int i = 0; i < 50; i++)
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

void append(char* s, char c){
				int len = strlen(s);
				s[len] = c;
				s[len+1] = '\0';
}

char* concat(const char *s1, const char *s2){
		char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
		//check for errors in malloc here
		strcpy(result, s1);
		strcat(result, s2);
		return result;
}

void save_one_solution (game * res, char * prefix, int n){

  char * savePrefix = malloc(sizeof(char) * 16);
	char * suffix = malloc(sizeof(char)*8);


  for(unsigned int i = 0; i < strlen(prefix); i++){
    savePrefix[i] = prefix[i];
  }

	strcpy(suffix,".sol");
	strcpy(savePrefix,prefix);

  strcat(savePrefix, suffix);

  save_game(res[n], savePrefix);

	free(savePrefix);
}

void save_all_solutions(game * res, char*prefix, int nbSol){
	save_one_solution(res, prefix,0);
	for(unsigned int i = 1; i < nbSol; i++)
		save_one_solution(res, prefix, i);
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
