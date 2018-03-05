#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "../header/game_io.h"
#include "game_io_util.c"

#define NB_MONSTERS 4


/** Change save file sample to match :
			<width> <height>
			<required_nb_ghosts>	<required_nb_vampires> <required_nb_zombies> <required_nb_spirits>
			<labels[n][0]> <labels[n][1]> ... <labels[n][width-1]>
			<labels[s][0]> <labels[s][1]> ... <labels[s][width-1]>
			<labels[e][0]> <labels[e][1]> ... <labels[e][height-1]>
			<labels[w][0]> <labels[w][1]> ... <labels[w][height-1]>
			<board[0][height-1]> <board[1][height-1]> ... <board[width-1][height-1]>
			...
			<board[0][1]> <board[1][1]> ... <board[width-1][1]>
			<board[0][0]> <board[1][0]> ... <board[width-1][0]>
*/



/// @{
/**
 * @brief Creates a game by loading its description in a file
 *
 * File format to be defined (next semester)
 *
 * @param filename
 * @return the loaded game
 **/
game load_game(char* filename){
	chdir("executable/saves");
	FILE* file = fopen(filename, "r");
	if(file == NULL){
		fprintf(stderr, "Error1 opening the file\n");
		exit(EXIT_FAILURE);
	}

	char charBuffer[35];
	int widthAndHeight[15];
	int nbMonsters[15];
	int northLabel[15];
	int southLabel[15];
	int eastLabel[15];
	int westLabel[15];

	//width & height
	if(!fgets(charBuffer, 35, file)){
		fprintf(stderr,"Invalid array in memory, sorry dude\n");
		fclose(file);
		return NULL;
	} else {
		string_filtering(charBuffer, widthAndHeight, file);
	}

	unsigned int height = widthAndHeight[1], width = widthAndHeight[0];
	printf("Width=%d and height=%d\n",width,height);

	game g = new_game_ext(width,height);	//We create the new game dude

	char ** monsterAndMirrorArray = init_matrice2(g);	//Init a 2D array which is an array with array of each line content


	//required nb monsters
	if(!fgets(charBuffer, 35, file)){
		fclose(file);
		free_matrice(g, monsterAndMirrorArray);
		return NULL;
	} else {
		string_filtering(charBuffer, nbMonsters, file);
	}


	//north label
	if(!fgets(charBuffer, 35, file)){
		fclose(file);
		free_matrice(g, monsterAndMirrorArray);
		return NULL;
	} else {
		string_filtering(charBuffer, northLabel, file);
	}

	//south label
	if(!fgets(charBuffer, 35, file)){
		fclose(file);
		free_matrice(g, monsterAndMirrorArray);
		return NULL;
	} else {
		string_filtering(charBuffer, southLabel, file);
	}

	//east label
	if(!fgets(charBuffer, 35, file)){
		fclose(file);
		free_matrice(g, monsterAndMirrorArray);
		return NULL;
	} else {
		string_filtering(charBuffer, eastLabel, file);
	}

	//west label
	if(!fgets(charBuffer, 35, file)){
		fclose(file);
		free_matrice(g, monsterAndMirrorArray);
		return NULL;
	} else {
		string_filtering(charBuffer, westLabel, file);
	}


	//Monster cells
	for(int y = 0; y<game_height(g);y++){
		if(!fgets(charBuffer, 35, file)){
			fclose(file);
			free_matrice(g, monsterAndMirrorArray);
			return NULL;
		} else {
			string_filtering_to_char(charBuffer, monsterAndMirrorArray[y], file);
		}
	}



	apply_monsterAndMirror_cell_content(g,monsterAndMirrorArray);
	apply_required_nb_monsters(g, nbMonsters);
	apply_required_nb_seen(g, northLabel, southLabel, eastLabel, westLabel);

	fclose(file);
	free_matrice(g, monsterAndMirrorArray);


	return g;
}




void save_game(cgame g, char* filename){
	//printf("\n\nINFO: Starting saving ...\n");

	int height = game_height(g);
	int width = game_width(g);

	//printf("INFO: Creating save file\n");
	chdir("executable/saves");
	FILE* file = fopen(filename,"w");
	if(file == NULL){
		fprintf(stderr, "Error2 opening the file \n");
		exit(EXIT_FAILURE);
	}


	//printf("INFO: Writing game dimension\n");
	char tmp[100];
	sprintf(tmp, "%d %d\n", width,height);
	fputs(tmp, file);

	//printf("INFO: Writing monsters available\n");
	fprintf(file, "%d ", required_nb_monsters(g,GHOST));
	fprintf(file, "%d ", required_nb_monsters(g,VAMPIRE));
	fprintf(file, "%d ", required_nb_monsters(g,ZOMBIE));
	fprintf(file, "%d ", required_nb_monsters(g,SPIRIT));
	save_empty_line(file);

	//printf("INFO: Writing required labels\n");
	for(int i = 0; i < width; i++){
		sprintf(tmp, "%d ",required_nb_seen(g,N,i));
		fputs(tmp,file);
	}
	save_empty_line(file);

	for(int i = 0; i < width; i++){
		sprintf(tmp, "%d ",required_nb_seen(g,S,i));
		fputs(tmp,file);
	}
	save_empty_line(file);

	for(int i = 0; i < height; i++){
		sprintf(tmp, "%d ",required_nb_seen(g,E,i));
		fputs(tmp,file);
	}
	save_empty_line(file);

	for(int i = 0; i < height; i++){
		sprintf(tmp, "%d ",required_nb_seen(g,W,i));
		fputs(tmp,file);
	}
	save_empty_line(file);

	//printf("INFO: Writing cells content\n");
	for(int x = game_height(g)-1; x >= 0; x--){
		for(int y = 0; y < game_width(g) ; y++){
			content tick_content = get_content(g,x,y);

			//Graphic show of cells content
			switch(tick_content){
				case EMPTY:
					fprintf(file,". ");
					break;
				case MIRROR:
					fprintf(file,"/ ");
					break;
				case ANTIMIRROR:
					fprintf(file,"\\ ");
					break;
				case VMIRROR:
					fprintf(file,"| ");
					break;
				case HMIRROR:
					fprintf(file,"- ");
					break;
				case SPIRIT:
					fprintf(file,"S ");
					break;
				case ZOMBIE:
					fprintf(file,"Z ");
					break;
				case GHOST:
					fprintf(file,"G ");
					break;
				case VAMPIRE:
					fprintf(file,"V ");
					break;
			}
		}
		save_empty_line(file);
	}
	fclose(file);
}
