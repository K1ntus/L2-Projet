#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.c"

/**
  *
  * FILE SAMPLE:
  * Width
  * Height
  * nb_zombie nb_ghost  nb_vampire  nb_spirit
  * required_nb_seen_north
  * required_nb_seen_south
  * required_nb_seen_east
  * required_nb_seen_west
  * Board content
  *
**/




/**
 * @file game_io.h
 *
 * @brief This file provides functions to load or save a game.
 *
 *
 **/

///@{

/**
 * @brief Creates a game by loading its description in a file
 *
 * File format to be defined (next semester)
 *
 * @param filename
 * @return the loaded game
 **/
game load_game(char* filename){

}



/**
 * @brief Save a game in a file
 *
 * File format to be defined (next semester)
 *
 * @param g game to save
 * @param filename
 **/
void save_game(cgame g, char* filename){
  printf("INFO: Starting saving ...\n");

  printf("INFO: Creating save file\n");
  FILE* file = fopen(filename,"w");

  printf("INFO: Writing game dimension\n");
  char tmp[100];
  sprintf(tmp, "%d\n%d", game_width(g),game_height(g));
  fputs(tmp, file);
  //gsprintf(tmp, "%d %d %d %d\n", required_nb_monster(g, ZOMBIE), required_nb_monster(g, GHOST), required_nb_monster(g, VAMPIRE), required_nb_monster(g, SPIRIT));
  //fputs(tmp, file);
  int tmp_val=0;
  for(unsigned int i = 0; i < game_width(g); i++){
    if(i%2 == 0){
      tmp[i]=required_nb_seen(g, N, tmp_val);
      tmp_val +=1;
    }else{
      tmp[i]=' ';
    }
    tmp[i++] = '\n';s
  }
  fputs(tmp,file);

  fclose(file);
}


int main (void) {
  /* code */
  save_game (new_game_ext(4,4), "test.save");
  return EXIT_SUCCESS;
}
