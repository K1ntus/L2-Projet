#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.c"



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


bool already_max_monsters_placed (game g, content monster){
  if(required_nb_monsters(g, monster) == current_nb_monsters(g,monster)){
    return false;
  }
  return true;
}

void init_matrice2(game g){
	int **res  = (int **)malloc(sizeof(int *) * game_width(g));
	res[0] = (int *)malloc(sizeof(int) * game_height(g) * game_width(g));
	for(int i = 0; i < game_width(g); i++)
	 *res[i] = (**res +  game_height(g) * i);

	//Initialise each cells of the board with enum type EMPTY
	for (int x = 0; x <  game_width(g); x++){
		for (int y = 0; y <  game_height(g); y++){
			res[x][y] = EMPTY;
		}
	}
}










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
		printf("\n\n");
}

/**
	*	0	NORTH
	*	1	SOUTH
	*	2	EAST
	*	3	WEST
**/
int ** init_array(game g){
 int **res  = (int **)malloc(sizeof(int *) * NB_DIR);
 int *north = (int *)malloc(sizeof(int) * game_height(g));
 int *south = (int *)malloc(sizeof(int) * game_height(g));
 int *east = (int *)malloc(sizeof(int) * game_width(g));
 int *west = (int *)malloc(sizeof(int) * game_width(g));

 res[0] = north;
 res[1] = south;
 res[2] = east;
 res[3] = west;
 return res;
}


int ** current_nb_seen_array(game g, int ** array){
	return array;
}

void which_side_see_this_cell(game g, int pos, int ** array){




}


bool is_valid(game g, int pos, int ** array){
  display(g);
  int max_size = game_width(g)*game_height(g);
  if (pos < 0 || pos > max_size){
    return false;
  }

	printf("pos=%d\n",pos);
  int x = pos/game_width(g);
  int y = pos%game_width(g);
	printf("posX=%d; posY=%d\n",x,y);
  if(get_content(g,x,y) != EMPTY){
    fprintf(stderr,"INFO: not an empty cell for the solver\n");
	}
    if(current_nb_monsters(g,ZOMBIE) < required_nb_monsters(g,ZOMBIE)){
      add_monster(g, ZOMBIE,x,y);//Changer en fct du nb de monstre vu
			printf("Added a zombie\n");
    }else if (current_nb_monsters(g,VAMPIRE) < required_nb_monsters(g,VAMPIRE)){
      fprintf(stderr, "INFO: already max number of zombie placed\n");
      add_monster(g,VAMPIRE,x,y);
    }else if (current_nb_monsters(g,GHOST) < required_nb_monsters(g,GHOST)){
      fprintf(stderr, "INFO: already max number of vampire placed\n");
      add_monster(g,GHOST,x,y);
    }else if (current_nb_monsters(g,SPIRIT) < required_nb_monsters(g,SPIRIT)){
      fprintf(stderr, "INFO: already max number of ghost placed\n");
      add_monster(g,SPIRIT,x,y);
    }else{
      fprintf(stderr, "INFO: already max number of spirit placed\n");
		}

	display(g);
	return is_valid(g, pos+1, array);

  for(unsigned int i = 0; i < max_size; i++){
    int x = pos/game_width(g);
    int y = pos%game_width(g);
    if(get_content(g,x,y) == EMPTY){
      printf("on add un truc");
      is_valid(g, pos, array);
    }
  }
  return true;

}


void usage (void){
		fprintf(stderr,"\n\nNombre de parametres invalides\n");
		fprintf(stderr,"Usage: undead_solve FIND_ONE|NB_SOL|FIND_ALL <nom_fichier_pb> <prefix_fichier_sol>\n");
		exit(EXIT_FAILURE);
}


int main (void /*int argc, char *argv[]*/){
	/*
	if (argc != 4){
		usage();
	}

	switch(argv[1]){
		case FIND_ONE:
			//TODO
			break;
		case NB_SOL:
			//TODO
			break;
		case FIND_ALL:
			//TODO
			break;
		}
		default:
			break;
	}*/
  game g = new_game_ext(4,4);
	int nbMonsters[] = {2,2,5,0};
	int ** array = init_array(g);
  generate(g, nbMonsters);
  is_valid(g,0, array);
}
