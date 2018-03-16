#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //access() fun + chdir
#include <stdbool.h>
#include <math.h>

#include "../header/game_display.h"
#include "../header/game_io.h"
#include "../header/game.h"
#include "../header/model.h"

#define INIT_WIDTH_REQ_MSTRS 100
#define INIT_HEIGHT 100

#define FONT "../ressources/Arial.ttf"
#define FONTSIZE 36

#ifndef _CONVERT_
char* convert_int_to_string(char*str, int val){
	char * res = (char *) malloc(sizeof(char) * (strlen(str)+val/10) );
	sprintf(res, "%s%d",str,val);
	return res;
}
#endif //	CONVERT

SDL_Surface * sdl_text_from_string(char * str){

	SDL_Color color = { 0, 0, 255, 255 };//Blue color in RBG

	TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
	if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
		TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

	SDL_Surface * surf = TTF_RenderText_Blended(font, str, color); // blended rendering for ultra nice text
	TTF_CloseFont(font);
	return surf;
}

void get_required_nb_monsters(game g, content monster, char* res){
	int val = required_nb_monsters(g, monster);
	convert_int_to_string(res, val);
}

void get_required_nb_seen(game g, unsigned int pos, direction dir, char* res){
	int val = required_nb_seen(g, dir, pos);
	convert_int_to_string(res,val);
}

char convert_content_to_char(content mstr){
	switch(mstr){
		case VAMPIRE:	return 'V'; break;
		case ZOMBIE:	return 'Z'; break;
		case GHOST:	return 'G'; break;
		case SPIRIT:	return 'S'; break;
		case EMPTY:	return 'E'; break;
		default:	return 'E'; break;
	}
	return '0';

}

content convert_char_to_content(char mstr){
	switch(mstr){
		case 'V':	return VAMPIRE; break;
		case 'Z':	return ZOMBIE; break;
		case 'G':	return GHOST; break;
		case 'S':	return SPIRIT; break;
		case 'E':	return EMPTY; break;
		default:	return EMPTY; break;
	}
	return MIRROR;//Error case ?
}


//Position de la souris, ou entrée clavier pour choisir un monstre, je ne sais pas encore
void convert_sdl_input_to_position(unsigned int pos_src, unsigned int * x, unsigned int * y){
	*y = 0;//(pos - [decalage a gauche])/taille d'une cellule
	*x = 0;//(pos - [decalage a gauche])%taille d'une cellule
}

content get_which_mob_is_select(unsigned int pos_src){	//pas sur de la maniere encore
	return EMPTY;
}

void add_monster_sdl(int pos, char mstr){
	unsigned int x,y;
	convert_sdl_input_to_position(pos,&x,&y);
	game g = load_game("autosave");
	add_monster(g, convert_char_to_content(mstr), x, y);

}
