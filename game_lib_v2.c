#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include <time.h>

#define COLONNE 4
#define LINE 4

//Structure containing the game
struct game_s{
	int **matrice;
	int vampires;
	int ghosts;
	int zombies;
  int spirit;
  int width;
  int height;
	int valuesNorth[4];
	int valuesSouth[4];
	int valuesEast[4];
	int valuesWest[4];
};

typedef struct game_s* game;
typedef const struct game_s* cgame;

//All possible tick content
typedef enum content_e {EMPTY, MIRROR, ANTIMIRROR, VMIRROR, HMIRROR, VAMPIRE, GHOST, ZOMBIE, SPIRIT} content;
#define NB_POSSIBLE_FILLINGS 9

//Four cardinals directions
typedef enum direction_e {N,S,E,W} direction;
#define NB_DIR 4

/**
 *  Misc.
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
 * @brief creates an empty game with all labels set to 0.
 * @param width number of columns of the board
 * @param height number of lines of the board
 * @return the created game
 **/

//Line-> height
//COLONNE-> width
 void init_matrice(game g, int width, int height){
 	g->matrice  = (int **)malloc(sizeof(int *) * width);
 	g->matrice[0] = (int *)malloc(sizeof(int) * height * width);
 	for(int i = 0; i < width; i++)
 		g->matrice[i] = (*g->matrice + height * i);

 	for (int x = 0; x <  width; x++){
 		for (int y = 0; y < height; y++){
 			g->matrice[x][y] = EMPTY;  // OR *(*(g->matrice+i)+j) = ++count
 		}
  }
}

game new_game_ext(int width, int height){
	game g = malloc(sizeof(game)+(3*sizeof(int))+(16*sizeof(int)));
	//Creation de la zone de jeu (ici de dimension LINE*COLONNE) et on rempli chaque case
	//par empty
	init_matrice(g, width, height);

	memory_test(g);

  //Put width & height params on structure
  g->height = height;
  g->width = width;

	//Nombre de monstres requis initialise a zero
	g->vampires  = 0;
	g->ghosts    = 0;
	g->zombies   = 0;
  g->spirit    = 0;

	//nombre de monstres vu requis
	for(unsigned int i = 0;  i < width;i++){
		g->valuesNorth[i] = 0;
		g->valuesSouth[i] = 0;
	}

	for(unsigned int i = 0; i < height; i++){
		g->valuesEast[i] = 0;
		g->valuesWest[i] = 0;
	}

	return g;
}

/**
 * @brief creates a game from a board.
 * It uses a given board possibly with its mirrors, and a list of labels.
 * It checks that the proposed dimensions (that should match the list)
 * match the size of the board.
 *
 * @param width number of columns of the board
 * @param height number of lines of the board
 * @param labels an array of four pointers towards array of labels (namely, labels[N], labels[S], labels[E], labels[W]).
 * The labels are given according to increasing coordinate value (from S to N or from W to E)
 * @param board an array of all the board squares, stored line-by-line (possibly with mirrors set already)
 * @param required_nb_ghosts the number of ghosts required in the game.
 * @param required_nb_vampires the number of vampires required in the game.
 * @param required_nb_zombies the number of zombies required in the game.
 * @param required_nb_spirits the number of spirits required in the game.
 * @return the created game
 **/

game setup_new_game_ext(int width, int height, int *labels[NB_DIR], content * board,
                        int required_nb_ghosts,  int required_nb_vampires,
                        int required_nb_zombies, int required_nb_spirits);





int game_height(cgame game){
  return game->height;
}

int game_width(cgame game){
  return game->width;
}


/**
 * @brief adds a mirror on the game board
 * @param game the game board where to add the mirror
 * @param mirror_type a content that corresponds to a mirror (MIRROR, ANTI_MIRROR, VMIRROR or HMIRROR)
 * @param col which column to insert the mirror on. (0<=col<width)
 * @param line which line to insert the mirror on (0<=line<height)
 **/

void add_mirror_ext(game game, content mirror_type, int col, int line){
  	memory_test(game);
  	assert(game);

  	if (col < 0 || col >= game->width){		//Si x est en dehors de la matrice
  		fprintf(stderr, "Wrong x parameter on get_content call\n");
  	} else if (line < 0 || line >= game->height){	//Si y est en dehors de la matrice
  		fprintf(stderr, "Wrong y parameter on get_content call\n");
  	}

  	if(mirror_type == MIRROR){
  		game->matrice[col][line] = MIRROR ;
  	} else if (mirror_type == ANTIMIRROR) {
  		game->matrice[col][line] = ANTIMIRROR ;
  	} else if (mirror_type == VMIRROR) {
  		game->matrice[col][line] = VMIRROR ;
  	} else if (mirror_type == HMIRROR) {
  		game->matrice[col][line] = HMIRROR ;
  	} else {
  		fprintf(stderr,"Error while placing mirror");
  	}
}



