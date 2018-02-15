#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game_io.h"



/** Change save file sample to match :
			<width> <height>
			<required_nb_ghosts>  <required_nb_vampires> <required_nb_zombies> <required_nb_spirits>
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
	int width = 4, height =4;
	FILE * file = fopen(filename, "r");

	game g = new_game_ext(width,height);

	fclose(file);
	return g;
}



/**
 * @brief Save a game in a file
 *
 * File format to be defined (next semester)
 *
 * @param g game to save
 * @param filename
 **/
void save_empty_line(FILE* file){
 	fputc('\n',file);
}
void save_game(cgame g, char* filename){
  printf("\n\nINFO: Starting saving ...\n");

  int height = game_height(g);
  int width = game_width(g);

  printf("INFO: Creating save file\n");
  FILE* file = fopen(filename,"w");

  printf("INFO: Writing game dimension\n");
  char tmp[100];
  sprintf(tmp, "%d %d\n", width,height);
  fputs(tmp, file);

  printf("INFO: Writing monsters available\n");
	fprintf(file, "%d ", required_nb_monsters(g,ZOMBIE));
	fprintf(file, "%d ", required_nb_monsters(g,VAMPIRE));
	fprintf(file, "%d ", required_nb_monsters(g,GHOST));
	fprintf(file, "%d ", required_nb_monsters(g,SPIRIT));
	save_empty_line(file);

  printf("INFO: Writing required labels\n");
  for(unsigned int i = 0; i < width; i++){
    sprintf(tmp, "%d ",required_nb_seen(g,N,i));
    fputs(tmp,file);
  }
	save_empty_line(file);

  for(unsigned int i = 0; i < width; i++){
    sprintf(tmp, "%d ",required_nb_seen(g,S,i));
    fputs(tmp,file);
  }
	save_empty_line(file);

  for(unsigned int i = 0; i < height; i++){
    sprintf(tmp, "%d ",required_nb_seen(g,E,i));
    fputs(tmp,file);
  }
	save_empty_line(file);

  for(unsigned int i = 0; i < height; i++){
    sprintf(tmp, "%d ",required_nb_seen(g,W,i));
    fputs(tmp,file);
  }
	save_empty_line(file);

  printf("INFO: Writing cells content\n");
  for(unsigned int posY = game_height(g); posY > 0; posY--){
		for(unsigned int posX = 0; posX < game_width(g); posX++){
      int tick_content = get_content(g,posX,posY-1);

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
          fprintf(file,"_ ");
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
	save_empty_line(file);
  fclose(file);
}
