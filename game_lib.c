#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define COLONNE 4
#define LINE 4

#define nbVampire 2;
#define nbGhost 2;
#define nbZombie 5;

//Structure containing the game 
struct game_s{
	int **matrice;
	int vampires;
	int ghosts;
	int zombies;
	int valuesNorth[4];
	int valuesSouth[4];
	int valuesEast[4];
	int valuesWest[4];
};
typedef struct game_s* game;
typedef const struct game_s* cgame;

//All possible tick content
typedef enum content_e {EMPTY, MIRROR, ANTIMIRROR, VAMPIRE, GHOST, ZOMBIE} content; 
#define NB_POSSIBLE_FILLINGS 6

//Four cardinals directions
typedef enum direction_e {N,S,E,W} direction; 
#define NB_DIR 4


void init_matrice(game g){  
    g->matrice  = (int **)malloc(sizeof(int *) * COLONNE);
    g->matrice[0] = (int *)malloc(sizeof(int) * LINE * COLONNE); 
    for(int i = 0; i < COLONNE; i++)
        g->matrice[i] = (*g->matrice + LINE * i);
  
    for (int x = 0; x <  COLONNE; x++){
        for (int y = 0; y < LINE; y++){
            g->matrice[x][y] = EMPTY;  // OR *(*(g->matrice+i)+j) = ++count
  		}
  	}

  	//DEBUG PURPOSE
  	/*
    for (int x = 0; x <  COLONNE; x++){
        for (int y = 0; y < LINE; y++){
            printf("%d ", g->matrice[x][y]);
        }
        printf("\n");
    }
    printf("\n");
    */
}



game new_game(void){
	game g = malloc(sizeof(game)+(3*sizeof(int))+(16*sizeof(int)));
    if(g==NULL){
      fprintf(stderr,"Not enough memory!\n");
      //exit(EXIT_FAILURE);
    }

	init_matrice(g);
	g->vampires = 0;
	g->ghosts = 0;
	g->zombies = 0;
	
    g->valuesNorth[0] = malloc(sizeof(int)*4); 
    g->valuesSouth[0] = malloc(sizeof(int)*4); 
    g->valuesEast[0] = malloc(sizeof(int)*4); 
    g->valuesWest[0] = malloc(sizeof(int)*4); 
    
	for(unsigned int i = 0;  i < COLONNE;i++){
		g->valuesNorth[i] = 0;
		g->valuesSouth[i] = 0;
		g->valuesEast[i] = 0;
		g->valuesWest[i] = 0;
	}
	return g;
}

/* sample : 
bool res = true;
  int nb_ghosts = 2;
  int nb_vampires = 2;
  int nb_zombies = 5;
  int valueNorth[] = {0, 3, 3, 0};
  int valueSouth[] = {0, 3, 2, 3};
  int valueEast[] = {0, 0, 3, 2};
  int valueWest[] = {0, 2, 3, 3};
  int *values [] = {valueNorth, valueSouth, valueEast, valueWest};
  content gameBoard[]={ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, MIRROR, ANTIMIRROR, EMPTY, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, MIRROR};
  game g = setup_new_game(values, gameBoard, nb_ghosts, nb_vampires ,nb_zombies);
*/

/*
  bool res = true;
  int nb_ghosts = 2;
  int nb_vampires = 2;
  int nb_zombies = 5;
  int valueNorth[] = {0, 3, 3, 0};
  int valueSouth[] = {0, 3, 2, 3};
  int valueEast[] = {0, 0, 3, 2};
  int valueWest[] = {0, 2, 3, 3};
  int *values [] = {valueNorth, valueSouth, valueEast, valueWest};
  content gameBoard[]={ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, MIRROR, ANTIMIRROR, EMPTY, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, MIRROR};
  game g = setup_new_game(values, gameBoard, nb_ghosts, nb_vampires ,nb_zombies);
*/
game setup_new_game(int *labels[NB_DIR], content * board, int required_nb_ghosts,  int required_nb_vampires, int required_nb_zombies){
  game g = new_game();
  g->vampires = required_nb_vampires;
  g->ghosts = required_nb_ghosts;
  g->zombies = required_nb_zombies;
  for(int i=0 ; i<COLONNE ; i++){
    g->valuesNorth[i] = labels[0][i]; // on supose que 0 equivalent a valueNorth
    g->valuesSouth[i] = labels[1][i]; // ..    ..   .. 1      ..    . valueSouth
    g->valuesEast[i] = labels[2][i]; //  ..    ..   .. 2      ..    . valueEast
    g->valuesWest[i] = labels[3][i]; //  ..    ..   .. 3      ..    . valueWest
  }

  int i = 0; // caze parce que case c'est un reserver au switch case
  for(int x=0 ; x<LINE ; x++){
    for (int y=0; y>COLONNE ; y++){
      g->matrice[x][y] = board[i];
      i++;
    }
  }

  return g;

}

