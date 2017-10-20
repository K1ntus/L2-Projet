#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

/*
Vérifier la hauter/largeur du jeu généré



*/

//game new_game();
bool test_new_game(){
  bool res = true;
  game g= new_game();
  assert(g);
  int sum = current_nb_monsters(g, ZOMBIE);
  add_monster(g, ZOMBIE, 5, 0);
  if(current_nb_monsters != sum){
      fprintf(stderr,("ERROR: Basic test on test_new_game failed\n"));
      res=false;
      delete_game(g);
      return res;    
  }
    printf("INFO: Test test_new_game : ");
    printf(res ? "true\n" : "false\n");
    delete_game(g);
    return true;
}

//void delete_game (game g);
bool test_delete_game(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, GHOST, 0, 1);
  delete_game(g);
  int var = get_content(g, 0, 1);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  restart_game(g);
  if(sum != 0){
      fprintf(stderr,("ERROR: Basic test on test_delete_game failed\n"));
      res=false;
      delete_game(g);
      return res;
  }
  if(var != GHOST || var != VAMPIRE || var != ZOMBIE || var != MIRROR || var != ANTIMIRROR || var != EMPTY) {
    printf("INFO: Test test_delete_game : ");
    printf(res ? "true\n" : "false\n");
    delete_game(g);
    return true;
  }
  fprintf(stderr,("ERROR: Basic test on delete_game failed\n"));
  delete_game(g);
  return false;
}

//content get_content(cgame game, int col, int line);
bool test_get_content(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, GHOST, 0, 1);
  add_monster(g, VAMPIRE, 0, 2);
  add_monster(g, ZOMBIE, 0, 3);
  if(get_content(g, 0, 1) != GHOST || get_content(g, 0, 2) != VAMPIRE || get_content(g, 0, 3) != ZOMBIE ) {
      fprintf(stderr,("ERROR: Basic test on get_content failed\n"));
      res=false;
  }
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  restart_game(g);
  if(sum != 3){
      fprintf(stderr,("ERROR: Basic test on test_get_content failed\n"));
      res=false;
    delete_game(g);
    return res;
    }
  printf("INFO: test_get_content : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//void add_mirror(game game, int dir, int col, int line);
bool test_add_mirror(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_mirror(g, 0, 1, 2);
  if(get_content(g, 1, 2) != MIRROR) {
      fprintf(stderr,"ERROR: Basic test on add_mirror failed\n");
      res=false;
      delete_game(g);
      return res;
  }

  printf("INFO: test_add_mirror : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//void set_required_nb_seen(game game, direction side, int pos, int value);
//int required_nb_seen(cgame game, direction side, int pos);
bool test_set_required_nb_seen(){
  bool res = true;
  game g = new_game();
  assert(g);
  set_required_nb_seen(g, N, 0, 1);
  if(required_nb_seen(g,N,0) != 1){
      fprintf(stderr,"ERROR: Basic test on set_required_nb_seen failed\n");
      res=false;
      delete_game(g);
      return res;
  }
  printf("INFO: test_set_required_nb_seen : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//void set_required_nb_monsters(game game, content monster, int value);
//int required_nb_monsters(cgame game, content monster);
bool test_set_required_nb_monsters(){
  bool res = true;
  game g = new_game();
  assert(g);
  set_required_nb_monsters(g, ZOMBIE, 2);
  if(required_nb_monsters(g, ZOMBIE) != 2){
      fprintf(stderr,"ERROR: Basic test on set_required_nb_monsters failed\n");
      res=false;
      delete_game(g);
      return res;
  }
  printf("INFO: Test test_set_required_nb_monsters : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//bool add_monster(game game, content monster, int col, int line);

//void restart_game(game g);
//on genere une game et on place un mob+miroir -> si mob a disparu && miroir resté -> ok
//miroir pas ok car on le fait etape par etape
bool test_restart_game(){
  bool res = true;
  game g = new_game();
  assert(g);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  restart_game(g);
  if(sum != 0){
      fprintf(stderr,("ERROR: Basic test on test_restart_game failed\n"));
      res=false;
    }
  printf("INFO: Test test_restart_game : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}


int main(void){
  bool result = true;
  result = test_get_content() && result;
  result = test_add_mirror() && result;
  result = test_set_required_nb_seen() && result;
  result = test_set_required_nb_monsters() && result;
  result = test_restart_game() && result;
  result = test_delete_game() && result;
  result = test_new_game() && result;
  if(result){
      printf("\nINFO: All tests successfull\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("\nINFO: A test failed\n");
      return EXIT_FAILURE;
  }
}
