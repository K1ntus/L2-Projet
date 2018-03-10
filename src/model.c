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
  //int bomb_x, bomb_y;
  //int mario_x, mario_y;
};

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){
  Env * env = malloc(sizeof(struct Env_t));

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init mario texture from PNG image */
  env->empty = IMG_LoadTexture(ren, EMPTY);
  if(!env->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY);

  /* init bomb texture from PNG image */
  env->mirror = IMG_LoadTexture(ren, MIRROR);
  if(!env->mirror) ERROR("IMG_LoadTexture: %s\n", MIRROR);
  /* init bomb texture from PNG image */
  env->antimirror = IMG_LoadTexture(ren, ANTIMIRROR);
  if(!env->antimirror) ERROR("IMG_LoadTexture: %s\n", ANTIMIRROR);
  /* init bomb texture from PNG image */
  env->vmirror = IMG_LoadTexture(ren, VMIRROR);
  if(!env->vmirror) ERROR("IMG_LoadTexture: %s\n", VMIRROR);
  /* init bomb texture from PNG image */
  env->hmirror = IMG_LoadTexture(ren, HMIRROR);
  if(!env->hmirror) ERROR("IMG_LoadTexture: %s\n", HMIRROR);


  /* init bomb texture from PNG image */
  env->zombie = IMG_LoadTexture(ren, ZOMBIE);
  if(!env->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIE);
  /* init bomb texture from PNG image */
  env->spirit = IMG_LoadTexture(ren, SPIRIT);
  if(!env->spirit) ERROR("IMG_LoadTexture: %s\n", SPIRIT);
  /* init bomb texture from PNG image */
  env->ghost = IMG_LoadTexture(ren, GHOST);
  if(!env->ghost) ERROR("IMG_LoadTexture: %s\n", GHOST);
  /* init bomb texture from PNG image */
  env->vampire = IMG_LoadTexture(ren, VAMPIRE);
  if(!env->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRE);

  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env * env){
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}

/* **************************************************************** */


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){

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

