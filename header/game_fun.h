#ifndef _GAME_FUN_
#define _GAME_FUN_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "game_io.h"



void append(char* s, char c);

char* concat(const char *s1, const char *s2);

char* convert_int_to_string(char* output, char*str, int val);

content convert_char_to_content(char c);




///@}

#endif // _GAME_H_
