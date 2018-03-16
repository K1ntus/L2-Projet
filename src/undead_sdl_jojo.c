// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "model.h"

#include "./game_sdl.c"
#include "../header/game.h"
/* **************************************************************** */
#define WIDTH 4
#define HEIGHT 4

#define WIDTH_SHIFT 100
#define HEIGHT_SHIFT 250

#define NB_MONSTERS 4

#define BACKGROUND "../ressources/background.png"

#define EMPTY "../ressources/empty.png"

#define MIRROR "../ressources/mirror.png"
#define ANTIMIRROR "../ressources/antimirror.png"
#define VMIRROR "../ressources/vmirror.png"
#define HMIRROR "../ressources/hmirror.png"

#define VAMPIRE "../ressources/vampire.png"
#define GHOST "../ressources/ghost.png"
#define SPIRIT "../ressources/spirit.png"
#define ZOMBIE "../ressources/zombie.png"

#define QUIT "../ressources/exit.png"
#define OPTIONS "../ressources/settings.png"
#define SOLVE "../ressources/solver.png"

/* **************************************************************** */

/* PUT YOUR VARIABLES HERE */
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

struct Env_t {
	game game;

  SDL_Texture * background;

  s_mirror_type mirror_type;
  s_monster_type monster_type;

  SDL_Texture * text;

  content monster_selected;	//Save the last pos when we
	int cell_selected;	//Save the cell pointed by a position with the mouse, use convert_sdl_input_to_position(pos_src,x,y) on game_sdl.c
};

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){
  Env * env = malloc(sizeof(struct Env_t));
  env-> mirror_type = malloc(sizeof(struct mirror_type));
  env-> monster_type = malloc(sizeof(struct monster_type));
  env-> game = new_game_ext(4,4);

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init empty cell texture from PNG image */
  env->monster_type->empty = IMG_LoadTexture(ren, EMPTY);
  if(!env->monster_type->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY);

  /* init mirrors texture from PNG image */
  env->mirror_type->mirror = IMG_LoadTexture(ren, MIRROR);
  if(!env->mirror_type->mirror) ERROR("IMG_LoadTexture: %s\n", MIRROR);

  /* init antimirrors texture from PNG image */
  env->mirror_type->antimirror = IMG_LoadTexture(ren, ANTIMIRROR);
  if(!env->mirror_type->antimirror) ERROR("IMG_LoadTexture: %s\n", ANTIMIRROR);

  /* init vmirrors texture from PNG image */
  env->mirror_type->vmirror = IMG_LoadTexture(ren, VMIRROR);
  if(!env->mirror_type->vmirror) ERROR("IMG_LoadTexture: %s\n", VMIRROR);

  /* init hmirrors texture from PNG image */
  env->mirror_type->hmirror = IMG_LoadTexture(ren, HMIRROR);
  if(!env->mirror_type->hmirror) ERROR("IMG_LoadTexture: %s\n", HMIRROR);

  /* init zombie texture from PNG image */
  env->monster_type->zombie = IMG_LoadTexture(ren, ZOMBIE);
  if(!env->monster_type->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIE);

  /* init spirit texture from PNG image */
  env->monster_type->spirit = IMG_LoadTexture(ren, SPIRIT);
  if(!env->monster_type->spirit) ERROR("IMG_LoadTexture: %s\n", SPIRIT);

  /* init ghost texture from PNG image */
  env->monster_type->ghost = IMG_LoadTexture(ren, GHOST);
  if(!env->monster_type->ghost) ERROR("IMG_LoadTexture: %s\n", GHOST);

  /* init vampire texture from PNG image */
  env->monster_type->vampire = IMG_LoadTexture(ren, VAMPIRE);
  if(!env->monster_type->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRE);


  /* init text texture using Arial font */
    //If required_nb_monster-current_nb_monster == 0 couleur = rouge sinon couleur = noir

/*
  SDL_Color color = { 0, 0, 255, 255 };//Blue color in RBG

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

  SDL_Surface * surf = TTF_RenderText_Blended(font, "0", color); // blended rendering for ultra nice text
  env->required_nb_seen->west = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);

  TTF_CloseFont(font);
*/


  return env;
}

/* **************************************************************** */

