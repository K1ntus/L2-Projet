#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "../header/game_io.h"

#define NB_MONSTERS 4



/**
 * @brief Save a game in a file
 *
 * File format to be defined
 *
 * @param g game to save
 * @param filename
 **/
void save_empty_line(FILE* file){
 	fputc('\n',file);
}


void apply_monsterAndMirror_cell_content(game g, char ** monsterArray){
for(int x = 0; x <game_width(g); x++){
	printf("1width = %d & x=:%d\n",game_width(g),x);
	for(int y = 0; y < game_height(g) ; y++){
		printf("***** y=%d\n",y);
		int posY=game_height(g)-(y+1);
		int posX = game_width(g)-(x+1);
			switch(monsterArray[game_height(g)-(y+1)][x]){
				case '\\':
					add_mirror_ext(g,ANTIMIRROR,posX,posY);
					break;
				case '/':
					add_mirror_ext(g,MIRROR,posX,posY);
					break;
				case '-':
					add_mirror_ext(g,HMIRROR,posX,posY);
					break;
				case '|':
					add_mirror_ext(g,VMIRROR,posX,posY);
					break;

				case 'Z':
					add_monster(g,ZOMBIE,posX,posY);
					break;
				case 'G':
					add_monster(g,GHOST,posX,posY);
					break;
				case 'V':
					add_monster(g,VAMPIRE,posX,posY);
					break;
				case 'S':
					add_monster(g,SPIRIT,posX,posY);
					break;

				default:
					break;
			}
		}
		printf("\n");
	}
}


content convert_char_to_content_io(char c){
	switch(c){
		case '\\':
			return ANTIMIRROR;
			break;
		case '/':
			return MIRROR;
			break;
		case '-':
			return HMIRROR;
			break;
		case '|':
			return VMIRROR;
			break;

		case 'Z':
			return ZOMBIE;
			break;
		case 'G':
			return GHOST;
			break;
		case 'V':
			return VAMPIRE;
			break;
		case 'S':
			return SPIRIT;
			break;


		default:
			return EMPTY;
			break;
	}
	return EMPTY;
}






void string_filtering(char*str, int*res, FILE* f){
	//get the numbers char on file
	char * token;
	token = strtok(str, " ");
	int var=0;

	int i = 0;
//manage the numbers list in order to remove space
	while (token != NULL) {
			sscanf (token, "%d", &var);
			res[i] = var;
			token = strtok(NULL, " ");
			i+=1;
	}
}


void string_filtering_to_char(char*str, char*res, FILE* f){
	//get the numbers char on file
	char * token;
	token = strtok(str, " ");
	char var='0';
	//printf("str:%s\n",str);

	int i = 0;
//manage the numbers list in order to remove space
	while (token != NULL) {
			sscanf (token, "%c", &var);
			res[i] = var;
			token = strtok(NULL, " ");
			//printf("token:%s\n",token);
			i+=1;
	}
	//printf("res:%s\n",res);
}


void error_while_loading_file(game g){

}

void apply_required_nb_monsters(game g, int * nbMonsters){
	set_required_nb_monsters(g,VAMPIRE, nbMonsters[0]);
	set_required_nb_monsters(g,GHOST, nbMonsters[1]);
	set_required_nb_monsters(g,ZOMBIE, nbMonsters[2]);
	set_required_nb_monsters(g,SPIRIT, nbMonsters[3]);
}

void apply_required_nb_seen(game g, int * north, int * south, int * east, int * west){
	for(int pos = 0; pos < game_width(g); pos++){
		set_required_nb_seen(g, N, pos, north[pos]);
		set_required_nb_seen(g, S, pos, south[pos]);
	}
	for(int pos = 0; pos < game_height(g); pos++){
		set_required_nb_seen(g, E, pos, east[pos]);
		set_required_nb_seen(g, W, pos, west[pos]);
	}
}

char** init_matrice2(game g){
	char **array1 =(char**) malloc((1+game_height(g)) * sizeof(char *) ); // Allocate row pointers
	for(int i = 0; i < game_height(g); i++)
	  array1[i] = (char*)malloc((1+game_width(g)) * sizeof(char));  // Allocate each row separately

	return array1;
}

void free_matrice(game g, char ** matrice){
	for(unsigned int i = game_height(g)-1; i > 0; i--){
		free(matrice[i]);
	}

	free(matrice[0]);
	free(matrice);
}