void add_mirror(game g, int dir, int x, int y){
  assert(g);
  if(dir == 0){
    	g->matrice[x][y] = MIRROR ;

  } else if (dir == 1) {
    	g->matrice[x][y] = ANTIMIRROR ;
  } else {
  	fprintf(stderr,"Error while placing mirror");
  }
}

void delete_game (game g){
	g->vampires = 0;
	g->ghosts = 0;
	g->zombies = 0;
	for(unsigned int i = 0;  i < COLONNE;i++){
		g->valuesNorth[i] = 0;
		g->valuesSouth[i] = 0;
		g->valuesEast[i] = 0;
		g->valuesWest[i] = 0;
	}

	for(unsigned int x = 0; x < LINE; x++){
		for(unsigned int y = 0; y < COLONNE; y++){
			g->matrice[x][y] = EMPTY;
		}
	}
	free(g->vampires);
	free(g->matrice);
	free(g->valuesWest[0]);
	free(g->valuesSouth[0]);
	free(g->valuesNorth[0]);
	free(g->valuesEast[0]);
	free(g);
}



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
//call example: set_required_nb_seen2 (g, N, 0, 0);
void set_required_nb_seen(game g, direction side, int pos, int value){
	if(value < 0 || pos < 0 || pos > COLONNE){
		fprintf(stderr, "Wrong value or pos in fct set_required_nb_seen2 for pos : %d\n", pos);
		//exit(EXIT_FAILURE);
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
		fprintf(stderr, "Wrong side given in fct set_required_nb_seen for side :%c\n", side);
		exit(EXIT_FAILURE);
	}
}


/**
 * @brief modifies the aimed number of a given monster on the board
 * @param game the game that you want to modify the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @param value the value you want to set to the parameter.
 **/
//call example: set_required_nb_monsters2 (g, ZOMBIE,  nbZombie);
void set_required_nb_monsters(game g, content monster, int value){
	if(value < 0) {
		fprintf(stderr, "Wrong value  in fct set_required_nb_monsters2 for value : %d\n", value);
		//exit(EXIT_FAILURE);
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
		fprintf(stderr, "Wrong monster type in fct set_required_nb_monsters for type : %c\n", monster);
		//exit(EXIT_FAILURE);		
	}
}


/**
 * @brief return the label on the side of the board
 * @param game the game we consider
 * @param side the side of the board we want the label from
 * @param pos the position of the label you want (from S to N or from W to E)
 **/
//call example: required_nb_seen2 (g, S, 0);
int required_nb_seen(cgame g, direction side, int pos){
	if(pos < 0 || pos > COLONNE){
		fprintf(stderr, "Wrong pos in fct required_nb_seen2 for pos : %d\n", pos);
		//exit(EXIT_FAILURE);
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
		fprintf(stderr, "Wrong side given in fct required_nb_seen2 for side :%c\n", side);
		//exit(EXIT_FAILURE);
	}
}


/**
 * @brief indicates the aimed number of a given monster on the board
 * @param game the game that you want to collect the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @return the number of monsters of that type that should be placed on the game.
 **/
//call example: required_nb_monsters2 (g, GHOST));
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
		fprintf(stderr, "Wrong monster type in fct required_nb_monsters2 for type : %c\n", monster);
		//exit(EXIT_FAILURE);		
	}
}

/**
 * @brief Clone the game g_src
 * @param g_src the game to clone
 * @return the clone of g_src
 **/
