#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
//#include "game_jordan.h"

/*
Amir : 
	copy_game
	delete_game
	get_content
	is_game_over
*/



#define COLONNE 4
#define LINE 4

struct game_s{
 int ** matrice;
 int vampires;
 int ghosts;
 int zombies;
 int valuesNorth[4];
 int valuesSouth[4];
 int valuesEast[4];
 int valuesWest[4];
};

typedef enum content_e {EMPTY, MIRROR, ANTIMIRROR, VAMPIRE, GHOST, ZOMBIE} content;
#define NB_POSSIBLE_FILLINGS 6


typedef enum direction_e {N,S,E,W} direction;
#define NB_DIR 4


/**
 * @brief Test if the game is over (that is the grid is filled according to the requirements).
 * @return true if all the constraints are satisfied
 **/
/**
 * @brief The structure pointer that stores the game
 **/

typedef struct game_s* game;
typedef const struct game_s* cgame;

bool is_game_over (cgame g){
	//Verification du nombre de monstres
	if (required_nb_monsters(g, ZOMBIE) != current_nb_monsters(g, ZOMBIE)){
		return false;
	} else if (required_nb_monsters(g, GHOST) != current_nb_monsters(g, GHOST)){
		return false;
	} else if (required_nb_monsters(g, VAMPIRE) != current_nb_monsters(g, VAMPIRE)){
		return false;
	}

	//verification des monstres vu
	for(unsigned int dir = 0; dir < 4; dir++){
		for(unsigned int pos = 0; pos < COLONNE; pos++){
			if(current_nb_seen(g, dir, pos) != required_nb_seen(g,dir,pos)){
				return false;
			}
		}
	}
	return true;
}





/**
 * @brief Clone the game g_src
 * @param g_src the game to clone
 * @return the clone of g_src
 **/
game copy_game (cgame g_src){
	if(!g_src || ! g_src -> matrice){
		fprintf(stderr, "Error in Function copy_game : Invalid parameters");
		exit(EXIT_FAILURE);
	}
	game copy_game = new_game();

	copy_game -> vampires = g_src -> vampires;
	copy_game -> ghosts = g_src -> ghosts;
	copy_game -> zombies = g_src -> zombies;

	for (int i = 0; i < LINE * COLONNE; i++){
		copy_game -> matrice[i] = g_src -> matrice [i];
	}
	for(int i = 0; i < 4; i++){
		copy_game -> valuesNorth[i] = g_src -> valuesNorth[i];
		copy_game -> valuesSouth[i] = g_src -> valuesSouth[i];
		copy_game -> valuesEast[i] = g_src -> valuesEast[i];
		copy_game -> valuesWest[i] = g_src -> valuesWest[i];
	}

	return copy_game;
}


/**
 * @brief Destroy the game and free allocated memory
 * @param g the game to destroy
 **/
void delete_game (game g);


/**
 * @brief get the content of a square in the board
 * @param game the game we consider
 * @param col the column of the square
 * @param line the line of the square
 * @return the content of the square
 **/

content get_content(cgame game, int col, int line);
