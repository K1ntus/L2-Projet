#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //access() fun + chdir
#include <stdbool.h>
#include <math.h>

#include "../header/game_io.h"
#include "../header/game.h"

#define INIT_WIDTH_REQ_MSTRS 100
#define INIT_HEIGHT 100

#define FONT "../ressources/Arial.ttf"
#define FONTSIZE 36


typedef struct required_nb_seen{
  SDL_Texture * west;
  SDL_Texture * east;
  SDL_Texture * south;
  SDL_Texture * north;
} * s_required_nb_seen;

typedef struct monster_type{
  SDL_Texture * zombie;
  SDL_Texture * ghost;
  SDL_Texture * spirit;
  SDL_Texture * vampire;
  SDL_Texture * empty;
} * s_monster_type;

typedef struct mirror_type{
  SDL_Texture * mirror;
  SDL_Texture * antimirror;
  SDL_Texture * vmirror;
  SDL_Texture * hmirror;
} * s_mirror_type;

typedef struct {
  int x;
  int y;
} s_top_corner;

typedef struct{
  int x;
  int y;
} s_cell_selected;

typedef struct{
  int width;
  int height;
} s_cell_size;

struct Env_t {
	game game;

  SDL_Texture * background;

  s_mirror_type mirror_type;
  s_monster_type monster_type;

  SDL_Texture * text;

  s_cell_size cell_size;
  s_top_corner top_corner;
  content monster_selected;	//Save the last pos when we
	s_cell_selected cell_selected;	//Save the cell pointed by a position with the mouse, use convert_sdl_input_to_position(pos_src,x,y) on game_sdl.c
};


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


SDL_Surface * sdl_text_from_string_labels(direction d, int pos, Env * env, char * str){
  SDL_Color color = { 0, 255, 0, 255 };//Red color in RBG
  if(required_nb_seen(env->game, d, pos) != current_nb_seen(env->game,d,pos)){
	  color.r = 255; //red color
    color.g = 0;
  }

	TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
	if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
		TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

	SDL_Surface * surf = TTF_RenderText_Blended(font, str, color); // blended rendering for ultra nice text
	TTF_CloseFont(font);
	return surf;
}

SDL_Surface * sdl_text_from_string_required_nb_monsters(Env * env, char * str){
	SDL_Color color = { 0, 0, 0, 255 };//Black color in RBG

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

char convert_int_to_content(int mstr){
	switch(mstr){
		case 0:	return VAMPIRE; break;
		case 1:	return ZOMBIE; break;
		case 2:	return GHOST; break;
		case 3:	return SPIRIT; break;
		case 4:	return EMPTY; break;
		default:	return EMPTY; break;
	}
	return MIRROR;//Error case ?
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

void add_monster_sdl(char mstr, Env* env){
  add_monster(env->game, convert_char_to_content(mstr), env->cell_selected.x,env->cell_selected.y);
}

bool toggle_fullscreen(SDL_Window* window,unsigned int flags){

	return true;
}


void get_which_cells_is_selected(int posX, int posY, Env* env){
  int topCorner_x=env->top_corner.x;
  int topCorner_y=env->top_corner.y;
  int cell_width=env->cell_size.width;
  int cell_height=env->cell_size.height;
  int valX=(posX-topCorner_x)/cell_width;
  int valY=game_height(env->game)-(posY-topCorner_y)/cell_height -1;

  if(valX >=0 && valX < game_width(env->game))
    env->cell_selected.x = valX;
  else
    env->cell_selected.x = 0;

  if(valY >=0 && valY< game_width(env->game))
    env->cell_selected.y = valY;
  else
    env->cell_selected.y = 0;

  printf("DEBUG: pos selected is: (%d;%d)\n", env->cell_selected.x,env->cell_selected.y);

}

void place_assets(int x, int y, content mstr, SDL_Window* window, SDL_Renderer* ren, Env * env, int cell_width, int cell_height){
  SDL_Rect rect;

	switch(mstr){
		case ZOMBIE:
			SDL_QueryTexture(env->monster_type->zombie, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->monster_type->zombie, NULL, &rect);
			return;
			break;
		case VAMPIRE:
			SDL_QueryTexture(env->monster_type->vampire, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->monster_type->vampire, NULL, &rect);
			return;
			break;
		case GHOST:
			SDL_QueryTexture(env->monster_type->ghost, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->monster_type->ghost, NULL, &rect);
			return;
			break;
		case SPIRIT:
			SDL_QueryTexture(env->monster_type->spirit, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->monster_type->spirit, NULL, &rect);
			return;
			break;


		case MIRROR:
			SDL_QueryTexture(env->mirror_type->mirror, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->mirror_type->mirror, NULL, &rect);
			return;
			break;
		case ANTIMIRROR:
			SDL_QueryTexture(env->mirror_type->antimirror, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->mirror_type->antimirror, NULL, &rect);
			return;
			break;
		case HMIRROR:
			SDL_QueryTexture(env->mirror_type->hmirror, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->mirror_type->hmirror, NULL, &rect);
			return;
			break;
		case VMIRROR:
			SDL_QueryTexture(env->mirror_type->vmirror, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
			SDL_RenderCopy(ren, env->mirror_type->vmirror, NULL, &rect);
			return;
			break;

		default:
			SDL_QueryTexture(env->monster_type->empty, NULL, NULL, &rect.w, &rect.h);
			rect.x = x+1/2*rect.w; rect.y = y+1/2*rect.h;
	    SDL_RenderCopy(ren, env->monster_type->empty, NULL, &rect);
			return;
			break;
	}

}


void display_monsters_on_board(int topCorner_x, int topCorner_y, SDL_Window* window, SDL_Renderer* ren, Env * env, int cell_width, int cell_height){
  	for( int y = game_height(env->game)-1; y >= 0; y--){
  		for( int x = 0; x < game_width(env->game); x++){
        place_assets(topCorner_x+cell_width*x,topCorner_y+cell_height*y,get_content(env->game,x,game_height(env->game)-y-1),window,ren,env, cell_width,cell_height);

    }
  }

}


void display_on_win(SDL_Window* window, SDL_Renderer* ren, Env * env){
  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /* init text texture 0 Arial font */
  SDL_Color color = { 255, 255, 0, 255 }; /* blue color in RGBA */  //color.r, color.g, color.b
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "Congratulations !", color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);


  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = h/2 - rect.h/2;
  SDL_RenderCopy(ren, env->text, NULL, &rect);
}
