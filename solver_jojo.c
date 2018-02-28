#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#include "game_io.c"
#include "solver_lib.c"

void convert_monster_placement_to_another_struct(s_priority_placement *array){
  s_priority_placement res[4];
  res[0] = array[0];
  unsigned int j = 0;
  for(unsigned int i = 0; i < 4; i++){
    for(j = i; j>0 && array[j].priorityValue>array[i].priorityValue; j--){
      res[j] = res[j-1];
    }
    res[j] = array[i];
  }
}

bool is_valid2(game g, int pos){
  //TMP
  if(pos >3)
    return false;

  if(pos < 0 || pos >= game_width(g)*game_height(g))
    return false;

  display(g);

  s_solverUtility structSideViewer;
  s_solverUtility * arrayOfSolverStruct = malloc(sizeof(s_solverUtility) * 50);
  s_priority_placement * arrayOfMonster = malloc(sizeof(s_priority_placement) *4);

  int x = pos%game_width(g);
  int y = pos/game_height(g);

  if(get_content(g,x,y) != EMPTY){
    free(arrayOfSolverStruct);
    return is_valid2(g,pos+1);
  }


  the_solverUtility_filler(g, structSideViewer, pos, arrayOfSolverStruct);

  arrayOfMonster = voting_to_choose_a_mob(g, arrayOfSolverStruct);
  convert_monster_placement_to_another_struct(arrayOfMonster);


  //content nextMobPlaned = which_mstr_have_a_lot_of_votes(s_monsterSelection);

  //add_monster(g,nextMobPlaned,x,y);

  free(arrayOfMonster);
  free(arrayOfSolverStruct);
  return is_valid2(g, pos+1);
}






int main(void){
  game g = new_game_ext(4,4);
	int nbMonsters[] = {2,2,5,0};

  generate(g, nbMonsters);
  if(is_valid2(g,0)){
    save_game(g, "game.sol");
  }


}