/**
 * @brief sets the label of a game
 * @param game the game to modify
 * @param side the side of the game where the label should be modified
 * @param pos the position that the label should be modified (from S to N or from W to E)
 * @param value the new value to give to the label
 **/

void set_required_nb_seen(game game, direction side, int pos, int value){
	memory_test(game);
	if(value < 0 || pos < 0 || pos > game->width){
		fprintf(stderr, "Wrong value or pos in fct set_required_nb_seen2 for pos : %d\n", pos);
		//exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}

}



/**
 * @brief modifies the aimed number of a given monster on the board
 * @param game the game that you want to modify the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE, ZOMBIE or SPIRIT)
 * @param value the value you want to set to the parameter.
 **/

void set_required_nb_monsters(game game, content monster, int value){
	memory_test(game);
	if(value < 0) {
		fprintf(stderr, "Wrong value  in fct set_required_nb_monsters2 for value : %d\n", value);
		//exit(EXIT_FAILURE);
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
		//exit(EXIT_FAILURE);
	}
}


/**
 * @brief Clone the game g_src
 * @param g_src the game to clone
 * @return the clone of g_src
 **/
game copy_game (cgame g_src){
	if(!g_src || !g_src -> matrice){
		fprintf(stderr, "Error in Function copy_game : Invalid parameters");
		//exit(EXIT_FAILURE);
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


/**
 * @brief Destroy the game and free allocated memory
 * @param g the game to destroy
 **/
void delete_game (game g){
	memory_test(g);
	g->vampires = 0;
	g->ghosts = 0;
	g->zombies = 0;


	for(int i=0 ; i< g->width ; i++){
		g->valuesNorth[i] = 0; // on supose que 0 equivalent a valueNorth
		g->valuesSouth[i] = 0; // ..	..   .. 1	  ..	. valueSouth
	}

	for(unsigned int i = 0; i < g->height; i++){
		g->valuesEast[i] = 0; //  ..	..   .. 2	  ..	. valueEast
		g->valuesWest[i] = 0; //  ..	..   .. 3	  ..	. valueWest
	}


	for(unsigned int x = 0; x < g->height; x++){
		for(unsigned int y = 0; y < g->width; y++){
			g->matrice[x][y] = EMPTY;
		}
	}
	free(g->matrice[0]);
	free(g->matrice);
	free(g);
}


/**
 * @brief return the label on the side of the board
 * @param game the game we consider
 * @param side the side of the board we want the label from
 * @param pos the position of the label you want (from S to N or from W to E)
 **/

int required_nb_seen(cgame game, direction side, int pos){
	if(pos < 0 || pos > game->width){
		fprintf(stderr, "Wrong pos in fct required_nb_seen for pos : %d\n", pos);
		//exit(EXIT_FAILURE);
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



/**
 * @brief get the content of a square in the board
 * @param game the game we consider
 * @param col the column of the square
 * @param line the line of the square
 * @return the content of the square
 **/

content get_content(cgame game, int col, int line){
	if (col < 0 || col >= game->width){		//Si col est en dehors de la matrice
		fprintf(stderr, "Wrong x parameter on get_content call\n");
	} else if (line < 0 || line >= game->height){	//Si line est en dehors de la matrice
		fprintf(stderr, "Wrong y parameter on get_content call\n");
	} else { 						//Si les pos sont ok
		int tick_content = game->matrice[col][line];
		return tick_content;
	}
	return EXIT_FAILURE;
}



/**
 * @brief indicates the aimed number of a given monster on the board
 * @param game the game that you want to collect the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE, ZOMBIE or SPIRIT)
 * @return the number of monsters of that type that should be placed on the game.
 **/

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




/**
 * @brief Restart a game by cleaning monsters from the board.
 **/

void restart_game(game g){
	memory_test(g);

	int tick_content;
	//On parcours l'ensemble de la matrice
	for(int x = 0; x < g->width; x++){
		for(int y = 0; y < g->height ; y++){
			tick_content = g->matrice[x][y];
			//Si le contenu de la case == un monstre, alors on le remplace par EMPTY
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


/**
 * @brief adds a monster on the game board.
 * Can also be used to remove any monster by adding EMPTY.
 * This function does not have effect on mirrors so it can be used safely in the course of the game.
 * @param game the game board where to add the monster
 * @param monster the type of monster to add
 * @param col the column where to insert the monster
 * @param line and the line where to insert the monster
 * @return false if the monster was not placed since the square was occupied by a mirror.
 **/

bool add_monster(game game, content monster, int col, int line){
	memory_test(game);

	//Si la position x et y pointe sur un miroir ou un antimiroir
	if(game->matrice[col][line] == MIRROR || game->matrice[col][line] == ANTIMIRROR
                                || game->matrice[col][line] == VMIRROR
                                || game->matrice[col][line] == HMIRROR){
		return false;
	} else if(col >=game->width || col < 0 || line < 0 || line >= game->height){	//Si la position x ou y est en dehors de la matrice
		return false;
	} else {//Si tout est ok
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
			return S;
		case S:
			return N;
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
			return W;
		case W:
			return E;
		default:
			fprintf(stderr, "Error while switching side after a horizontal mirror\n");
			return EXIT_FAILURE;
	}
}


/**
*Appelee a chaque tours de boucle de current_nb_seen
*	calcule la prochaine position en fct de sa pos actuelle
*	et de son side
*
**/
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
			fprintf(stderr, "Unable to calculate next position for\ncurrent_nb_seen.\n");
			exit(EXIT_FAILURE);
	}
}


/**
*
*	Calcul la position initiale en X et Y en fonction du side
*	et de sa position sur ce Side
*
**/
int *current_nb_seen_init(int pos, int *posTab, direction side){
	int posX=0, posY=0;
	if(side == N){
			posX=pos;
			posY=COLONNE-1;

	}else if (side == S){
			posX=pos;
			posY=0;

	}else if (side == E){
			posX=LINE-1;
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
	//memory_test(game);

	/**
	*
	*	Initialisation :
	*		mirror_seen dit si un miroir a deja ete vu ou pas
	*		isEnd est true ssi on sort du board
	*		sum le nombre de monstres vu retourne
	*		posTab un tableau contenant la positon X et la position Y
	*
	**/

	bool mirror_seen = false;
	bool isEnd       = false;
	int sum = 0;

	int *posTab = malloc(sizeof(int)*2);//Tableau contenant la position x, et la position y
	posTab = current_nb_seen_init(pos, posTab, side);  //Initialisation des positions en fonction du side et de pos

	while(!isEnd){
		//Si la position x OU y sort de la matrice
		if (posTab[0] <0
          || posTab[0] > game->width -1
          || posTab[1] < 0
          || posTab[1] > game->height -1) {
  		free(posTab);
  		return sum;
		}


	/**
	*	RAPPEL: posTab[0] = la position en X, posTab[0] = la position en Y
	*	Ici, on verifie le contenu de la case. En fonction de son contenu et
	*	de si un miroir a été vu (ou pas) on incrémente le nombre de monstre vu
	*	depuis le side passe en parametre et sa position
	**/
		if(game->matrice[posTab[0]][posTab[1]] == ZOMBIE){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == GHOST && mirror_seen){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == VAMPIRE && !mirror_seen){
			sum+=1;
		}else if(game->matrice[posTab[0]][posTab[1]] == MIRROR){
			side = direction_after_mirror(side);//Changement du side
			if(!mirror_seen)//On ne change la valeur que si elle n'avait pas été changée, (petite opti ?)
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == ANTIMIRROR){
			side = direction_after_antimirror(side);//Changement du side
			if(!mirror_seen)
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == VMIRROR){
			side = direction_after_vmirror(side);//Changement du side
			if(!mirror_seen)
				mirror_seen=true;
		}else if(game->matrice[posTab[0]][posTab[1]] == HMIRROR){
			side = direction_after_hmirror(side);//Changement du side
			if(!mirror_seen)
				mirror_seen=true;
		}

		posTab=next_pos(posTab, side);//On calcule la prochaine position

	}
	return sum;
}



/**
 * @brief counts the current number of monsters of a given type
 * @param game the game board
 * @param monster the type of monster
 * @return the total number of monsters of the given type on the board.
 **/

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

/**
 * @brief Test if the game is over (that is the grid is filled according to the requirements).
 * @return true if all the constraints are satisfied
 **/

bool is_game_over (cgame g){
	//Verification du nombre de monstres
	//ie. : si le nombre de monstres posé != nombre de monstres requis
	if (required_nb_monsters(g, ZOMBIE) != current_nb_monsters(g, ZOMBIE)){
		return false;
	} else if (required_nb_monsters(g, GHOST) != current_nb_monsters(g, GHOST)){
		return false;
	} else if (required_nb_monsters(g, VAMPIRE) != current_nb_monsters(g, VAMPIRE)){
		return false;
	}else if (required_nb_monsters(g, SPIRIT) != current_nb_monsters(g, SPIRIT)){
		return false;
	}

	//On cree une copie de type 'game' de 'cgame'
	game g2 = (game) g;
	//verification des monstres vu
	for(unsigned int dir = 0; dir < NB_DIR; dir++){
		for(unsigned int pos = 0; pos < g->width; pos++){
			if(current_nb_seen(g2, dir, pos) != required_nb_seen(g,dir,pos)){
				return false;
			}
		}
	}
	return true;
}


int main(){
	game g = new_game_ext(5,5);
	return 1;
}
