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
#include "../header/game_io.h"
/* **************************************************************** */

#define WIDTH 4
#define HEIGHT 4

#define INIT_WIDTH_REQ_MSTRS 100
#define INIT_HEIGHT 100

#define FONT_SRC "../ressources/Arial.ttf"
#define FONTSIZE 36
#define WIDTH_SHIFT 100
#define HEIGHT_SHIFT 250

#define NB_MONSTERS 4

#define BACKGROUND_SRC "../ressources/background.png"
#define NEW_GAME_SRC "../ressources/restart.png"
#define RESTART_GAME_SRC "../ressources/new_game.png"
#define SOLUTION_SRC "../ressources/solution.png"

#define EMPTY_SRC "../ressources/empty.png"

#define MIRROR_SRC "../ressources/mirror.png"
#define ANTIMIRROR_SRC "../ressources/antimirror.png"
#define VMIRROR_SRC "../ressources/vmirror.png"
#define HMIRROR_SRC "../ressources/hmirror.png"

#define VAMPIRE_SRC "../ressources/vampire.gif"
#define GHOST_SRC "../ressources/ghost.gif"
#define SPIRIT_SRC "../ressources/spirit.png"
#define ZOMBIE_SRC "../ressources/zombie.png"

#define QUIT_SRC "../ressources/exit.png"
#define OPTIONS_SRC "../ressources/settings.png"
#define SOLVE_SRC "../ressources/solver.png"

/* **************************************************************** */

/* PUT YOUR VARIABLES HERE */

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){
  Env * env = malloc(sizeof(struct Env_t));
  env-> mirror_type = malloc(sizeof(struct mirror_type));
  env-> monster_type = malloc(sizeof(struct monster_type));
  env-> game = new_game_generation();
  env->top_corner.x = 0;
  env->top_corner.y = 0;
  env->cell_selected.x = 0;
  env->cell_selected.y = 0;

  env->monster_selected = (content) EMPTY;

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND_SRC);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND_SRC);

  /* init empty cell texture from PNG image */
  env->monster_type->empty = IMG_LoadTexture(ren, EMPTY_SRC);
  if(!env->monster_type->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY_SRC);

  /* init mirrors texture from PNG image */
  env->mirror_type->mirror = IMG_LoadTexture(ren, MIRROR_SRC);
  if(!env->mirror_type->mirror) ERROR("IMG_LoadTexture: %s\n", MIRROR_SRC);

  /* init antimirrors texture from PNG image */
  env->mirror_type->antimirror = IMG_LoadTexture(ren, ANTIMIRROR_SRC);
  if(!env->mirror_type->antimirror) ERROR("IMG_LoadTexture: %s\n", ANTIMIRROR_SRC);

  /* init vmirrors texture from PNG image */
  env->mirror_type->vmirror = IMG_LoadTexture(ren, VMIRROR_SRC);
  if(!env->mirror_type->vmirror) ERROR("IMG_LoadTexture: %s\n", VMIRROR_SRC);

  /* init hmirrors texture from PNG image */
  env->mirror_type->hmirror = IMG_LoadTexture(ren, HMIRROR_SRC);
  if(!env->mirror_type->hmirror) ERROR("IMG_LoadTexture: %s\n", HMIRROR_SRC);

  /* init zombie texture from PNG image */
  env->monster_type->zombie = IMG_LoadTexture(ren, ZOMBIE_SRC);
  if(!env->monster_type->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIE_SRC);

  /* init spirit texture from PNG image */
  env->monster_type->spirit = IMG_LoadTexture(ren, SPIRIT_SRC);
  if(!env->monster_type->spirit) ERROR("IMG_LoadTexture: %s\n", SPIRIT_SRC);

  /* init ghost texture from PNG image */
  env->monster_type->ghost = IMG_LoadTexture(ren, GHOST_SRC);
  if(!env->monster_type->ghost) ERROR("IMG_LoadTexture: %s\n", GHOST_SRC);

  /* init vampire texture from PNG image */
  env->monster_type->vampire = IMG_LoadTexture(ren, VAMPIRE_SRC);
  if(!env->monster_type->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRE_SRC);

  env->new_game_button.img = IMG_LoadTexture(ren, NEW_GAME_SRC);
  if(!env->new_game_button.img) ERROR("IMG_LoadTexture: %s\n", NEW_GAME_SRC);

  env->restart_button.img = IMG_LoadTexture(ren, RESTART_GAME_SRC);
  if(!env->restart_button.img) ERROR("IMG_LoadTexture: %s\n", RESTART_GAME_SRC);

  env->solution.img = IMG_LoadTexture(ren, SOLUTION_SRC);
  if(!env->solution.img) ERROR("IMG_LoadTexture: %s\n", SOLUTION_SRC);

  /* init text texture using Arial font */
    //If required_nb_monster-current_nb_monster == 0 couleur = rouge sinon couleur = noir

