#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
//#include <time.h>

//Structure containing the game
struct game_s{
	int **matrice;	//A two dimensional array containing the board content, ie. mirrors and monsters
	int vampires, ghosts, zombies, spirit;
	int width, height;	//Width && height of the board
	int *valuesNorth;	//Those four arrays are here to save the required nb of monster to be seen on each side
	int *valuesSouth;
	int *valuesEast;
	int *valuesWest;
};

/**
 *	Misc.
**/

void memory_test(game g){
	if(g==NULL){
		fprintf(stderr,"Not enough memory!\n");
		exit(EXIT_FAILURE);
	}
	if (g->matrice == NULL){
		fprintf(stderr,"Not enough memory!\n");
		exit(EXIT_FAILURE);

	}
}


/**
 * @brief creates an empty game with all labels and nb of monsters set to 0.
 * @param width number of columns of the board
 * @param height number of lines of the board
 * @return the created game
 **/
 void init_matrice(game g, int width, int height){
 	g->matrice	= (int **)malloc(sizeof(int *) * width);
 	g->matrice[0] = (int *)malloc(sizeof(int) * height * width);
 	for(int i = 0; i < width; i++)
 		g->matrice[i] = (*g->matrice + height * i);

//Initialise each cells of the board with enum type EMPTY
 	for (int x = 0; x <	width; x++){
 		for (int y = 0; y < height; y++){
 			g->matrice[x][y] = EMPTY;
 		}
	}
}

game new_game_ext(int width, int height){
	game g = malloc(sizeof(game)+(3*sizeof(int))+(16*sizeof(int))+4*sizeof(int));

	//Game board creation (dimension : width/height) and required mallocs.
	init_matrice(g, width, height);

	memory_test(g);

	//Put width & height params on structure
	g->height = height;
	g->width = width;

	//Initialisation of numbers of each monsters
	g->vampires	= 0;
	g->ghosts		= 0;
	g->zombies	= 0;
	g->spirit		= 0;

	//Initialisation of each required_nb_seen value
	g->valuesNorth = malloc(width * sizeof(int));
	g->valuesSouth = malloc(width * sizeof(int));
	for(unsigned int i = 0;	i < width;i++){
		g->valuesNorth[i] = 0;
		g->valuesSouth[i] = 0;
	}
	g->valuesEast = malloc(height * sizeof(int));
	g->valuesWest = malloc(height * sizeof(int));
	for(unsigned int i = 0; i < height; i++){
		g->valuesEast[i] = 0;
		g->valuesWest[i] = 0;
	}

	return g;
}


game setup_new_game_ext(int width, int height,
												int *labels[NB_DIR], content * board,
												int required_nb_ghosts, int required_nb_vampires,
												int required_nb_zombies, int required_nb_spirits){
	game g = new_game_ext(width, height);
	memory_test(g);

	g->vampires = required_nb_vampires;
	g->ghosts = required_nb_ghosts;
	g->spirit = required_nb_spirits;
	g->zombies = required_nb_zombies;

	for(int i=0 ; i<g->width ; i++){
		g->valuesNorth[i] = labels[0][i]; // 0 is equivalent to valueNorth
		g->valuesSouth[i] = labels[1][i]; // 1		..	. valueSouth
	}

	for(unsigned int i = 0; i < g->height; i++){
		g->valuesEast[i] = labels[2][i]; //	2		..	. valueEast
		g->valuesWest[i] = labels[3][i]; //	3		..	. valueWest
	}

	int i = 0;
	for(int x=0 ; x<g->height ; x++){
		for (int y=0; y<g->width ; y++){
			g->matrice[y][x] = board[i];
			i++;
		}
	}

	return g;
}




int game_height(cgame game){
	return game->height;
}
int game_width(cgame game){
	return game->width;
}


void add_mirror_ext(game game, content mirror_type, int col, int line){
		memory_test(game);
		assert(game);

		if (col < 0 || col >= game->width){		//If x isnt a valid position
			fprintf(stderr, "Wrong x parameter on get_content call\n");
		} else if (line < 0 || line >= game->height){	//If y isnt a valid position
			fprintf(stderr, "Wrong y parameter on get_content call\n");
		}

		if (mirror_type != MIRROR && mirror_type != ANTIMIRROR && mirror_type != VMIRROR && mirror_type != HMIRROR){
			fprintf(stderr,"Error while placing mirror\n");
			return;
		}
		game->matrice[col][line] = mirror_type;
}



