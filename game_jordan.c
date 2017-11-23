#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/*
jordan :
	set_required_nb_seen
	set_required_nb_monsters
	required_nb_seen
	required_nb_monsters
*/

/**
 * @brief sets the label of a game
 * @param game the game to modify
 * @param side the side of the game where the label should be modified
 * @param pos the position that the label should be modified (from S to N or from W to E)
 * @param value the new value to give to the label
 **/
//call example: set_required_nb_seen (g, N, 0, 0);
void set_required_nb_seen(game g, direction side, int pos, int value){
	if(value < 0 || pos < 0 || pos > COLONNE){
		fprintf(stderr, "Wrong value or pos in fct set_required_nb_seen for pos : %d\n", pos);
		exit(EXIT_FAILURE);
	}

	if(side == N){
		g->valuesNorth[pos] = value;
	} 
	else if(side == S){
		g->valuesSouth[pos] = value;
	} 
	else if(side == E){
		g->valuesEast[pos] = value;
	} 
	else if(side == W){
		g->valuesWest[pos] = value;
	} else {
		fprintf(stderr, "Wrong side given in fct set_required_nb_seen for side :%s\n", side);
		exit(EXIT_FAILURE);
	}
}


/**
 * @brief modifies the aimed number of a given monster on the board
 * @param game the game that you want to modify the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @param value the value you want to set to the parameter.
 **/
//call example: set_required_nb_monsters (g, ZOMBIE,  nbZombie);
void set_required_nb_monsters(game g, content monster, int value){
	if(value < 0) {
		fprintf(stderr, "Wrong value  in fct set_required_nb_monsters for value : %d\n", value);
		exit(EXIT_FAILURE);
	}
	if(monster == ZOMBIE){
		g->zombies = value;
	} 
	else if (monster == VAMPIRE){
		g->vampires = value;
	}
	else if (monster == GHOST){
		g->ghosts = value;
	} else {
		fprintf(stderr, "Wrong monster type in fct set_required_nb_monsters for type : %s\n", monster);
		exit(EXIT_FAILURE);		
	}
}


/**
 * @brief return the label on the side of the board
 * @param game the game we consider
 * @param side the side of the board we want the label from
 * @param pos the position of the label you want (from S to N or from W to E)
 **/
//call example: required_nb_seen (g, S, 0);
int required_nb_seen(cgame g, direction side, int pos){
	if(pos < 0 || pos > COLONNE){
		fprintf(stderr, "Wrong pos in fct required_nb_seen for pos : %d\n", pos);
		exit(EXIT_FAILURE);
	}

	if(side == N){
		return g->valuesNorth[pos];
	} 
	else if(side == S){
		return g->valuesSouth[pos];
	} 
	else if(side == E){
		return g->valuesEast[pos];
	} 
	else if(side == W){
		return g->valuesWest[pos];
	} else {
		fprintf(stderr, "Wrong side given in fct required_nb_seen for side :%s\n", side);
		exit(EXIT_FAILURE);
	}
}


/**
 * @brief indicates the aimed number of a given monster on the board
 * @param game the game that you want to collect the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @return the number of monsters of that type that should be placed on the game.
 **/
//call example: required_nb_monsters (g, GHOST));
int required_nb_monsters(cgame g, content monster){
	if(monster == ZOMBIE){
		return g->zombies;
	} 
	else if (monster == VAMPIRE){
		return g->vampires;
	}
	else if (monster == GHOST){
		return g->ghosts;
	} else {
		fprintf(stderr, "Wrong monster type in fct required_nb_monsters for type : %s\n", monster);
		exit(EXIT_FAILURE);		
	}
}

