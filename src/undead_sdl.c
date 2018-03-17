// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "model.h"


/* **************************************************************** */
#define WIDTH 4
#define HEIGHT 4

#define FONT "../ressources/Arial.ttf"
#define FONTSIZE 36
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

/* **************************************************************** */

/* PUT YOUR VARIABLES HERE */
struct Env_t {
  SDL_Texture * background;

  SDL_Texture * empty;

  SDL_Texture * mirror;
  SDL_Texture * antimirror;
  SDL_Texture * vmirror;
  SDL_Texture * hmirror;

  SDL_Texture * zombie;
  SDL_Texture * spirit;
  SDL_Texture * ghost;
  SDL_Texture * vampire;

  SDL_Texture * text;

  SDL_Texture * required_nb_seen_north;
  SDL_Texture * required_nb_seen_south;
  SDL_Texture * required_nb_seen_east;
  SDL_Texture * required_nb_seen_west;

  //int bomb_x, bomb_y;
  //int mario_x, mario_y;
};

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){
  Env * env = malloc(sizeof(struct Env_t));

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init empty cell texture from PNG image */
  env->empty = IMG_LoadTexture(ren, EMPTY);
  if(!env->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY);

  /* init mirrors texture from PNG image */
  env->mirror = IMG_LoadTexture(ren, MIRROR);
  if(!env->mirror) ERROR("IMG_LoadTexture: %s\n", MIRROR);

  /* init antimirrors texture from PNG image */
  env->antimirror = IMG_LoadTexture(ren, ANTIMIRROR);
  if(!env->antimirror) ERROR("IMG_LoadTexture: %s\n", ANTIMIRROR);

  /* init vmirrors texture from PNG image */
  env->vmirror = IMG_LoadTexture(ren, VMIRROR);
  if(!env->vmirror) ERROR("IMG_LoadTexture: %s\n", VMIRROR);

  /* init hmirrors texture from PNG image */
  env->hmirror = IMG_LoadTexture(ren, HMIRROR);
  if(!env->hmirror) ERROR("IMG_LoadTexture: %s\n", HMIRROR);

  /* init zombie texture from PNG image */
  env->zombie = IMG_LoadTexture(ren, ZOMBIE);
  if(!env->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIE);

  /* init spirit texture from PNG image */
  env->spirit = IMG_LoadTexture(ren, SPIRIT);
  if(!env->spirit) ERROR("IMG_LoadTexture: %s\n", SPIRIT);

  /* init ghost texture from PNG image */
  env->ghost = IMG_LoadTexture(ren, GHOST);
  if(!env->ghost) ERROR("IMG_LoadTexture: %s\n", GHOST);

  /* init vampire texture from PNG image */
  env->vampire = IMG_LoadTexture(ren, VAMPIRE);
  if(!env->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRE);


  /* init text texture using Arial font */
    //If required_nb_monster-current_nb_monster == 0 couleur = rouge sinon couleur = noir
  SDL_Color color = { 0, 0, 255, 255 }; /* blue color in RGBA */

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "0", color); // blended rendering for ultra nice text
  env->required_nb_seen_west = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

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

  /* required nb monster display */
  SDL_QueryTexture(env->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + 0; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->zombie, NULL, &rect);

  SDL_QueryTexture(env->ghost, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + windowWidth/4; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->ghost, NULL, &rect);

  SDL_QueryTexture(env->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + windowWidth/3 + windowWidth/6; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->vampire, NULL, &rect);

  SDL_QueryTexture(env->spirit, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + windowWidth/2 + windowWidth/4; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->spirit, NULL, &rect);
  /* end required nb monster display */

  /* labels value */
  SDL_QueryTexture(env->required_nb_seen_west, NULL, NULL, &rect.w, &rect.h);
  rect.x = windowWidth/4 - windowWidth /8; rect.y = windowHeight/3;
  SDL_RenderCopy(ren, env->required_nb_seen_west, NULL, &rect);

  //Try to make a board
  SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE); /* red */
  int cell_width = 50;
  for(int i=0; i<WIDTH; i++){
    SDL_RenderDrawLine(ren, 10+(WIDTH*cell_width), 10+(i*cell_width), 10+(WIDTH*cell_width), 60+(i*cell_width));
  	for(int j=0; j<HEIGHT; j++){
    	SDL_RenderDrawLine(ren, 10+(i*cell_width), 10+(j*cell_width), 60+(i*cell_width), 10+(j*cell_width));
    	SDL_RenderDrawLine(ren, 10+(i*cell_width), 60+(j*cell_width), 60+(i*cell_width), 60+(j*cell_width));
    	SDL_RenderDrawLine(ren, 10+(i*cell_width), 10+(j*cell_width), 10+(i*cell_width), 60+(j*cell_width));
      }
    }



  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}

/* **************************************************************** */


bool process(SDL_Window* window, SDL_Renderer* ren, Env * env, SDL_Event * e){

  /* get current window size */
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env){
  SDL_DestroyTexture(env->mirror);
  SDL_DestroyTexture(env->antimirror);
  SDL_DestroyTexture(env->hmirror);
  SDL_DestroyTexture(env->vmirror);

  SDL_DestroyTexture(env->empty);

  SDL_DestroyTexture(env->zombie);
  SDL_DestroyTexture(env->spirit);
  SDL_DestroyTexture(env->ghost);
  SDL_DestroyTexture(env->vampire);

  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->text);

  free(env);
}

/* **************************************************************** */