void set_required_nb_seen(game game, direction side, int pos, int value){
	memory_test(game);
	if(value < 0 || pos < 0 || pos > game->width){
		fprintf(stderr, "Wrong value or pos in fct set_required_nb_seen2 for pos : %d\n", pos);
		return;
	}
	if(side == N){
		game->valuesNorth[pos] = value;
	}
	else if(side == S){
		game->valuesSouth[pos] = value;
	}
	else if(side == E){
		game->valuesEast[pos] = value;
	}
	else if(side == W){
		game->valuesWest[pos] = value;
	} else {
		fprintf(stderr, "Wrong side given in fct set_required_nb_seen for side :%c\n", side);
		return;
	}

}



void set_required_nb_monsters(game game, content monster, int value){
	memory_test(game);
	if(value < 0) {
		fprintf(stderr, "Wrong value	in fct set_required_nb_monsters2 for value : %d\n", value);
		return;
	}
	if(monster == ZOMBIE){
		game->zombies = value;
	} else if (monster == VAMPIRE){
		game->vampires = value;
	}	else if (monster == GHOST){
		game->ghosts = value;
	}	else if (monster == SPIRIT){
		game->spirit = value;
	} else {
		fprintf(stderr, "Wrong monster type in fct set_required_nb_monsters for type : %c\n", monster);
		return;
	}
}


game copy_game (cgame g_src){
	if(!g_src || !g_src -> matrice){
		fprintf(stderr, "Error in Function copy_game : Invalid parameters");
		return NULL;
	}
	game copy_game = new_game_ext(g_src->width, g_src->height);

	copy_game->vampires = g_src->vampires;
	copy_game->ghosts = g_src->ghosts;
	copy_game->zombies = g_src->zombies;

	for (int x = g_src->width-1; x >= 0; x--){
		for(int y = 0; y < g_src->height; y++){
			copy_game -> matrice[x][y] = g_src -> matrice [x][y];
		}
	}


	for(int i = 0; i < g_src->width; i++){
		copy_game -> valuesNorth[i] = g_src -> valuesNorth[i];
		copy_game -> valuesSouth[i] = g_src -> valuesSouth[i];
	}

	for(unsigned int i = 0; i < g_src->height; i++){
		copy_game -> valuesEast[i] = g_src -> valuesEast[i];
		copy_game -> valuesWest[i] = g_src -> valuesWest[i];
	}

	return copy_game;
}



void delete_game (game g){
	memory_test(g);

	free(g->matrice[0]);
	free(g->matrice);
	free(g->valuesNorth);
	free(g->valuesSouth);
	free(g->valuesEast);
	free(g->valuesWest);
	free(g);
}



int required_nb_seen(cgame game, direction side, int pos){
	if(pos < 0){
		fprintf(stderr, "Wrong pos in fct required_nb_seen for pos : %d\n", pos);
		return EXIT_FAILURE;
	}

	if(side == N || side == S){
			if(pos >= game->width){
				fprintf(stderr, "Wrong pos in fct required_nb_seen for posz : %d && side: %d\n", pos, side);
				return EXIT_FAILURE;
		}
	}else{
		if(pos >= game->height){
			fprintf(stderr, "Wrong pos in fct required_nb_seen for pos : %d && side: %d\n", pos, side);
				return EXIT_FAILURE;
		}
	}
	switch (side){
		case N:
			return game->valuesNorth[pos];
		case S:
			return game->valuesSouth[pos];
		case E:
			return game->valuesEast[pos];
		case W:
			return game->valuesWest[pos];
		default:
			fprintf(stderr, "Wrong side given in fct required_nb_seen2 for side :%c\n", side);
			return EXIT_FAILURE;
	}
}



content get_content(cgame game, int col, int line){
	if (col < 0 || col >= game->width){		//	If col is invalid
		fprintf(stderr, "Wrong x parameter on get_content call\n");
	} else if (line < 0 || line >= game->height){	//	If line is invalid
		fprintf(stderr, "Wrong y parameter on get_content call\n");
	} else { 						// If all pos are okay
		int tick_content = game->matrice[col][line];
		return tick_content;
	}
	return EXIT_FAILURE;
}



int required_nb_monsters(cgame game, content monster){
	switch(monster){
		case ZOMBIE:
			return game->zombies;
		case VAMPIRE:
			return game->vampires;
		case GHOST:
			return game->ghosts;
		case SPIRIT:
			return game->spirit;
		default:
			fprintf(stderr, "Wrong monster type in fct required_nb_monsters2 for type : %c\n", monster);
			return EXIT_FAILURE;
	}
}




