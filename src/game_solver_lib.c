#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_fun.h"

//typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode; //on game_fun.h



/**
 * @brief check the next position to the labels in order to optimise the processing of the solver
 * @param g the game board to analyse
 * @param pos the position on the game board ( 0<= pos <= width*heght-1)
 * @param mstr the monster we want to place
 * @return false if it would be useless to place this monster, else true
 **/
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


/**
 * @brief copy a string, and put it on another char* variable (like strcopy to be short)
 * @param target the string where we want to paste
 * @param source the string where we want to copy
 * @return void
 **/
void copy_string(char *target, char *source) {
   while (*source) {
      *target = *source;
      source++;
      target++;
   }
   *target = '\0';
}

/**
 * @brief check if the board as parameters is already saved on the game array
 * @param g the game board to compare with
 * @param array an array with all already saved game board from sovler
 * @return true if alreade saved, else false
 **/
bool board_already_saved_as_solution(game g1, game * array){
	for(unsigned int i = 0; i < 50; i ++){	//Arbitrary value (50) to change
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


/**
 * @brief check some things on the parameters, like the difference between current and required nb seen, etc
 * @param g the game board to analyse
 * @return true if this game would be not solved this way, else true
 **/
bool potential_invalid_game(game g){
	for(int x = 0; x < game_width(g);x++){
		if(required_nb_seen(g, N, x) - current_nb_seen(g,N,x) < 0)
			return true;
		if(required_nb_seen(g,S,x) - current_nb_seen(g,S,x) < 0)
			return true;
	}


	for(int x = 0; x < game_height(g);x++){
		if(required_nb_seen(g, E, x) - current_nb_seen(g, E,x) < 0)
		return true;
		if(required_nb_seen(g,W,x) - current_nb_seen(g,W,x) < 0)
		return true;
	}

	return false;
}


/**
 * @brief add a solving game to the solve array
 * @param g the game board to analyse
 * @param res the game result array where we want to append the first parameters
 * @return void
 **/
void append_game_array(game g, game * res){
	for(unsigned int i = 0; i < 25; i++){
		if(res[i] == NULL){
			res[i] = copy_game(g);
			break;
		}
	}
}


/**
 * @brief init the game_board res array with null value for each cells just to be sure
 * @param res the result array of game board
 * @return char* void
 **/
void result_array_init(game * res){
	for(unsigned int i = 0; i < 25; i++)	//5 parce qu'après c chiant pour les files
		res[i] = NULL;
}

/**
 * @brief convert the string as launch parameters and convert it to a solve_mode value
 * @param argv a string from launch parameters
 * @return solve_mode equals to NB_SOL, FIND_ONE or FIND_ALL
 **/
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


/**
 * @brief called if the solve mode is FIND_ONE, and will save only ONE file
 * @param resArray the result array containing all game_board which solve the one as parameters
 * @param prefix the name of the file before the extension
 * @param n unused parameters
 * @return void
 **/
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



/**
 * @brief called if the solve mode is FIND_ALL, and will save only ALL board with one file per solution
 * @param res the result array containing all game_board which solve the one as parameters
 * @param prefix the name of the file before the extension
 * @param nbSol the numbers of solution to save on file
 * @return void
 **/
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



/**
 * @brief called if the solve mode is NB_SOL, will save a file which will containt the number of solution for a board
 * @param nbSol the int value to print on the file

 /**
  * @brief called if the solve mode is FIND_ONE, and will save only ONE file
  * @param resArray the result array containing all game_board which solve the one as parameters
  * @param prefix the name of the file before the extension
  * @param n unused parameters
  * @return void
  **/
 * @param prefix the name of the file before the extension
 * @return void
 **/
void save_nb_sol(int nbSol, char * prefix){
	char suffix[]=".nbsol";

	strcat(prefix, suffix);
	printf("%s !\n", prefix);
	FILE * f = fopen(prefix, "w");

	fprintf(f,"NB_SOL = %d\n",nbSol);

	fclose(f);
}



/**
 * @brief called to save the file, work a bit like a crossroad. For each solve_mode will call the required function
 * @param s the wanted solved_mode (ie. NB_SOL, FIND_ONE or FIND_ALL)
 * @param nbSol an integer with the number of solutions which has been find
 * @param res an array which contain all the board which save the original one
 * @param prefix the name of the file to save before the extension
 * @return void
 **/
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