game copy_game (cgame g_src){
	if(!g_src || ! g_src -> matrice){
		fprintf(stderr, "Error in Function copy_game : Invalid parameters");
		//exit(EXIT_FAILURE);
	}
	game copy_game = new_game();

	copy_game->vampires = g_src->vampires;
	copy_game->ghosts = g_src->ghosts;
	copy_game->zombies = g_src->zombies;

	for (int x = COLONNE-1; x >= 0; x--){
		for(int y = 0; y < LINE; y++){
			copy_game -> matrice[x][y] = g_src -> matrice [x][y];
		}
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
 * @brief get the content of a square in the board
 * @param game the game we consider
 * @param col the column of the square
 * @param line the line of the square
 * @return the content of the square
 **/

int get_content(cgame game, int x, int y){
	if (x < 0 || x >COLONNE){
		fprintf(stderr, "Wrong x parameter on get_content call\n");
	} else if (y < 0 || y > LINE){
		fprintf(stderr, "Wrong y parameter on get_content call\n");
	} else {
		int tick_content = game->matrice[x][y];
		return tick_content;
	}
	return EXIT_FAILURE;
}

/**
 * @brief says how many monsters can be seen on the current game board
 * @param game the game board to look at
 * @param side the side of the board we consider (N, S, W, or E)
 * @param pos the coordinate on that side (from S to N or from W to E)
 * @return the number of monsters that can be seen through all the mirrors from a given side at position x 
 **/
void debug_current_nb_seen(game g,int posX,int posY){
	printf("|      Z:%d V:%d G:%d      |\n",
		required_nb_monsters (g, ZOMBIE), 
		required_nb_monsters (g, VAMPIRE), 
		required_nb_monsters (g, GHOST));
	printf("|                       |\n");

//affichage des nombres cote nord
	printf("|                       |\n");
	int tick_content;

	for(int x = COLONNE-1; x >= 0; x--){
		//Bordures cote gauche && nombres
		printf("|     ", required_nb_seen(g, W, x));
		for(int y = 0; y < LINE ; y++){
			tick_content = get_content(g,y,x);
			if(x==posX && y == posY){
				printf("+");
			}else{
				printf(" ");
			}
			//affichage graphique du contenu des cases
			if(tick_content == EMPTY){
				printf("_ ");
			}
			if(tick_content == MIRROR){
				printf("/ ");
			}
			if(tick_content == ANTIMIRROR){
				printf("\\ ");
			}
			if(tick_content == ZOMBIE){
				printf("Z ");
			}
			if(tick_content == GHOST){
				printf("G ");
			}
			if(tick_content == VAMPIRE){
				printf("V ");
			}
		}
		//Bordures cote droit && nombres
		printf("      |\n",required_nb_seen (g, E, x));
	}

	//nombres en bas
	printf("|                       |\n");
	printf("|                       |\n");
	printf("|         start         |\n\n\n");
}
int current_nb_seen(cgame g, direction side, int pos){
	bool mirror_seen = false;
	bool isEnd = false;
	int posX, posY, sum=0;
	//printf("\n\nCurrent_nb_seen : \n\n");
	//printf("Side : %d, pos: %d\n",side,pos);
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
	/**
	 * On this line of sight, Ghosts are only visible when reflected in
	 * at least one mirror, vampires are visible unless they are reflected in a
	 * mirror, while Zombies are always visible.
	 **/
	while(!isEnd){
		//printf("x:%d, y:%d, side:%d\n\n",posX, posY, side);
		//printf("Side:%d\n",side);
		//printf("posX:%d, posY:%d\n",posX,posY);
		//sleep(1);
		if (posX ==-1 || posX == 4 || posY==-1 ||posY==4){
			isEnd = true;
			return sum;
		}
		if(side == N){
			if(posY<=0){
				isEnd = true;
				return sum;
			}
			posY--;
			if(g->matrice[posX][posY] == MIRROR){
				mirror_seen=true;
				side = W;
			}else if(g->matrice[posX][posY] == ANTIMIRROR){
				mirror_seen=true;
				side = W;
			}else if(g->matrice[posX][posY] == ZOMBIE){
				sum+=1;
			}else if(g->matrice[posX][posY] == GHOST && mirror_seen){
				sum+=1;
			}else if(g->matrice[posX][posY] == VAMPIRE && !mirror_seen){
				sum+=1;
			}

		}
		else if(side == S){
			if(posY>=LINE-1){
				isEnd = true;
				return sum;
			}
			posY++;
			if(g->matrice[posX][posY] == MIRROR){
				mirror_seen=true;
				side = W;
			}else if(g->matrice[posX][posY] == ANTIMIRROR){
				mirror_seen=true;
				side = E;
			}else if(g->matrice[posX][posY] == ZOMBIE){
				sum+=1;
			}else if(g->matrice[posX][posY] == GHOST && mirror_seen){
				sum+=1;
			}else if(g->matrice[posX][posY] == VAMPIRE && !mirror_seen){
				sum+=1;
			}

		}
		else if(side == E){
			if(posX<=0){
				isEnd = true;
				return sum;
			}
			posX--;
			if(g->matrice[posX][posY] == MIRROR){
				mirror_seen=true;
				side = N;
			}else if(g->matrice[posX][posY] == ANTIMIRROR){
				mirror_seen=true;
				side = S;
			}else if(g->matrice[posX][posY] == ZOMBIE){
				sum+=1;
			}else if(g->matrice[posX][posY] == GHOST && mirror_seen){
				sum+=1;
			}else if(g->matrice[posX][posY] == VAMPIRE && !mirror_seen){
				sum+=1;
			}

		}
		else if(side == W){
			if(posX>=COLONNE-1){
				isEnd = true;
				return sum;
			}
			posX++;

			if(g->matrice[posX][posY] == MIRROR){
				mirror_seen=true;
				side = N;
			}else if(g->matrice[posX][posY] == ANTIMIRROR){
				mirror_seen=true;
				side = S;
			}else if(g->matrice[posX][posY] == ZOMBIE){
				sum+=1;
			}else if(g->matrice[posX][posY] == GHOST && mirror_seen){
				sum+=1;
			}else if(g->matrice[posX][posY] == VAMPIRE && !mirror_seen){
				sum+=1;
			}
		}

		//debug_current_nb_seen(g,posX,posY);
	}
	return 0;

}
/**
 * @brief counts the current number of monsters of a given type
 * @param game the game board
 * @param monster the type of monster
 * @return the total number of monsters of the given type on the board.
 **/

int current_nb_monsters(cgame game, content monster){	
	int sum = 0, tick_content=EMPTY;

	for(int x = 0; x < COLONNE; x++){
		for(int y = 0; y < LINE ; y++){
			tick_content = game->matrice[x][y];

			if(tick_content == monster){
				sum = sum+1;
			}
		}
	}
	//printf("SOMME = %d\n",sum );
	//printf("\nSUM:%d\n", sum);
	return sum;
}



/**

Sarah :
	restart_game
	add_monster
	current_nb_seen
	current_nb_monsters

**/


/**
 * @brief Restart a game by cleaning monsters from the board.
 **/

void restart_game(game g){
	game tmp = new_game();
	int tick_content;
	for(int x = COLONNE-1; x >= 0; x--){
		for(int y = 0; y < LINE ; y++){
			tick_content = g->matrice[x][y];
			if(tick_content == ZOMBIE){
				g->matrice[y][x] = EMPTY;
			}
			if(tick_content == GHOST){
				g->matrice[y][x] = EMPTY;
			}
			if(tick_content == VAMPIRE){
				g->matrice[y][x] = EMPTY;
			}
		}
	}
}

/**
 * @brief Test if the game is over (that is the grid is filled according to the requirements).
 * @return true if all the constraints are satisfied
 **/
/**
 * @brief The structure pointer that stores the game
 **/
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
 * @brief adds a monster on the game board.
 * Can also be used to remove any monster by adding EMPTY. 
 * This function does not have effect on mirrors so it can be used safely in the course of the game.
 * @param game the game board where to add the monster
 * @param monster the type of monster to add
 * @param col the column where to insert the monster
 * @param line and the line where to insert the monster
 * @return false if the monster was not placed since the square was occupied by a mirror.
 **/

bool add_monster(game g, content monster, int x, int y){
	if(g->matrice[x][y] == MIRROR || g->matrice[x][y] == ANTIMIRROR){
		return false;
	} else if(x >COLONNE || x < 0 || y < 0 || y > LINE){	
		return false;
	} else {
		switch(monster){
			case ZOMBIE:
				g->matrice[x][y] = ZOMBIE;
				return true;	

			case GHOST:
				g->matrice[x][y] = GHOST;
				return true;	

			case VAMPIRE:
				g->matrice[x][y] = VAMPIRE;
				return true;	

			case EMPTY:
				g->matrice[x][y] = EMPTY;
				return true;

			default:
				return false;
		}
	}
	return false;
}

/*
int main(){
	game g = new_game();
	return 1;
}
*/