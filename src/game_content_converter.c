#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../header/game.h"
#include "../header/game_io.h"
#include "../header/game_display.h"

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


/*
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
*/



/**
 * @brief convert the int parameters to a string variable, concat it to a string and return it
 * @param str the string where the integer will be add (note: could be "");
 * @param val the integer to convert
 * @return char* str@val
 **/
char* convert_int_to_string(char*str, int val){
	char * res = (char *) malloc(sizeof(char) * (strlen(str)+val/10) );
	sprintf(res, "%s%d",str,val);
	return res;
}




/**
 * @brief convert a char to a content_type
 * @param c the char entry parameters
 * @return the correspondant content_type, or EMPTY if dont understand the char
 **/
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
