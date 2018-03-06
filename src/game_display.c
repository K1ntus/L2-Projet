#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "../header/game.h"
#include "../header/game_display.h"


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
	for(int x = game_width(g)-1; x >= 0; x--){
		//Left & right side of the board
		printf("|   %d  ", required_nb_seen(g, W, x));
		for(int y = 0; y < game_height(g) ; y++){
			tick_content = get_content(g,x,y);

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
