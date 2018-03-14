// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"


/* **************************************************************** */
#define FONT "Arial.ttf"
#define FONTSIZE 36
#define BACKGROUND "../ressources/background.png"
#define ANTIMIRROR "../ressources/antimirror.png"
#define GHOST "../ressources/ghost.png"
#define HMIRROR "../ressources/hmirror.png"
#define MIRROR "../ressources/mirror.png"
#define SPIRIT "../ressources/spirit.png"
#define VAMPIRE "../ressources/vampire.png"
#define VMIRROR "../ressources/vmirror.png"
#define ZOMBIE "../ressources/zombie.png"

struct Env_t {

  /* PUT YOUR VARIABLES HERE */
  SDL_Texture * background;
  SDL_Texture * antimirror;
  SDL_Texture * ghost;
  SDL_Texture * hmirror;
  SDL_Texture * mirror;
  SDL_Texture * spirit;
  SDL_Texture * vampire;
  SDL_Texture * vmirror;
  SDL_Texture * zombie;
  SDL_Texture * text;
  //current position were we want to place the monster
  int pos_x, pos_y;
};

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){
  Env * env = malloc(sizeof(struct Env_t));

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */
  int width, height;
  SDL_GetWindowSize(win, &width, &height);
  //env -> pos_x =
  //env -> pos_y =

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);
  /* init antimirror texture from PNG image */
  env->antimirror = IMG_LoadTexture(ren, ANTIMIRROR);
  if(!env->antimirror) ERROR("IMG_LoadTexture: %s\n", ANTIMIRROR);
  /* init hmirror texture from PNG image */
  env->hmirror = IMG_LoadTexture(ren, HMIRROR);
  if(!env->hmirror) ERROR("IMG_LoadTexture: %s\n", HMIRROR);
  /* init vmirror texture from PNG image */
  env->vmirror = IMG_LoadTexture(ren, VMIRROR);
  if(!env->vmirror) ERROR("IMG_LoadTexture: %s\n", VMIRROR);

  /* init zombie texture from PNG image */
  env->zombie = IMG_LoadTexture(ren, ZOMBIE);
  if(!env->ZOMBIE) ERROR("IMG_LoadTexture: %s\n", ZOMBIE);
  /* init ghost texture from PNG image */
  env->ghost = IMG_LoadTexture(ren, ghost);
  if(!env->ghost) ERROR("IMG_LoadTexture: %s\n", GHOST);
  /* init background texture from PNG image */
  env->spirit = IMG_LoadTexture(ren, SPIRIT);
  if(!env->spirit) ERROR("IMG_LoadTexture: %s\n", SPIRIT);

  /* init text texture using Arial font */
  SDL_Color color = { 0, 0, 255, 255 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "0", color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env * env){
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
  SDL_Rect rect;

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */


  /* get current window size */
  int width, height;
  SDL_GetWindowSize(window, &width, &height);

  /* required nb monster display */
  SDL_QueryTexture(env->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + 0; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->zombie, NULL, &rect);

  SDL_QueryTexture(env->ghost, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + width/4; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->ghost, NULL, &rect);

  SDL_QueryTexture(env->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + width/3 + width/6; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->vampire, NULL, &rect);

  SDL_QueryTexture(env->spirit, NULL, NULL, &rect.w, &rect.h);
  rect.x = rect.w/4 + width/2 + width/4; rect.y = rect.h/5;
  SDL_RenderCopy(ren, env->spirit, NULL, &rect);



}

/* **************************************************************** */


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){
  int width, height;
  SDL_GetWindowSize(win, &width, &height);

  if (e->type == SDL_QUIT) {
    return true;
  }
  /* Android events */
#ifdef __ANDROID__
  else if (e->type == SDL_FINGERDOWN) {
    env->pos_x = e->tfinger.x * width; /* tfinger.x, normalized in [0..1] */
    env->pos_y = e->tfinger.y * height; /* tfinger.y, normalized in [0..1] */
  }
  /* other events */
#else
  /*else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    env->mario_x = mouse.x;
    env->mario_y = mouse.y;
  }*/

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
    case SDLK_LEFT:  env->pos_x -= 10; break;
    case SDLK_RIGHT: env->pos_x += 10; break;
    case SDLK_UP:    env->pos_y -= 10; break;
    case SDLK_DOWN:  env->pos_y += 10; break;
    case SDLK_ESCAPE:  return true; break;
    }
  }
#endif
  return false;
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env){
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
  SDL_DestroyTexture(env->mirror);
  SDL_DestroyTexture(env->antimirror);
  SDL_DestroyTexture(env->hmirror);
  SDL_DestroyTexture(env->vmirror);

  SDL_DestroyTexture(env->zombie);
  SDL_DestroyTexture(env->spirit);
  SDL_DestroyTexture(env->ghost);
  SDL_DestroyTexture(env->text);
  SDL_DestroyTexture(env->vampire);
  SDL_DestroyTexture(env->background);
  free(env);
}

/* **************************************************************** */
