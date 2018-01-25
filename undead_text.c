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
*/


#include <stdlib.h>
#include <stdio.h>
#include "game_io.h"

#define COLONNE 4
#define LINE 4

#define clear() printf("\033[H\033[y")

int nbVampire = 2;
int nbGhost = 2;
int nbZombie = 5;
int nbSpirit = 5; //dépend de la taille de matrice


void generate(game g){

	set_required_nb_monsters (g, ZOMBIE,  nbZombie);
	set_required_nb_monsters (g, GHOST,  nbGhost);
	set_required_nb_monsters (g, VAMPIRE,  nbVampire);
	set_required_nb_monsters (g, SPIRIT,  nbSpirit);


//AntiMirror
	add_mirror_ext(g,ANTIMIRROR,0,0);
	add_mirror_ext(g,ANTIMIRROR,0,2);
	add_mirror_ext(g,ANTIMIRROR,0,3);
	add_mirror_ext(g,ANTIMIRROR,3,0);
	add_mirror_ext(g,ANTIMIRROR,2,1);
	//va dépendre de la taille de la matrice

//Mirror
	add_mirror_ext(g,MIRROR,3,3);
	add_mirror_ext(g,MIRROR,3,1);
	//va dépendre de la taille de la matrice


	//Tant qu'on sait pas si ça doit etre aléatoire ou non ou change pas
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

void display(game g){
//affichage du nombre de mobs a placer
	printf("|   Z:%d V:%d G:%d S:%d   |\n",
		required_nb_monsters(g, ZOMBIE),
		required_nb_monsters(g, VAMPIRE),
		required_nb_monsters(g, GHOST),
		required_nb_monsters(g, SPIRIT));

	printf("|                     |\n");

//affichage des nombres cote nord
	//affichage 1re ligne
	printf("|     ");
	for(int i=0; i<game_width(g) ; i++){
		printf("%d ",required_nb_seen(g, N, i));
	}
	printf("    |\n");
	//affichage 2eme ligne
	printf("|     ");
	for(int i=0; i<game_width(g) ; i++){
		printf(" ");
	}
	printf("     |\n");

	int tick_content;

	for(int x = game_height(g)-1; x >= 0; x--){
		//Bordures cote gauche && nombres
		printf("|  %d  ", required_nb_seen(g, W, x));
		for(int y = 0; y < game_width(g) ; y++){
			tick_content = get_content(g,y,x);

			//affichage graphique du contenu des cases
			if(tick_content == EMPTY){
				printf("  ");
			}
			if(tick_content == MIRROR){
				printf("/ ");
			}
			if(tick_content == ANTIMIRROR){
				printf("\\ ");
			}
			if(tick_content == VMIRROR){
				printf("| ");
			}
			if(tick_content == HMIRROR){
				printf("_ ");
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
			if(tick_content == SPIRIT){
				printf("S ");
			}
		}
		//Bordures cote droit && nombres
		printf(" %d  |\n",required_nb_seen (g, E, x));
	}

	//nombres en bas

	//affichage ligne vide
	printf("|     ");
	for(int i=0; i<game_width(g) ; i++){
		printf(" ");
	}
	printf("     |\n");
	//affichage 1re ligne
	printf("|     ");
	for(int i=0; i<game_width(g) ; i++){
		printf("%d ",required_nb_seen(g, S, i));
	}
	printf("    |\n");
	//affichage ligne vide
	printf("|     ");
	for(int i=0; i<game_width(g) ; i++){
		printf(" ");
	}
	printf("     |\n");

	//affichage ligne start (a modifier si la taille est inférieure à 3
	printf("|     start");
	int nbr_space = game_width(g) + game_width(g)-1;  // donne la taille en espaces de required nbr seen + leurs espaces
	for(int i=0; i<(nbr_space - 5) ; i++){ //  (5 taille de chaine 'start' )   donne le nombre d'espace à ajouter après start
		printf(" ");
	}
	printf("     |\n");


}


void entry(game g, int x, int y, char mstr){
	if (x >= 0 && x <= game_width(g) && y >= 0 && y <= game_height(g) ){ //Verification de la position

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
				if(mstr == SPIRIT){
					nbSpirit++;
	  				set_required_nb_monsters (g, SPIRIT,  nbSpirit);
				}
				add_monster(g, EMPTY, x, y);
				printf("\n");
			}

		//Cas ou l'on veut placer un monstre
		if(get_content (g, x, y) == EMPTY){
			if(mstr == 'V' || mstr == 'v'){//Si l'utilisateur a entré V (ou v)
				if(nbVampire == 0){//S'il ne reste plus de vampires a placer
					printf("Vous avez déjà placé tous les Vampires\n");
				}else{
					nbVampire--;
					mstr = VAMPIRE;
	  				//set_required_nb_monsters (g, VAMPIRE,  nbVampire);
					add_monster(g, mstr, x, y);
					printf("\n");
  				}
			}

			if(mstr == 'G' || mstr == 'g'){//Si l'utilisateur a entré G (ou g)
				if(nbGhost == 0){
					printf("\nVous avez déjà placé tous les Fantômes\n");
				}else{
					nbGhost--;
					mstr = GHOST;
	  				//set_required_nb_monsters (g, GHOST,  nbGhost);
					add_monster(g, mstr, x, y);
					printf("\n");
  				}
			}

			if(mstr == 'Z' || mstr == 'z'){//Si l'utilisateur a entré Z (ou z)
				if(nbZombie == 0){
					printf("Vous avez déjà placé tous les Zombies\n");
				}else{
					nbZombie--;
					mstr = ZOMBIE;
	  				//set_required_nb_monsters (g, ZOMBIE,  nbZombie);
					add_monster(g, mstr, x, y);
					printf("\n");
  				}
			}

			if(mstr == 'S' || mstr == 's'){//Si l'utilisateur a entré V (ou v)
				if(nbSpirit == 0){//S'il ne reste plus de vampires a placer
					printf("Vous avez déjà placé tous les Spirits\n");
				}else{
					nbSpirit--;
					mstr = SPIRIT;
	  				//set_required_nb_monsters (g, VAMPIRE,  nbVampire);
					add_monster(g, mstr, x, y);
					printf("\n");
  				}
			}

		} else {
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
	int r, x, y;
	char mstr;
	//Génération du jeu
  	game g = new_game_ext(5, 5);
	generate(g);
	display(g);

	while(is_game_over(g) != true){
		if(is_game_over(g)){
			printf("\n\nVOUS AVEZ GAGNE\n\n");
		}
//Entrée utilisateur
		printf("\n\nLe format est le suivant : <x> <y> <G|V|Z|S|E>,\navec <x> et <y> allant de 0 à 3.\n\n		Commande : ");//le 0 à 3 changera selon la taille de la matrice
		r = scanf("%d %d %c",&x,&y,&mstr);
		printf("\n\n");
//Verification de l'entree utilisateur
		if(!usage(g, r, x, y, mstr)){ //qu'en cas d'erreur importante (ie r == EOF)
			break;
		}
		display(g);
		//debug(g);
	}
//fin while
	//clear();

	if(is_game_over(g)){
		printf("\n\nVOUS AVEZ GAGNE\n\n");
	}
  	delete_game(g);
  	return EXIT_SUCCESS;
}