/*
  SDL_Color color = { 0, 0, 255, 255 };//Blue color in RBG

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

  SDL_Surface * surf = TTF_RenderText_Blended(font,"0", color); // blended rendering for ultra nice text
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
  env->windowHeight = windowHeight, env->windowWidth = windowWidth;

	//int y_upset = windowHeight/10;
	//int x_upset = windowHeight/5;
	int last_img_width;

  /* required nb monster display */
  SDL_QueryTexture(env->monster_type->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = 0; rect.y = 0;
	last_img_width = rect.w;
  SDL_RenderCopy(ren, env->monster_type->vampire, NULL, &rect);

  SDL_QueryTexture(env->monster_type->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x =  windowWidth/4; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->zombie, NULL, &rect);

  SDL_QueryTexture(env->monster_type->ghost, NULL, NULL, &rect.w, &rect.h);
  rect.x =  windowWidth/2; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->ghost, NULL, &rect);

  SDL_QueryTexture(env->monster_type->spirit, NULL, NULL, &rect.w, &rect.h);
  rect.x = 3*windowWidth/4; rect.y = 0;
  SDL_RenderCopy(ren, env->monster_type->spirit, NULL, &rect);
  /* end required nb monster display */

	/* required nb monster value*/
  //Each mobs icon are 64*64
	for(unsigned int x = 1; x < NB_MONSTERS+1; x++){
		int value = required_nb_monsters(env->game, convert_int_to_content(x-1));
		SDL_Surface * label_value = sdl_text_from_string_required_nb_monsters(env,convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = 64+ ((x-1)*windowWidth/4); rect.y = rect.h/2; //Monster are 64*64px, so print at half way
		SDL_RenderCopy(ren, label, NULL, &rect);
	}

  int cell_width = (windowWidth - ((windowWidth/10 + last_img_width))) / (game_width(env->game)+1);
  int cell_height = (windowHeight - ((windowHeight/10+last_img_width))) / (game_height(env->game)+1);
  int last_img_y_position;
  SDL_Surface * name;
    for(unsigned int x = 1; x < NB_MONSTERS+1; x++){
      content c = convert_int_to_content(x-1);
  		switch (c){
        case VAMPIRE:
           name =  sdl_text_from_string("Vampire :");
          break;
        case GHOST:
          name = sdl_text_from_string("Ghost :");
          break;
        case ZOMBIE:
          name =  sdl_text_from_string("Zombie :");
          break;
        case SPIRIT:
          name = sdl_text_from_string("Spirit :");
          break;
        default:
          break;
      }
  		SDL_Texture * monster_name = SDL_CreateTextureFromSurface(ren, name);
      SDL_QueryTexture(monster_name, NULL, NULL, &rect.w, &rect.h);
      rect.w/=2;
      rect.x = 25+ ((x-1)*windowWidth/4); rect.y = rect.h/2; //Monster are 64*64px, so print at half way
      SDL_RenderCopy(ren, monster_name, NULL, &rect);
    }

	/* labels value north (and south)*/
	for(unsigned int x = 0; x < game_width(env->game); x++){
		int posX = last_img_width+ (3*windowWidth/25)+ (x+1)*cell_width;

		//NORTH
		int value = required_nb_seen(env->game,N, x);
		SDL_Surface * label_value = sdl_text_from_string_labels(N,x,env, convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = posX-(last_img_width) - windowWidth/20; rect.y = windowHeight/6;//Monster have a height of 64px
		SDL_RenderCopy(ren, label, NULL, &rect);
    last_img_y_position = rect.y;


		//SOUTH
		value = required_nb_seen(env->game,S, x);
		label_value = sdl_text_from_string_labels(S,x,env, convert_int_to_string("", value));

		label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		//rect.x = posX-(last_img_width) - windowWidth/20; rect.y = windowHeight - rect.h; //Monster have a height of 64px
		rect.x = posX-(last_img_width) - windowWidth/20; rect.y = cell_height*(game_height(env->game)+1) + rect.h*2; //Monster have a height of 64px
		SDL_RenderCopy(ren, label, NULL, &rect);
	}


	/* labels value east (and west)*/
	for(unsigned int x = 0; x < game_height(env->game); x++){

		//EAST
		int value = required_nb_seen(env->game,E, game_height(env->game)-x-1);
		SDL_Surface * label_value = sdl_text_from_string_labels(E,game_height(env->game)-x-1,env,convert_int_to_string("", value));

		SDL_Texture * label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
    //rect.x = windowWidth - windowWidth/10; rect.y =  windowHeight/6 + rect.h + cell_height*x; //Monster have a height of 64px
    rect.x = cell_width*(game_width(env->game)+1) + rect.w*2; rect.y =  windowHeight/6 + rect.h + cell_height*x; //Monster have a height of 64px
    SDL_RenderCopy(ren, label, NULL, &rect);


		//WEST
		value = required_nb_seen(env->game, W, game_height(env->game)-x-1);
		label_value = sdl_text_from_string_labels(W,game_height(env->game)-x-1,env,convert_int_to_string("", value));

		label = SDL_CreateTextureFromSurface(ren, label_value);
		SDL_QueryTexture(label, NULL, NULL, &rect.w, &rect.h);
		rect.x = windowWidth/10; rect.y =  windowHeight/6 + rect.h + cell_height*x; //Monster have a height of 64px
		last_img_width = rect.w;
		SDL_RenderCopy(ren, label, NULL, &rect);
	}





  //Try to make a board
  SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE); /* dark */

  int posY = last_img_y_position+rect.h;
  int posX=windowWidth/10 + 2*last_img_width;

  int topCorner_x = posX;
  int topCorner_y = posY;

  for(int x=0; x<=game_width(env->game); x++){
    SDL_RenderDrawLine(ren, posX+x*cell_width, posY, posX+x*cell_width, posY+(game_height(env->game)*cell_height)); //Vertical lines render
  	for(int y=0; y<=game_height(env->game); y++){
      SDL_RenderDrawLine(ren, posX, posY+y*cell_height, posX+game_width(env->game) * cell_width, posY+y*cell_height);//(x1,y1),(x2,y2)	//Horizontal line render

			//posY = last_img_y_position+ (3*windowWidth/25) + (y*cell_width);
		}
	}



  env->cell_size.width = cell_width;
  env->cell_size.height = cell_height;
  env->top_corner.x = topCorner_x;
  env->top_corner.y=topCorner_y;
  display_monsters_on_board(topCorner_x, topCorner_y,  window,  ren, env, cell_width, cell_height);


  //Display new game button
  SDL_QueryTexture(env->new_game_button.img, NULL, NULL, &rect.w, &rect.h);
  rect.w /=2, rect.h /=2;
  rect.x =  0; rect.y = windowHeight-rect.h;
  env->new_game_button.top_x = rect.x;
  env->new_game_button.top_y = rect.y;
  env->new_game_button.width = rect.w;
  env->new_game_button.height = rect.h;
  SDL_RenderCopy(ren, env->new_game_button.img, NULL, &rect);

  //Display restart button
  SDL_QueryTexture(env->restart_button.img, NULL, NULL, &rect.w, &rect.h);
  rect.w /=2, rect.h /=2;
  rect.x = 0; rect.y = windowHeight-(2*rect.h);
  env->restart_button.top_x = rect.x;
  env->restart_button.top_y = rect.y;
  env->restart_button.width = rect.w;
  env->restart_button.height = rect.h;
  SDL_RenderCopy(ren, env->restart_button.img, NULL, &rect);

  //Display solution button
  SDL_QueryTexture(env->solution.img, NULL, NULL, &rect.w, &rect.h);
  rect.w /=2, rect.h /=2;
  rect.x = windowWidth-rect.w; rect.y = windowHeight-(rect.h);
  env->solution.top_x = rect.x;
  env->solution.top_y = rect.y;
  env->solution.width = rect.w;
  env->solution.height = rect.h;
  SDL_RenderCopy(ren, env->solution.img, NULL, &rect);



  if(is_game_over(env->game)){
    display_on_win(window, ren, env);
    sleep(1);
    env->game = new_game_generation();
  }

}

