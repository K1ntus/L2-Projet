#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <game_io.h>

bool test_get_content(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, GHOST, 0, 1);
  if(get_content(g, 0, 1) != GHOST) {
      fprintf(stderr,("Basic test on get_content failed\n"));
      res=false;
  }
  delete_game(g);
  return res;
}

bool test_add_mirror(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_mirror(g, 0, 1, 2);
  if(get_content(g, 1, 2) != MIRROR) {
      fprintf(stderr,"Basic test on add_mirror failed\n");
      res=false;
  }
  delete_game(g);
  return res;
}

bool test_add_monster(){
  bool res = true;
  game g =new_game();
  assert(g);
  add_monster(g,V,0,2);
  if(get_content(g,0,2)!=V){
      fprintf(stderr, "Basic test on add_monster failed");
      res = false;
  }
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
  }
  printf("INFO: Test test_set_required_nb_monsters : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//void restart_game(game g); 
//on genere une game et on place un mob+miroir -> si mob a disparu && miroir resté -> ok
//miroir pas ok car on le fait etape par etape
bool test_restart_game(){
  bool res = true;
  game g = new_game();
  assert(g);
  add_mirror(g, 0, 1, 2);
  add_monster(g, GHOST, 0, 1);
  restart_game(g);
  if(get_content(g, 0, 1) != EMPTY) {
      fprintf(stderr,("ERROR: Basic test on test_restart_game failed\n"));
      res=false;
    }
  printf("INFO: Test test_restart_game : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

bool test_current_nb_monster(){
	bool res=true;
	game g = new_game();
	add_monster(g, GHOST, 1, 1);
	add_monster(g, GHOST, 2, 1);
	add_monster(g, GHOST, 3, 1);
	add_monster(g, GHOST, 0, 1);
	assert(g);
	if(current_nb_monster(g)!=4){
    fprintf("Basic test on current_nb_monster failed\n")
    res=false;
  }
  printf("INFO: Test test_current_nb_monster: ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
		
}
//int current_nb_seen (cgame  game , direction  side , int  pos);
//void set_required_nb_seen(game game, direction side, int pos, int value);
bool test_current_nb_seen(){
  bool res = true;
  game g = new_game();
  assert(g);
  set_required_nb_seen( g , N , 0 , 1);
  if(current_nb_seen( g , N , 0) != 1) {
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
  result = test_add_monster() && result;
  result = test_current_nb_monster() && result;
  result = test_restart_game();
  result = test_set_required_nb_monsters() && result;
  result = test_set_required_nb_seen() && result;
 // result = test_current_nb_() && result;

  if(result){
      printf("Tests successfull\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("Tests failed\n");
      return EXIT_FAILURE;
  }
}
