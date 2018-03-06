#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_display.h"



bool board_is_full(game g){
	for (signed int x = 0; x < game_width(g); x++){
		for(int y = 0; y < game_height(g); y++){
			if(get_content(g,x,y) == EMPTY)
				return false;
		}
	}
	return true;
}

void append(char* s, char c){
				int len = strlen(s);
				s[len] = c;
				s[len+1] = '\0';
}

char* concat(const char *s1, const char *s2){
		char * result = (char *) malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
		//check for errors in malloc here
		strcpy(result, s1);
		strcat(result, s2);
		return result;
}




char* convert_int_to_string(char*str, int val){
	char * res = (char *) malloc(sizeof(char) * (strlen(str)+val/10) );
	sprintf(res, "%s%d",str,val);
	return res;
}

content convert_char_to_content(char c){
	switch(c){
		case 'G':
			return GHOST;
		case 'g':
			return GHOST;
		case 'S':
			return SPIRIT;
		case 's':
			return SPIRIT;
		case 'V':
			return VAMPIRE;
		case 'v':
			return VAMPIRE;
		case 'z':
			return ZOMBIE;
		case 'Z':
			return ZOMBIE;
		case 'e':
			return EMPTY;
		case 'E':
			return EMPTY;
	}
	return EMPTY;
}
