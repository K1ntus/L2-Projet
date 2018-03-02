#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "game_display.c"
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

//game is_valid(game g, int pos, content monster, int *nb_sol){
void is_valid(game g, int pos, content monster, game * res, int * nb_sol){
	int x = pos%game_width(g);
	int y = pos/game_width(g);


	game g2 = new_game_ext(game_width(g), game_height(g));
	g2 = copy_game(g);



	if(get_content(g2,x,y) == EMPTY){
		add_monster(g2, monster, x, y);
	}

	if(is_game_over(g2)){
		//printf("A solution has been found !\n");
		append_game_array(g2,res);
		*nb_sol +=1;
		free(g2);
		return ;
	}
	if(board_is_full(g2)){
		free(g2);
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

		return ;
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

void save_one_solution (game * res1, char * prefix, int n){

	char *savePrefix = malloc(sizeof(char)*27);
	char *res = malloc(sizeof(char)*32);
	char suffix[]=".sol";

	for(unsigned int i = 0; i < strlen(prefix); i++){
		savePrefix[i] = prefix[i];
	}

	if(n != 0){
		//char suffix[]=".sol";
		char s[50];
		printf("savePrefix before:%s\n",savePrefix );
		sprintf(s, "%d",n); // Conversion de l'entier
		printf("savePrefix before:%s\n",savePrefix );
		strcat(suffix, s);
		printf("savePrefix before:%s\n",savePrefix ); /****/
		printf("savePrefix before:%s\n",savePrefix );
		printf("SavePrefix after:%s\n",savePrefix);
		printf("final string:%s\n",res);

	}


	strcat(res,savePrefix);
	strcat(res,suffix);

	save_game(res1[n], savePrefix);

	strcpy(suffix,".sol");
	strcpy(savePrefix,prefix);

	free(res);
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
