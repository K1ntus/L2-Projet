#ifndef _GAME_FUN_
#define _GAME_FUN_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "game_io.h"

/**
 * @file game_fun.h
 *
 * @brief This file provides useful functions to manage the game.
 *
 *
 **/


/**
 * @brief add a char at the end of a string
 * @param s string to modify
 * @param c the character to add to the string
 * @return void
 **/
void append(char* s, char c);

/**
 * @brief concat s1 with s2
 * @param s1 the first string to concatene with
 * @param s2 the second string to concat
 * @return a string with the result
 **/
char* concat(const char *s1, const char *s2);

/**
 * @brief convert an integer to a string and append it at the end of a char* variable
 * @param str a string
 * @param val the integer to convert
 * @return char* output
 **/
char* convert_int_to_string(char* output, char*str, int val);


/**
 * @brief convert a char c to a content type
 * @param c the entry character to convert
 * @return a monster type (ZOMBIE; GHOST; SPIRIT; VAMPIRE)
 **/
content convert_char_to_content(char c);


///@}

#endif // _GAME_H_
