#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game_io.h"

#define NB_MONSTERS 4


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


void error_while_loading_file(game g){

}

void apply_required_nb_monsters(game g, int * nbMonsters){
  set_required_nb_monsters(g,GHOST, nbMonsters[0]);
  set_required_nb_monsters(g,VAMPIRE, nbMonsters[1]);
  set_required_nb_monsters(g,ZOMBIE, nbMonsters[2]);
  set_required_nb_monsters(g,SPIRIT, nbMonsters[3]);
}

void apply_required_nb_seen(game g, int * north, int * south, int * east, int * west){
  for(unsigned int pos = 0; pos < game_width(g); pos++){
    set_required_nb_seen(g, N, pos, north[pos]);
    set_required_nb_seen(g, S, pos, south[pos]);
  }
  for(unsigned int pos = 0; pos < game_height(g); pos++){
    set_required_nb_seen(g, E, pos, east[pos]);
    set_required_nb_seen(g, W, pos, west[pos]);
  }
}

void apply_monsterAndMirror_cell_content(game g, int ** monsterArray){
for(unsigned int x = 0; x < game_width(g); x++){
  for(unsigned int y = game_height(g); y >0; y--){
      switch(monsterArray[game_width(g) - (y)][x]){
        case ANTIMIRROR:
          add_mirror_ext(g,ANTIMIRROR,x,y-1);
          break;
        case MIRROR:
          add_mirror_ext(g,MIRROR,x,y-1);
          break;
        case HMIRROR:
          add_mirror_ext(g,HMIRROR,x,y-1);
          break;
        case VMIRROR:
          add_mirror_ext(g,VMIRROR,x,y-1);
          break;

        case ZOMBIE:
          add_monster(g,ZOMBIE,x,y-1);
          break;
        case GHOST:
          add_monster(g,GHOST,x,y-1);
          break;
        case VAMPIRE:
          add_monster(g,VAMPIRE,x,y-1);
          break;
        case SPIRIT:
          add_monster(g,SPIRIT,x,y-1);
          break;

        default:
          break;
      }
    }
  }
}


int** init_matrice2(game g){
	int **res  = (int **)malloc(sizeof(int *) * game_width(g));
	res[0] = (int *)malloc(sizeof(int) * game_height(g) * game_width(g));
	for(int i = 0; i < game_width(g); i++)
	   res[i] = malloc(sizeof(int)*game_width(g));

  return res;
}

void free_matrice(game g, int ** matrice){
  for (int x = game_width(g); x >0; x--){
    free(matrice[x]);
  }
  free(matrice[0]);
  free(matrice);
}

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
  FILE* file = fopen(filename, "r");

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
    return NULL;
  } else {
    string_filtering(charBuffer, widthAndHeight, file);
  }

	unsigned int height = widthAndHeight[1], width = widthAndHeight[0];
  game g = new_game_ext(height,width);

  int ** monsterAndMirrorArray = init_matrice2(g);

  //required nb monsters
  if(!fgets(charBuffer, 35, file)){
    return NULL;
  } else {
    string_filtering(charBuffer, nbMonsters, file);
  }


  //north label
  if(!fgets(charBuffer, 35, file)){
    return NULL;
  } else {
    string_filtering(charBuffer, northLabel, file);
  }

  //south label
  if(!fgets(charBuffer, 35, file)){
    return NULL;
  } else {
    string_filtering(charBuffer, southLabel, file);
  }

  //east label
  if(!fgets(charBuffer, 35, file)){
    return NULL;
  } else {
    string_filtering(charBuffer, eastLabel, file);
  }

  //west label
  if(!fgets(charBuffer, 35, file)){
    return NULL;
  } else {
    string_filtering(charBuffer, westLabel, file);
  }

  //Monster cells
  for(unsigned int y = 0; y<height;y++){
    if(!fgets(charBuffer, 35, file)){
      return NULL;
    } else {
      string_filtering(charBuffer, monsterAndMirrorArray[y], file);
    }
  }

  apply_monsterAndMirror_cell_content(g,monsterAndMirrorArray);
  apply_required_nb_monsters(g, nbMonsters);
  apply_required_nb_seen(g, northLabel, southLabel, eastLabel, westLabel);

  fclose(file);
  free_matrice(g, monsterAndMirrorArray);
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
      content tick_content = get_content(g,posX,posY-1);

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
