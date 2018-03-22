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
  * @brief possible input mode for the solver
  * FIND_ONE save file containing one solution of the board
  * NB_SOL ssave a file with the number of solution for the game as parameters
  * FIND_ALL save files (max. 5) with possible and differents solutions of the board
  **/
 typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode;


 /**
  * @brief Solver: verify if the solution to compare already exist
  * @param g the game solved to verify
  * @param array a vector containing all game solutions
  * @return true if already saved, false sinon
  **/
 bool board_already_saved_as_solution(game g1, game * array);


  /**
   * @brief Solver: working on, check if its worth to continue on this board
   * @param g the game solved to verify
   * @return true if invalid game
   **/
 bool potential_invalid_game(game g);

  /**
   * @brief Solver: Add a solved board to a game * variable
   * @param g the game solved to verify
   * @param res vector which contain game_solved or NULL
   * @return add the game to the vector at the first NULL value (and if there's less than 5 solutions)
   **/
 void append_game_array(game g, game * res);


 void result_array_init(game * res);

  /**
   * @brief Solver: return the wanted solve mode from input string
   * @param *argv the string from input
   * @return '"FIND_ONE, FIND_ALL or NB_SOL"'
   **/
 solve_mode get_which_solve_mode_is_asked (char * argv);


  /**
   * @brief Solver: save one game board which resolve the one as parameters
   * @param resArray an array with all available solutions
   * @param prefix the string for the beginning of the file
   * @param n should be set at 0 ! REALLY
   * @return void
   **/
 void save_one_solution (game * resArray, char * prefix, int n);

   /**
    * @brief Solver: save all (max.5) game board which resolve the one as parameters
    * @param res an array with all available solutions
    * @param prefix the string for the beginning of the file
    * @param nbSol the numbers of solutions
    * @return void
    **/
 void save_all_solutions(game * res, char*prefix, int nbSol);

  /**
   * @brief Solver: save the number of solution on a file
	 * @param s the solving mode
	 * @param res an array with all available solutions
	 * @param nbSol the numbers of solutions
	 * @param prefix the string for the beginning of the file
   * @return void
   **/
 void save_nb_sol(int nbSol, char * prefix);


  /**
   * @brief Solver: save the data from solver depending of the solving mode
 	 * @param s the solving mode
 	 * @param nbSol the numbers of solutions
 	 * @param res an array with all available solutions
 	 * @param prefix the string for the beginning of the file
   * @return void
  **/
 void saving_data_from_the_solver (solve_mode s, int nbSol, game * res, char * prefix);




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
 * @return char*
 **/
char* convert_int_to_string(char*str, int val);


/**
 * @brief convert a char c to a content type
 * @param c the entry character to convert
 * @return a monster type (ZOMBIE; GHOST; SPIRIT; VAMPIRE)
 **/
content convert_char_to_content(char c);



/**
 * @brief verify if every cells aren't EMPTY
 * @param g the game board to check
 * @return true if the board doesnt have any EMPTY cell, else false
 **/
bool board_is_full(game g);



///@}

#endif // _GAME_H_
