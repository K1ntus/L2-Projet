/*
- un fichier undead_text.c qui maintenant permet de jouer Ãƒ  undead.
L'instance qui sera chargÃƒÂ©e sera exactement celle contenue comme exemple dans game.h.
Le fonctionnement du jeu doit ÃƒÂªtre le suivant :

tant que la solution n'est pas trouvÃƒÂ©e :
   afficher la grille
   lire un coup sur l'entrÃƒÂ©e standard : (le format est le suivant : <x> <y> <G|V|Z>\n )
   si le coup est valide alors
	   jouer ce coup
   sinon
	   ignorer ce coup
fin tant que
afficher la grille

Pour l'affichage, vous devez respecter la convention suivante :

 @verbatim
 |   Z:5 V:2 G:2   |   Z:5 V:2 G:2   |
 |                 |                 |
 |     0 3 3 0     |     0 3 3 0     |
 |                 |                 |
 |  3  \     /  2  |  3  \ V V /  2  |
 |  3  \        3  |  3  \ Z Z Z  3  |
 |  2      \ /  0  |  2  Z G \ /  0  |
 |  0  \     \  0  |  0  \ Z G \  0  |
 |                 |                 |
 |     0 3 2 3     |     0 3 2 3     |
 |                 |                 |
 |     start       |     solution    |
 @endverbatim
*/


#include <stdlib.h>
#include <stdio.h>
#include "game_io.h"
#include "game.h"

#define clear() printf("\033[H\033[y")

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

// Handle the entry of the user
void entry(game g, int x, int y, char mstr, int * nbMonsters, char choice){
	if (x >= 0 && x <= game_width(g) && y >= 0 && y <= game_height(g) ){ //Check the validity of the position
		//If we want to remove a monster
		if(mstr == 'E' || mstr == 'e'){//If the user have enter 'E' (or 'e') for Empty
			int mstr = get_content(g, x, y);
			if(mstr == VAMPIRE){
				nbMonsters[0]++;
  				set_required_nb_monsters (g, VAMPIRE,  nbMonsters[0]);
			}
			if(mstr == ZOMBIE){
				nbMonsters[2]++;
  				set_required_nb_monsters (g, ZOMBIE,  nbMonsters[2]);
			}
			if(mstr == GHOST){
				nbMonsters[1]++;
  				set_required_nb_monsters (g, GHOST,  nbMonsters[1]);
			}
			if(mstr == SPIRIT){
				nbMonsters[3]++;
  				set_required_nb_monsters (g, SPIRIT,  nbMonsters[3]);
			}
			add_monster(g, EMPTY, x, y);
			printf("\n");
		}

		//Event if we want to place a monster
		if(get_content (g, x, y) == EMPTY){
			if(mstr == 'V' || mstr == 'v'){   //If the user wrote 'V' (or 'v') for a vampire
				if(nbMonsters[0] == 0){        //If there's not enought Vampire to place
					printf("Vous avez dÃ©jÃ   placÃ© tous les Vampires\n");
				}else{
					nbMonsters[0]--;
					mstr = VAMPIRE;
					add_monster(g, mstr, x, y);
					printf("\n");
					}
			}

			if(mstr == 'G' || mstr == 'g'){//If the user wrote 'G' (or 'g') for a ghost
				if(nbMonsters[1] == 0){
					printf("\nVous avez dÃ©jÃ  placÃ© tous les FantÃ´mes\n");
				}else{
					nbMonsters[1]--;
					mstr = GHOST;
					add_monster(g, mstr, x, y);
					printf("\n");
					}
			}
			if(mstr == 'Z' || mstr == 'z'){//If the user wrote 'Z' (or 'z') for a zombie
				if(nbMonsters[2] == 0){
					printf("Vous avez dÃ©jÃ  placÃ© tous les Zombies\n");
				}else{
					nbMonsters[2]--;
					mstr = ZOMBIE;
					add_monster(g, mstr, x, y);
					printf("\n");
					}
			}
			if(mstr == 'S' || mstr == 's'){//If the user wrote 'G' (or 'g') for a ghost
				if(nbMonsters[3] == 0){//If there s not enought spirit to place
					printf("Vous avez dÃ©jÃ  placÃ© tous les Spirits\n");
				}else{
					nbMonsters[3]--;
					mstr = SPIRIT;
					add_monster(g, mstr, x, y);
					printf("\n");
				}
			}

		}else{
				printf("\n\nCase non vide, veuillez rÃ©essayer\n");
			}
	}else{
		printf("\n\nCoordonnÃ©es invalides\n");
	}
	if(choice == 'y' || choice == 'Y'){
		printf("Vous avez sauvegardé la partie");
		save_game(g,"autosave");
	}
}


void debug(game g){
	printf("\nINFO: Nombre de monstres visibles NORTH :\n");
	for(unsigned int i = 0; i < game_width(g); i++){
		int tmp = current_nb_seen(g, N, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles SOUTH :\n");
	for(unsigned int i = 0; i < game_width(g); i++){
		int tmp = current_nb_seen(g, S, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles EAST :\n");
	for(unsigned int i = 0; i < game_height(g); i++){
		int tmp = current_nb_seen(g, E, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles WEST :\n");
	for(unsigned int i = 0; i < game_height(g); i++){
		int tmp = current_nb_seen(g, W, i);
		printf("%d ", tmp);
	}
}


/*
*
* Clear the text memory (the user's entry)
*
*/

void bufferCleaner(void){
  int c = 0;
  while (c != '\n' && c != EOF)
  {
      c = getchar();
  }
}

bool usage (game g, int r, int x, int y, char mstr, int * nbMonsters, char choice){
	if(r == 4){
		entry(g, x, y, mstr, nbMonsters, choice);
	} else if(r == EOF){
		return false;
	} else if (r != 3){
		fprintf(stderr,"\n\nNombre de paramÃ¨tres invalides\n");
		bufferCleaner();
	}
	return true;
}

void usage_loading_save(void){

}


int main(int argc, char *argv[]){
	int r, x, y;
	char mstr, choice;

	//Game generation
  	game g = new_game_ext(4, 4);
	//nbMonsters[0] => Vampire; nbMonsters[1] => Ghost; nbMonsters[2] => Zombie; nbMonsters[3] => Spirits
	int nbMonsters[] = {2,2,5,0};

	if(argc == 3){
		printf("Loading %s file\n",argv[1]);
		g = load_game(argv[1]);
	} else {
		printf("Generating random board, unable to load any save file\n");

		generate(g, nbMonsters);
	}



	display(g);

	while(is_game_over(g) != true){
	//User Entry
		printf("\n\nLe format est le suivant : <x> <y> <G|V|Z|S|E>,\navec <x> et <y> des entiers naturels valident.\n\n		Commande : ");
		r = scanf("%d %d %c",&x,&y,&mstr);
		printf("Do you want to save the game ?\n");
		choice = scanf("%c",&choice);
		printf("\n\n");
	//Check the validity of user Entry
		if(!usage(g, r, x, y, mstr, nbMonsters, choice)){ //If an important error occurs, (ie. r = EOF)
			break;
		}

		display(g);
		//debug(g);
	}
	//end while

	if(is_game_over(g)){
		printf("\n\nVOUS AVEZ GAGNE\n\n");
	}
  	delete_game(g);
  	return EXIT_SUCCESS;
}