void restart_game(game g){
	memory_test(g);

	int tick_content;
	//We get the content of each cells
	for(int x = 0; x < g->width; x++){
		for(int y = 0; y < g->height ; y++){
			tick_content = g->matrice[x][y];
			//If cell is a monster, then replace by empty
			switch(tick_content){
				case MIRROR:
					break;
				case ANTIMIRROR:
					break;
				case HMIRROR:
					break;
				case VMIRROR:
					break;
				default:
					g->matrice[x][y]=EMPTY;
					break;
			}
		}
	}
}



bool add_monster(game game, content monster, int col, int line){
	memory_test(game);

	//If x && y position is any mirror type
	if(game->matrice[col][line] == MIRROR || game->matrice[col][line] == ANTIMIRROR
																|| game->matrice[col][line] == VMIRROR
																|| game->matrice[col][line] == HMIRROR){
		return false;
	} else if(col >=game->width || col < 0 || line < 0 || line >= game->height){	//If the position x OR y is out of the matrice
				return false;
	} else {//If everything is ok
		game->matrice[col][line] = monster;
	}
	return false;
}






direction direction_after_antimirror(direction side) {
	switch(side){
		case N:
			return W;
		case S:
			return E;
		case E:
			return S;
		case W:
			return N;
		default:
			fprintf(stderr, "Error while switching side after a an antimirror\n");
			return EXIT_FAILURE;
	}
}

direction direction_after_mirror(direction side) {
	switch(side){
		case N:
			return E;
		case S:
			return W;
		case E:
			return N;
		case W:
			return S;
		default:
			fprintf(stderr, "Error while switching side after a mirror\n");
			return EXIT_FAILURE;
	}
}

direction direction_after_vmirror(direction side) {
	switch(side){
		case N:
			return N;
		case S:
			return S;
		case E:
			return W;
		case W:
			return E;
		default:
			fprintf(stderr, "Error while switching side after a vertical mirror\n");
			return EXIT_FAILURE;
	}
}

direction direction_after_hmirror(direction side) {
	switch(side){
		case N:
			return S;
		case S:
			return N;
		case E:
			return E;
		case W:
			return W;
		default:
			fprintf(stderr, "Error while switching side after a horizontal mirror\n");
			return EXIT_FAILURE;
	}
}



int *next_pos(int * pos, direction side){
	switch(side){
		case N:
			pos[1]--;
			return pos;
		case S:
			pos[1]++;
			return pos;
		case E:
			pos[0]--;
			return pos;
		case W:
			pos[0]++;
			return pos;
		default:
			fprintf(stderr, "Unable to calculate next position for\nNext_pos.\n");
			exit(EXIT_FAILURE);
	}
}

int *current_nb_seen_init(cgame g, int pos, int *posTab, direction side){
	int posX=0, posY=0;
	if(side == N){
			posX=pos;
			posY=g->width-1;

	}else if (side == S){
			posX=pos;
			posY=0;

	}else if (side == E){
			posX=g->height-1;
			posY=pos;

	}else if (side == W){
			posX=0;
			posY=pos;
	}
	posTab[0]=posX;
	posTab[1]=posY;
	return posTab;
}

int current_nb_seen(cgame game, direction side, int pos){
	/**
	*
	*	Initialisation :
	*		mirror_seen say if a mirror as already been seen, or not
	*		isEnd if true ONLY IF we are going out of the board
	*		sum is the number of monsters seen returned
	*		posTab is an array with the position X && Y
	*
	**/
	bool mirror_seen = false;
	bool isEnd			 = false;
	int sum = 0;

	int *posTab = malloc(sizeof(int)*2);//array with the position x && y; sizeof(int)*2 because that's an array with 2 cells
	posTab = current_nb_seen_init(game, pos, posTab, side);	//Init. of the position with the side & pos parameters

	while(!isEnd){
		//If x OR y is invalid
		if (posTab[0] <0
					|| posTab[0] >= game->width
					|| posTab[1] < 0
					|| posTab[1] >= game->height) {
			free(posTab);
			return sum;
		}


	/**
	*	RAPPEL: posTab[0] = the X position , posTab[0] = the Y position
	*	Here, we check the content of the cell. Depending of his content and
	*	if a mirror has been seen (or not) (var. mirror_seen) we increment the number of monsters seen
	*	from the side parameters and his position on this side
	**/
		if(game->matrice[posTab[0]][posTab[1]] == ZOMBIE){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == GHOST && mirror_seen){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == SPIRIT){
			//ON FAIT QUE DALLE
		}else if(game->matrice[posTab[0]][posTab[1]] == VAMPIRE && !mirror_seen){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == MIRROR){
			side = direction_after_mirror(side);//Switching side
			if(!mirror_seen)//We only change this value if it has not been changed before -little optimisation ?-
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == ANTIMIRROR){
			side = direction_after_antimirror(side);//Switching side
			if(!mirror_seen)
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == VMIRROR){
			side = direction_after_vmirror(side);//Switching side
			if(!mirror_seen)
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == HMIRROR){
			side = direction_after_hmirror(side);//Switching side
			if(!mirror_seen)
				mirror_seen=true;
		}

		posTab=next_pos(posTab, side);//Calculate the next position

	}
	return sum;
}


