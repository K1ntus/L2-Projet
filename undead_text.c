<<<<<<< HEAD
//Gère uniquement l'affichage initial pour le moment

/*
*
*   https://hastebin.com/ocofidikom.cpp
*
*/


//Gère uniquement l'affichage initial pour le moment


=======
>>>>>>> v1.0 Première version du jeu
/*
- un fichier undead_text.c qui maintenant permet de jouer à undead. 
L'instance qui sera chargée sera exactement celle contenue comme exemple dans game.h.
Le fonctionnement du jeu doit être le suivant :

tant que la solution n'est pas trouvée :
   afficher la grille
   lire un coup sur l'entrée standard : (le format est le suivant : <x> <y> <G|V|Z>\n )
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
<<<<<<< HEAD

*/

//#include <unistd.h> //pour le reset (debug)
=======
*/

>>>>>>> v1.0 Première version du jeu

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

#define COLONNE 4
#define LINE 4
<<<<<<< HEAD
#define clear() printf("\033[H\033[J")
=======

#define couleur(param) printf("\033[%sm",param)
#define clear() printf("\033[H\033[y")
>>>>>>> v1.0 Première version du jeu

int nbVampire = 2;
int nbGhost = 2;
int nbZombie = 5;

<<<<<<< HEAD
/*
* Not used
*
* Nettoyer la memoire tampon (l'entree du user)
*/

