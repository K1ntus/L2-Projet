#ifndef _GAME_DISPLAY_H_
#define _GAME_DISPLAY_H_

#include "game.h"
#include "game_io.h"

/**
 * @file game_display.h
 *
 * @brief This file provides functions to display the map of the game.
 *
 *
 **/

//Displays an empty line
void display_empty_line(game g);

//Displays the numbers of monsters to place in top of the board
void display_required_nb_monsters(game g);

//Displays the numbers of monsters seen on the north side of the map
void display_required_nb_seen_north(game g);

//Displays a line of the map including the number of monsters seen corresponding to the same line
void display_cellsContent_and_sideValues(game g);

//Displays the start line
void display_start(game g);

//the main fonction for displaying the game (it uses the other fonctions that display the a part of the game)
void display(game g);

#endif
