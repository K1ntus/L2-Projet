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

 /**
  * @brief display an empty line on the console
  * @param g the game board
  * @return void
  **/
void display_empty_line(game g);

 /**
  * @brief display the required numbers of monsters to place
  * @param g the game board
  * @return void
  **/
void display_required_nb_monsters(game g);

 /**
  * @brief display the labels values of the top side
  * @param g the game board
  * @return void
  **/
void display_required_nb_seen_north(game g);

 /**
  * @brief display the labels values of the bottom and side labels
  * @param g the game board
  * @return void
  **/
void display_cellsContent_and_sideValues(game g);

 /**
  * @brief display the logo "start" at the bottom of the game
  * @param g the game board
  * @return void
  **/
void display_start(game g);

 /**
  * @brief function which display the whole game_board
  * @param g the game board
  * @return void
  **/
void display(game g);

#endif
