#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game_io.h"
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



//SOME TEMPORARY FUNCTIONS

//Display an empty line
void display_empty_line(game g){
		printf("|     ");
		for(int i=0; i<game_width(g) ; i++){
			printf("  ");
		}
		printf("      |\n");
}

//Display the numbers of monsters to place in top of the board
void display_required_nb_monsters(game g){
	if (game_width(g) <= 4){
		printf("|  Z:%d V:%d G:%d S:%d  |\n",
		required_nb_monsters(g, ZOMBIE),
		required_nb_monsters(g, VAMPIRE),
		required_nb_monsters(g, GHOST),
		required_nb_monsters(g, SPIRIT));
	}else{
		printf("|  ");
		int spaces = (game_width(g) + game_width(g) - 11)/2;   //Calculate the number of spaces to display (in each side of the text)
		for(int i=0; i<spaces; i++){													 //In order to center the text
			printf(" ");
		}
		printf(" Z:%d V:%d G:%d S:%d ",
		required_nb_monsters(g, ZOMBIE),
		required_nb_monsters(g, VAMPIRE),
		required_nb_monsters(g, GHOST),
		required_nb_monsters(g, SPIRIT));

		for(int i=0; i<spaces+1; i++){
			printf(" ");
		}
		printf("   |\n");
	}
}

void display_required_nb_seen_north(game g){
	printf("|      ");
	for(int i=0; i<game_width(g) ; i++){
		printf("%d ",required_nb_seen(g, N, i));
	}
	printf("     |\n");
}

void display_cellsContent_and_sideValues(game g){
	int tick_content;
	for(int x = game_height(g)-1; x >= 0; x--){
		//Left & right side of the board
		printf("|   %d  ", required_nb_seen(g, W, x));
		for(int y = 0; y < game_width(g) ; y++){
			tick_content = get_content(g,y,x);

			//Graphic show of cells content
			switch(tick_content){
				case EMPTY:
					printf("  ");
					break;
				case MIRROR:
					printf("/ ");
					break;
				case ANTIMIRROR:
					printf("\\ ");
					break;
				case VMIRROR:
					printf("| ");
					break;
				case HMIRROR:
					printf("_ ");
					break;
				case SPIRIT:
					printf("S ");
					break;
				case ZOMBIE:
					printf("Z ");
					break;
				case GHOST:
					printf("G ");
					break;
				case VAMPIRE:
					printf("V ");
					break;
			}
		}
//Right side && number of monsters to be seen
	printf(" %d   |\n",required_nb_seen (g, E, x));
	}
}

void display_required_nb_seen_south(game g){
		printf("|      ");
		for(int i=0; i<game_width(g) ; i++){
			printf("%d ",required_nb_seen(g, S, i));
		}
		printf("     |\n");
}

void display_start(game g){
	if (game_width(g) <= 4){
		printf("|       start       |");
	}else{
		printf("|  ");
		int spaces = game_width(g) + (game_width(g)-1) - 8;  //Give the number of space to add before and after the text
		for(int i = 0; i<spaces/2; i++){//Divided by 2 for left side
			printf(" ");
		}
		printf("     start      ");

		for(int i=0; i<spaces/2 + 1; i++){//Divided by 2 for the right side
			printf(" ");
		}
		printf("  |\n");
	}
}

//Calls each functions created to display all the element of the game board
void display(game g){
		display_required_nb_monsters(g);
		display_empty_line(g);

		display_required_nb_seen_north(g);
		display_empty_line(g);

		display_cellsContent_and_sideValues(g);
		display_empty_line(g);

		display_required_nb_seen_south(g);
		display_empty_line(g);
		display_empty_line(g);

		display_start(g);
}

//Creation of a new map containing the new monster
void generate(game g, int * nbMonsters){
	set_required_nb_monsters (g, ZOMBIE,  nbMonsters[2]);
	set_required_nb_monsters (g, GHOST,  nbMonsters[1]);
	set_required_nb_monsters (g, VAMPIRE,  nbMonsters[0]);
	set_required_nb_monsters (g, SPIRIT,  nbMonsters[3]);

//AntiMirror
	add_mirror_ext(g,ANTIMIRROR,0,0);
	add_mirror_ext(g,ANTIMIRROR,0,2);
	add_mirror_ext(g,ANTIMIRROR,0,3);
	add_mirror_ext(g,ANTIMIRROR,3,0);
	add_mirror_ext(g,ANTIMIRROR,2,1);

//Mirror
	add_mirror_ext(g,MIRROR,3,3);
	add_mirror_ext(g,MIRROR,3,1);

	set_required_nb_seen (g, N, 0, 0);
	set_required_nb_seen (g, N, 1, 3);
	set_required_nb_seen (g, N, 2, 3);
	set_required_nb_seen (g, N, 3, 0);

	set_required_nb_seen (g, S, 3, 3);
	set_required_nb_seen (g, S, 2, 2);
	set_required_nb_seen (g, S, 1, 3);
	set_required_nb_seen (g, S, 0, 0);

	set_required_nb_seen (g, E, 0, 0);
	set_required_nb_seen (g, E, 1, 0);
	set_required_nb_seen (g, E, 2, 3);
	set_required_nb_seen (g, E, 3, 2);

	set_required_nb_seen (g, W, 3, 3);
	set_required_nb_seen (g, W, 2, 3);
	set_required_nb_seen (g, W, 1, 2);
	set_required_nb_seen (g, W, 0, 0);
}


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
 void save_empty_line(FILE* file){
 	fputc('\n',file);
 }
void save_game(cgame g, char* filename){
  printf("\n\nINFO: Starting saving ...\n");

	char emptyLine[1] = {'\n'};
  int height = game_height(g);
  int width = game_width(g);

  printf("INFO: Creating save file\n");
  FILE* file = fopen(filename,"w");

  printf("INFO: Writing game dimension\n");
  char tmp[100];
  sprintf(tmp, "%d\n%d\n", width,height);
  fputs(tmp, file);

  printf("INFO: Writing monsters available\nINFO: error\n");
  //sprintf(tmp, "%d %d %d %d\n", required_nb_monster(g,ZOMBIE), required_nb_monster(g, GHOST), required_nb_monster(g, VAMPIRE), required_nb_monster(g, SPIRIT));
  //fputs(tmp, file);

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
  for(unsigned int pos = 0; pos < width*height; pos++){
    int posX = pos%width;
    int posY = pos/height;
    sprintf(tmp, "%d ",get_content(g,posX,posY));
    fputs(tmp,file);
  }
	save_empty_line(file);


  fclose(file);
}


int main (void) {
  /* code */
  game g = new_game_ext(4,4);
  int nbMonsters[] = {5,2,2,0};
  generate(g, nbMonsters);
  display(g);
  save_game (g, "test.save");

  return EXIT_SUCCESS;
}