int current_nb_monsters(cgame game, content monster){
	int sum = 0;
	for(int x=0;x<game->width;x++){
		for(int y=0;y<game->height;y++){
			if (game->matrice[x][y]==monster)
				sum++;
		}
	}
	return sum;
}


bool is_game_over (cgame g){
	//Check the numbers of monsters
	//ie. : if numbers on the board != number of monster to use
	if (required_nb_monsters(g, ZOMBIE) != current_nb_monsters(g, ZOMBIE)){
		return false;
	} else if (required_nb_monsters(g, GHOST) != current_nb_monsters(g, GHOST)){
		return false;
	} else if (required_nb_monsters(g, VAMPIRE) != current_nb_monsters(g, VAMPIRE)){
		return false;
	}else if (required_nb_monsters(g, SPIRIT) != current_nb_monsters(g, SPIRIT)){
		return false;
	}


	//check numbers of monsters seen
	for(unsigned int dir = 0; dir < NB_DIR; dir++){
		for(unsigned int pos = 0; pos < g->width; pos++){
			if(current_nb_seen(g, dir, pos) != required_nb_seen(g,dir,pos)){
				return false;
			}
		}
	}
	return true;
}




/**
 *
 *	OLD FUNCTIONS - ie. V1 FUNCTIONS -
 *
**/

/**
 * @brief creates an empty game with all squares set to empty, all labels and the number of required monsters set to 0.
 * @return the created game
 **/
void init_matrice_old(game g){
	g->matrice	= (int **)malloc(sizeof(int *) * game_width(g));
	g->matrice[0] = (int *)malloc(sizeof(int) * game_height(g) * game_width(g));
	for(int i = 0; i < game_width(g); i++)
		g->matrice[i] = (*g->matrice + game_height(g) * i);

	for (int x = 0; x <	game_width(g); x++){
		for (int y = 0; y < game_height(g); y++){
			g->matrice[x][y] = EMPTY;	// OR *(*(g->matrice+i)+j) = ++count
		}
	}
}

game new_game(void){
	game g = new_game_ext(4,4);
	return g;
}


/**
 * @brief creates a game from a board description.
 * It uses a given board possibly with its mirrors, and a list of labels.
 * @param labels an array of four pointers towards array of labels (namely, labels[N], labels[S], labels[E], labels[W]).
 * The labels are given according to increasing coordinate value (from S to N or from W to E)
 * @param board an array of all the board squares, stored sequentially line by line starting from coordinate (0,0)
 * @param required_nb_ghosts the number of ghosts required in the game.
 * @param required_nb_vampires the number of vampires required in the game.
 * @param required_nb_zombies the number of zombies required in the game.
 * @return the created game
 **/
game setup_new_game(int *labels[NB_DIR], content * board, int required_nb_ghosts,	int required_nb_vampires, int required_nb_zombies){
	game g = new_game();
	memory_test(g);

	g->vampires = required_nb_vampires;
	g->ghosts = required_nb_ghosts;
	g->zombies = required_nb_zombies;

	for(int i=0 ; i<game_width(g) ; i++){
		g->valuesNorth[i] = labels[0][i]; // 0 is	equivalent to valueNorth
		g->valuesSouth[i] = labels[1][i]; // 1		..	. valueSouth
	}

	for(unsigned int i = 0; i < game_height(g); i++){
		g->valuesEast[i] = labels[2][i]; // 2		..	. valueEast
		g->valuesWest[i] = labels[3][i]; // 3		..	. valueWest
	}

	int i = 0;
	for(int x=0; x<game_height(g); x++){
		for (int y=0; y<game_width(g); y++){
			g->matrice[y][x] = board[i];
			i++;
		}
	}

	return g;
}


/**
 * @brief adds a mirror on the game board
 * @param game the game board where to add the mirror
 * @param dir the direction on which to add the mirror: 0 for +45 degrees (/), 1 for -45 degrees (\\)
 * @param col which column to insert the mirror on (0<=col<4)
 * @param line which line to insert the mirror on (0<=line<4)
 **/
void add_mirror(game g, int dir, int x, int y){
	if(dir == 0){
		add_mirror_ext(g, MIRROR, x, y);
	}
	add_mirror_ext(g, ANTIMIRROR, x, y);
}