/* **************************************************************** */


bool process(SDL_Window* window, SDL_Renderer* ren, Env * env, SDL_Event * e){
  //SDL_SetWindowResizable(window,true);//Can(not) change the size of the window


  /* get current window size */
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);


	/* generic events */
	if (e->type == SDL_QUIT){
		return true;
	}


#ifdef __ANDROID__
  else if (e->type == SDL_FINGERDOWN) {
    get_which_cells_is_selected(e->tfinger.x * w,  e->tfinger.y*h, env);
  }
  /* other events */
#else
  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    get_which_cells_is_selected(mouse.x, mouse.y, env);
	}
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
		/*
    case SDLK_LEFT:  env->bomb_x -= 10; break;
    case SDLK_RIGHT: env->bomb_x += 10; break;
    case SDLK_UP:    env->bomb_y -= 10; break;
    case SDLK_DOWN:  env->bomb_y += 10; break;
		*/
    case SDLK_v:
      add_monster_sdl('V', env);
      //printf("key v pressed - add a vampire\n");
      break;		//Function TODO
    case SDLK_z:
      add_monster_sdl('Z', env);
      //printf("key z pressed - add a zombie\n");
      break;		//Function TODO
    case SDLK_g:
      add_monster_sdl('G', env);
      //printf("key g pressed - add a ghost\n");
      break;		//Function TODO
    case SDLK_s:
      add_monster_sdl('S', env);
      //printf("key s pressed - add a spirit\n");
      break;		//Function TODO
    case SDLK_e:
      add_monster_sdl('E', env);
      //printf("key e pressed - cell got cleared\n");
      break;		//Function TODO
    case SDLK_f:  toggle_fullscreen(window,0); break;									//Function TODO
    case SDLK_ESCAPE:  return true; break;	//Exit the program
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

  SDL_DestroyTexture(env->restart_button.img);
  SDL_DestroyTexture(env->new_game_button.img);

	delete_game(env->game);

  free(env);
}

/* **************************************************************** */