void bufferCleaner(void){//
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void generate(game g){
  	/* Fonctions dont on a besoin :
  	add_mirror (game game, int dir, int col, int line)
	set_required_nb_monsters (game game, content monster, int value)  --> 
	set_required_nb_seen (game game, direction side, int pos, int value)
	required_nb_seen (cgame game, direction side, int pos)
  	*/

  	set_required_nb_monsters (g, ZOMBIE,  nbZombie);
  	set_required_nb_monsters (g, GHOST,  nbGhost);
  	set_required_nb_monsters (g, VAMPIRE,  nbVampire);

	add_mirror(g,1,0,0);//antimirror
	add_mirror(g,1,1,0);
	add_mirror(g,1,3,0);
	add_mirror(g,1,2,2);
	add_mirror(g,1,3,3);

	add_mirror(g,0,0,3);//Mirror
	add_mirror(g,0,2,3);
=======

void generate(game g){

	set_required_nb_monsters (g, ZOMBIE,  nbZombie);
	set_required_nb_monsters (g, GHOST,  nbGhost);
	set_required_nb_monsters (g, VAMPIRE,  nbVampire);

//AntiMirror
	add_mirror(g,1,0,0);
	add_mirror(g,1,0,2);
	add_mirror(g,1,0,3);
	add_mirror(g,1,3,0);
	add_mirror(g,1,2,1);

//Mirror
	add_mirror(g,0,3,3);
	add_mirror(g,0,3,1);

>>>>>>> v1.0 Première version du jeu

	set_required_nb_seen (g, N, 0, 0);
	set_required_nb_seen (g, N, 1, 3);
	set_required_nb_seen (g, N, 2, 3);
	set_required_nb_seen (g, N, 3, 0);

<<<<<<< HEAD
	set_required_nb_seen (g, S, 0, 0);
	set_required_nb_seen (g, S, 1, 3);
	set_required_nb_seen (g, S, 2, 2);
	set_required_nb_seen (g, S, 3, 3);

	set_required_nb_seen (g, W, 0, 3);
	set_required_nb_seen (g, W, 1, 3);
	set_required_nb_seen (g, W, 2, 2);
	set_required_nb_seen (g, W, 3, 0);

	set_required_nb_seen (g, E, 0, 2);
	set_required_nb_seen (g, E, 1, 3);
	set_required_nb_seen (g, E, 2, 0);
	set_required_nb_seen (g, E, 3, 0);
=======
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

>>>>>>> v1.0 Première version du jeu

}

void display(game g){
<<<<<<< HEAD
	printf("\n|   Z:%d V:%d G:%d   |\n",required_nb_monsters (g, ZOMBIE), required_nb_monsters (g, VAMPIRE), required_nb_monsters (g, GHOST));
	printf("|                 |\n");
	printf("|     %d %d %d %d     |\n",required_nb_seen (g, N, 0),required_nb_seen (g, N, 1),required_nb_seen (g, N, 2),required_nb_seen (g, N, 3));
	printf("|                 |\n");
	for(int i = 0; i < COLONNE; i++){
		printf("|  %d  ",required_nb_seen (g, W, i));
		for(int j = 0; j < LINE; j++){
			enum content_e tick_content = get_content(g,i,j);
=======
//affichage du nombre de mobs a placer
	printf("|   Z:%d V:%d G:%d   |\n",
		required_nb_monsters (g, ZOMBIE), 
		required_nb_monsters (g, VAMPIRE), 
		required_nb_monsters (g, GHOST));
	printf("|                 |\n");

//affichage des nombres cote nord
	printf("|     %d %d %d %d     |\n", required_nb_seen(g, N, 0), required_nb_seen(g, N, 1), required_nb_seen(g, N, 2), required_nb_seen (g, N, 3));
	printf("|                 |\n");
	int tick_content;

	for(int x = COLONNE-1; x >= 0; x--){
		//Bordures cote gauche && nombres
		printf("|  %d  ", required_nb_seen(g, W, x));
		for(int y = 0; y < LINE ; y++){
			tick_content = get_content(g,y,x);

			//affichage graphique du contenu des cases
>>>>>>> v1.0 Première version du jeu
			if(tick_content == EMPTY){
				printf("  ");
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
<<<<<<< HEAD
		printf(" %d  |\n",required_nb_seen (g, W, i));
	}
=======
		//Bordures cote droit && nombres
		printf(" %d  |\n",required_nb_seen (g, E, x));
	}

	//nombres en bas
>>>>>>> v1.0 Première version du jeu
	printf("|                 |\n");
	printf("|     %d %d %d %d     |\n",required_nb_seen (g, S, 0),required_nb_seen (g, S, 1),required_nb_seen (g, S, 2),required_nb_seen (g, S, 3));
	printf("|                 |\n");
	printf("|      start      |\n");
}


void entry(game g, int x, int y, char mstr){
<<<<<<< HEAD
/*	int x,y;
	char mstr;
	printf("\n \nLe format est le suivant : <x> <y> <G|V|Z>,\navec <x> et <y> allant de 0 à 3.\n\n   Commande : ");
	int r = scanf ("%d %d ", &x, &y);
	r += scanf("%c\n", &mstr);
	printf("%d",r);
	if(r ==EOF){ exit(EXIT_FAILURE); }
*/
	
//Try de definir des constantes au lieu de ces boucles -> meilleure perf

	if (x >= 0 && x <= 3 && y >= 0 && y <= 3 ){ //Verification de la position
		if(get_content (g, y, x) == EMPTY){

//add_monster(game game, content monster, int col, int line);
=======
	if (x >= 0 && x <= 3 && y >= 0 && y <= 3 ){ //Verification de la position

			//Cas ou l'on veut supprimer un monstre
			if(mstr == 'E' || mstr == 'e'){//Si l'utilisateur a entré E (ou e) ie Empty
				int mstr = get_content(g, x, y);
				if(mstr == VAMPIRE){
					nbVampire++;
	  				set_required_nb_monsters (g, VAMPIRE,  nbVampire);
				}
				if(mstr == ZOMBIE){
					nbZombie++;
	  				set_required_nb_monsters (g, ZOMBIE,  nbZombie);
				}
				if(mstr == GHOST){
					nbGhost++;
	  				set_required_nb_monsters (g, GHOST,  nbGhost);
				}
					add_monster(g, EMPTY, x, y);
					printf("\n");
			}

		//Cas ou l'on veut placer un monstre
		if(get_content (g, x, y) == EMPTY){
>>>>>>> v1.0 Première version du jeu
			if(mstr == 'V' || mstr == 'v'){//Si l'utilisateur a entré V (ou v)
				if(nbVampire == 0){//S'il ne reste plus de vampires a placer
					printf("Vous avez déjà placé tous les Vampires\n");
				}else{
					nbVampire--;
					mstr = VAMPIRE;
<<<<<<< HEAD
	  				set_required_nb_monsters (g, VAMPIRE,  nbVampire);
					add_monster(g, mstr, y, x);
=======
	  				//set_required_nb_monsters (g, VAMPIRE,  nbVampire);
					add_monster(g, mstr, x, y);
>>>>>>> v1.0 Première version du jeu
					printf("\n");
  				}
			}

<<<<<<< HEAD
			if(mstr == 'G' || mstr == 'g'){//voir plus haut
=======
			if(mstr == 'G' || mstr == 'g'){//Si l'utilisateur a entré G (ou g)
>>>>>>> v1.0 Première version du jeu
				if(nbGhost == 0){
					printf("\nVous avez déjà placé tous les Fantômes\n");
				}else{
					nbGhost--;
					mstr = GHOST;
<<<<<<< HEAD
	  				set_required_nb_monsters (g, GHOST,  nbGhost);
					add_monster(g, mstr, y, x);
=======
	  				//set_required_nb_monsters (g, GHOST,  nbGhost);
					add_monster(g, mstr, x, y);
>>>>>>> v1.0 Première version du jeu
					printf("\n");
  				}
			}

<<<<<<< HEAD
			if(mstr == 'Z' || mstr == 'z'){//voir plus haut
=======
			if(mstr == 'Z' || mstr == 'z'){//Si l'utilisateur a entré Z (ou z)
>>>>>>> v1.0 Première version du jeu
				if(nbZombie == 0){
					printf("Vous avez déjà placé tous les Zombies\n");
				}else{
					nbZombie--;
					mstr = ZOMBIE;
<<<<<<< HEAD
	  				set_required_nb_monsters (g, ZOMBIE,  nbZombie);
					add_monster(g, mstr, y, x);
=======
	  				//set_required_nb_monsters (g, ZOMBIE,  nbZombie);
					add_monster(g, mstr, x, y);
>>>>>>> v1.0 Première version du jeu
					printf("\n");
  				}
			}
		} else {			
<<<<<<< HEAD
			printf("Case non vide, veuillez réessayer\n");
		}
	}	
}



void usage (char * cmd){ 
	fprintf(stderr, "Usage : %s\n", cmd);
	exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){
	//system("reset"); //clear la console pour plus de propreté
	
	if (argc != 1){
		usage(argv[0]);
	}
	
  	game g = new_game();
	generate(g);
	int r;
	int x,y;
	char mstr;
	display(g);
	while(is_game_over != true){
		printf("\n \nLe format est le suivant : <x> <y> <G|V|Z>,\navec <x> et <y> allant de 0 à 3.\n\n   Commande : ");
		r = scanf("%d %d %c",&x,&y,&mstr);
		if(r == 3){
			entry(g, x, y, mstr);
		} else if(r == EOF){
			break;
		} else {
			fprintf(stderr,"Erreur");
		}
		display(g);
	}

  	delete_game(g);
  	return EXIT_SUCCESS;
}
=======
			printf("\n\nCase non vide, veuillez réessayer\n");
		}
	} else {
		printf("\n\nCoordonnées invalides\n");
	}
}


void debug(game g){
	//int 	current_nb_seen (cgame game, direction side, int pos)
	printf("\nINFO: Nombre de monstres visibles NORTH :\n");
	for(unsigned int i = 0; i < 4; i++){
		int tmp = current_nb_seen(g, N, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles SOUTH :\n");
	for(unsigned int i = 0; i < 4; i++){
		int tmp = current_nb_seen(g, S, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles EAST :\n");
	for(unsigned int i = 0; i < 4; i++){
		int tmp = current_nb_seen(g, E, i);
		printf("%d ", tmp);
	}
	printf("\nINFO: Nombre de monstres visibles WEST :\n");
	for(unsigned int i = 0; i < 4; i++){
		int tmp = current_nb_seen(g, W, i);
		printf("%d ", tmp);
	}
}


/*
*
* Nettoyer la memoire tampon (l'entree du user)
*
*/

void bufferCleaner(void){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

bool usage (game g, int r, int x, int y, char mstr){
	if(r == 3){
		entry(g, x, y, mstr);
	} else if(r == EOF){
		return false;
	} else if (r != 3){
		fprintf(stderr,"\n\nNombre de paramètres invalides\n");
		bufferCleaner();
	}
	return true;
}

int main(){
	clear();
	int r, x, y;
	char mstr;
	//Génération du jeu 
  	game g = new_game();
	generate(g);
	display(g);
	
/*
	while(is_game_over(g) != true){
		debug(g); //TEMPORAIRE
*/

	if(is_game_over(g)){
		couleur("44");
		printf("\n\nVOUS AVEZ GAGNE\n\n");
		couleur("0");
	}
//Entrée utilisateur
		printf("\n\nLe format est le suivant : <x> <y> <G|V|Z|E>,\navec <x> et <y> allant de 0 à 3.\n\n		Commande : ");
		r = scanf("%d %d %c",&x,&y,&mstr);
		printf("\n\n");

//Verification de l'entree utilisateur
		if(!usage(g, r, x, y, mstr)){ //qu'en cas d'erreur importante (ie r == EOF)
			break; 
		}

		display(g);
	}
//fin while
	//clear();

	if(is_game_over(g)){
		couleur("44");
		printf("\n\nVOUS AVEZ GAGNE\n\n");
		couleur("0");
	}
  	delete_game(g);
  	return EXIT_SUCCESS;
}

>>>>>>> v1.0 Première version du jeu
