#ifndef _GAME_JORDAN_
#define _GAME_JORDAN_
#include <stdbool.h>



#define COLONNE 4
#define LINE 4

struct game_s{
 int ** matrice;
 int vampires;
 int ghosts;
 int zombies;
 int valuesNorth[4];
 int valuesSouth[4];
 int valuesEast[4];
 int valuesWest[4];
};

/** 
 * @brief possible contents of a square on the board.
 * MIRROR stands for a mirror at +45 degrees (/), ANTIMIRROR at -45 degrees (\\) (mnemonic is slash and antislash).
 **/
typedef enum content_e {EMPTY, MIRROR, ANTIMIRROR, VAMPIRE, GHOST, ZOMBIE} content;

#define NB_POSSIBLE_FILLINGS 6

/** 
 * @brief the fourth cardinal directions
 **/

typedef enum direction_e {N,S,E,W} direction;

#define NB_DIR 4


/**
 * @brief The structure pointer that stores the game
 **/

typedef struct game_s* game;

/**
 * @brief The structure constant pointer that stores the game
 * That means that it is not possible to modify the game using this pointer.
 * See also: http://www.geeksforgeeks.org/const-qualifier-in-c/
 * See also this more technical discussion: http://stackoverflow.com/questions/8504411/typedef-pointer-const-weirdness
 **/

typedef const struct game_s* cgame;



/**
 * @brief sets the label of a game
 * @param game the game to modify
 * @param side the side of the game where the label should be modified
 * @param pos the position that the label should be modified (from S to N or from W to E)
 * @param value the new value to give to the label
 **/

void set_required_nb_seen2(game game, direction side, int pos, int value);


/**
 * @brief modifies the aimed number of a given monster on the board
 * @param game the game that you want to modify the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @param value the value you want to set to the parameter.
 **/

void set_required_nb_monsters2(game game, content monster, int value);
/**
 * @brief return the label on the side of the board
 * @param game the game we consider
 * @param side the side of the board we want the label from
 * @param pos the position of the label you want (from S to N or from W to E)
 **/

int required_nb_seen2(cgame game, direction side, int pos);

/**
 * @brief indicates the aimed number of a given monster on the board
 * @param game the game that you want to collect the information about
 * @param monster the type of monster (should be GHOST, VAMPIRE or ZOMBIE)
 * @return the number of monsters of that type that should be placed on the game.
 **/

int required_nb_monsters2(cgame game, content monster);

#endif // _GAME_H_