void render(SDL_Window* window, SDL_Renderer* ren, Env * env){
  SDL_Rect rect;

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */


  /* get current window size */
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	//int y_upset = windowHeight/10;
	//int x_upset = windowHeight/5;
	int last_img_width;

  /* required nb monster display */
  SDL_QueryTexture(env->monster_type->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + 0; rect.y = 0;
	last_img_width = rect.w;
  SDL_RenderCopy(ren, env->monster_type->zombie, NULL, &rect);

  SDL_QueryTexture(env->monster_type->ghost, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + windowWidth/4; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->ghost, NULL, &rect);

  SDL_QueryTexture(env->monster_type->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + 3*windowWidth/6; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->vampire, NULL, &rect);

  SDL_QueryTexture(env->monster_type->spirit, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + 3*windowWidth/4; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->spirit, NULL, &rect);
  /* end required nb monster display */

	/* required nb monster*/
	for(unsigned int x = 1; x < NB_MONSTERS+1; x++){
		int value = required_nb_monsters(env->game, convert_int_to_content(x-1));
		SDL_Surface * label_value = sdl_text_from_string(convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = (last_img_width/2)+ (x*windowWidth/6) - windowWidth /8+ ((last_img_width/2)*x); rect.y = last_img_width/2; //Monster are 100*100px, so print at half way
		SDL_RenderCopy(ren, label, NULL, &rect);
	}

	/* labels value north (and south)*/
	for(unsigned int x = 1; x < game_width(env->game)+1; x++){

		//NORTH
		int value = required_nb_seen(env->game,N, x-1);
		SDL_Surface * label_value = sdl_text_from_string(convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = (2*windowWidth/10)+(x*windowWidth/6) - windowWidth /8; rect.y = 125; //Monster have a height of 100px
		SDL_RenderCopy(ren, label, NULL, &rect);


		//SOUTH
		value = required_nb_seen(env->game,S, x-1);
		label_value = sdl_text_from_string(convert_int_to_string("", value));

		label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x =  (2*windowWidth/10)+(x*windowWidth/6) - windowWidth /8; rect.y = windowHeight - 100; //Monster have a height of 100px
		SDL_RenderCopy(ren, label, NULL, &rect);
	}



	/* labels value east (and west)*/
	for(unsigned int x = 0; x < game_height(env->game); x++){

		//EAST
		int value = required_nb_seen(env->game,E, x);
		SDL_Surface * label_value = sdl_text_from_string(convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = windowWidth - windowWidth/10; rect.y = 150+x*100; //Monster have a height of 100px
		SDL_RenderCopy(ren, label, NULL, &rect);


		//WEST
		value = required_nb_seen(env->game, W, x);
		label_value = sdl_text_from_string(convert_int_to_string("", value));

		label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = windowWidth/10; rect.y = 150+x*100;  //Monster have a height of 100px
		last_img_width = rect.w;
		SDL_RenderCopy(ren, label, NULL, &rect);
	}

  //Try to make a board
  SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE); /* red */
	int cell_width = (windowWidth - ((windowWidth/10 + last_img_width)*2)) / game_width(env->game);

  for(int x=0; x<game_width(env->game); x++){
    SDL_RenderDrawLine(ren, last_img_width+   windowWidth/10+ x*cell_width, HEIGHT_SHIFT+10+(x*cell_width),  last_img_width+   windowWidth/10+ (x+1)*cell_width, HEIGHT_SHIFT+60+(x*cell_width));//(x1,y1),(x2,y2)
  	for(int y=0; y<game_height(env->game); y++){
    	SDL_RenderDrawLine(ren, last_img_width+  10+(x*cell_width), HEIGHT_SHIFT+10+(y*cell_width), last_img_width+  60+(x*cell_width), HEIGHT_SHIFT+10+(y*cell_width));
    	SDL_RenderDrawLine(ren, last_img_width+  10+(x*cell_width), HEIGHT_SHIFT+60+(y*cell_width), last_img_width+  60+(x*cell_width), HEIGHT_SHIFT+60+(y*cell_width));
    	SDL_RenderDrawLine(ren, last_img_width+  10+(x*cell_width), HEIGHT_SHIFT+10+(y*cell_width), last_img_width+  10+(x*cell_width), HEIGHT_SHIFT+60+(y*cell_width));
		}
	}



  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}

/* **************************************************************** */


bool process(SDL_Window* window, SDL_Renderer* ren, Env * env, SDL_Event * e){

  /* get current window size */
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	/* generic events */
	if (e->type == SDL_QUIT){
		return true;
	}


#ifdef __ANDROID__
  else if (e->type == SDL_FINGERDOWN) {
    env->mario_x = e->tfinger.x * w; /* tfinger.x, normalized in [0..1] */
    env->mario_y = e->tfinger.y * h; /* tfinger.y, normalized in [0..1] */
  }
  /* other events */
#else
  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
		/*
    env->mario_x = mouse.x;
    env->mario_y = mouse.y;
		*/
	}
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
		/*
    case SDLK_LEFT:  env->bomb_x -= 10; break;
    case SDLK_RIGHT: env->bomb_x += 10; break;
    case SDLK_UP:    env->bomb_y -= 10; break;
    case SDLK_DOWN:  env->bomb_y += 10; break;
		*/
    case SDLK_v:  printf("key v pressed - add a vampire\n"); break;
    case SDLK_z:  printf("key z pressed - add a zombie\n"); break;
    case SDLK_g:  printf("key g pressed - add a ghost\n"); break;
    case SDLK_s:  printf("key s pressed - add a spirit\n"); break;
    case SDLK_e:  printf("key e pressed - clear the cell\n"); break;
    case SDLK_f:  printf("key f pressed - fullscreen\n"); break;
    case SDLK_ESCAPE:  return true; break;
    }
  }
#endif


  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env){
  SDL_DestroyTexture(env->mirror_type->mirror);
  SDL_DestroyTexture(env->mirror_type->antimirror);
  SDL_DestroyTexture(env->mirror_type->hmirror);
  SDL_DestroyTexture(env->mirror_type->vmirror);

  SDL_DestroyTexture(env->monster_type->empty);

  SDL_DestroyTexture(env->monster_type->zombie);
  SDL_DestroyTexture(env->monster_type->spirit);
  SDL_DestroyTexture(env->monster_type->ghost);
  SDL_DestroyTexture(env->monster_type->vampire);

  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->text);

	delete_game(env->game);

  free(env);
}

/* **************************************************************** */
