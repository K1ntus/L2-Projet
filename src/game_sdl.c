#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //access() fun + chdir
#include <stdbool.h>
#include <math.h>

#include "../header/game_display.h"
#include "../header/game_io.h"
#include "../header/game_fun.h"
#include "../header/game.h"
#include "../header/model.h"


char* get_required_nb_monsters(game g, content monster){

}

char* get_required_nb_seen(game g, unsigned int pos, direction dir){

}

char convert_content_to_char(game g, content mstr){

}


//Position de la souris, ou entrée clavier pour choisir un monstre, je ne sais pas encore
void convert_sdl_input_to_position(unsigned int pos_src, unsigned int * x, unsigned int * y){
	*y = 0;
	*x = 0;
}

content get_which_mob_is_select(unsigned int pos_src){	//pas sur de la maniere encore

}
