#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game_lib_v2.c"
#include <time.h>   // pour rand


void generate(game g){

  set_required_nb_monsters (g, ZOMBIE,  5);
  set_required_nb_monsters (g, GHOST, 2);
  set_required_nb_monsters (g, SPIRIT, 0);
  set_required_nb_monsters (g, VAMPIRE,  2);

//AntiMirror
  add_mirror_ext(g,ANTIMIRROR,0,0);
  add_mirror_ext(g,ANTIMIRROR,0,2);
  add_mirror_ext(g,ANTIMIRROR,0,3);
  add_mirror_ext(g,ANTIMIRROR,3,0);
  add_mirror_ext(g,ANTIMIRROR,2,1);

//Mirror
  add_mirror_ext(g,MIRROR,3,3);
  add_mirror_ext(g,MIRROR,3,1);


  set_required_nb_seen (g, N, 0, 0);
  set_required_nb_seen (g, N, 1, 3);
  set_required_nb_seen (g, N, 2, 3);
  set_required_nb_seen (g, N, 3, 0);

  set_required_nb_seen (g, S, 3, 3);
  set_required_nb_seen (g, S, 2, 2);
  set_required_nb_seen (g, S, 1, 3);
  set_required_nb_seen (g, S, 0, 0);

  set_required_nb_seen (g, E, 0, 0);
  set_required_nb_seen (g, E, 1, 0);
  set_required_nb_seen (g, E, 2, 3);
  set_required_nb_seen (g, E, 3, 2);

  set_required_nb_seen (g, W, 3, 3);
  set_required_nb_seen (g, W, 2, 3);
  set_required_nb_seen (g, W, 1, 2);
  set_required_nb_seen (g, W, 0, 0);

  add_monster(g,GHOST,  1,1);
  add_monster(g,GHOST,  2,0);
  add_monster(g,VAMPIRE,1,3);
  add_monster(g,VAMPIRE,2,3);
  add_monster(g,ZOMBIE, 0,1);
  add_monster(g,ZOMBIE, 1,0);
  add_monster(g,ZOMBIE, 1,2);
  add_monster(g,ZOMBIE, 2,2);
  add_monster(g,ZOMBIE, 3,2);
}




bool test_add_monster_ghost(){
  bool res = true;
  game g =new_game_ext(4,4);
  assert(g);
  add_monster(g,GHOST,2,2);

  //If the pos where the ghost should be isnt good
  if(get_content(g,2,2) != GHOST){
    res=false;
  }

  //If any pos != where the ghost should be is not empty
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          res=false;
        }
      }
    }
  }

  printf(res ? "INFO:  test_add_monster_ghost : ✓\n" : "INFO:  test_add_monster_ghost ✕\n");
  delete_game(g);
  return res;
}

bool test_add_monster_zombie(){
  bool res = true;
  game g =new_game_ext(4,4);
  assert(g);
  add_monster(g,ZOMBIE,2,2);

    //If any pos != where the zombie should be is not good
  if(get_content(g,2,2) != ZOMBIE){
    res = false;
  }

    //If any pos != where the zombie should be is not empty
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          res = false;
        }
      }

    }
  }

  printf(res ? "INFO:  test_add_monster_zombie : ✓\n" : "INFO:  test_add_monster_zombie ✕\n");
  delete_game(g);
  return res;
}

bool test_add_monster_vampire(){
  bool res = true;
  game g =new_game_ext(4,4);
  assert(g);
  add_monster(g,VAMPIRE,2,2);

    //If any pos != where the vampire should be is not good
  if(get_content(g,2,2) != VAMPIRE){
    res = false;
  }

    //If any pos != where the vampire should be is not empty
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          res = false;
        }
      }

    }
  }

  printf(res ? "INFO:  test_add_monster_vampire : ✓\n" : "INFO:  test_add_monster_vampire ✕\n");
  delete_game(g);
  return res;
}


bool test_add_monster(){
  bool res = true;
  res = test_add_monster_vampire() && res;
  res = test_add_monster_zombie() && res;
  res = test_add_monster_ghost() && res;

  game g =new_game_ext(4,4);

  //If add_monster_zombie/ghost/vampire return false
  if(res == false){
    res=false;  //No return because wanna display text at the end of the function, na !
  }

  assert(g);
  add_monster(g,VAMPIRE,1,2);

    //If any pos != where the vampire should be is not good
  if(get_content(g, 1, 2) != VAMPIRE){
    res=false;
  }
  assert(g);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
//If there's not another monster adding himself when it should not have


  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 1 || y != 2)
      if(get_content(g,x,y) != EMPTY){
        res=false;
      }
    }
  }

  printf(res ? "INFO:  test_add_monster : success\n" : "ERROR: test_add_monster failed\n");
  delete_game(g);
  return res;
}

bool test_current_nb_monster(){
  bool res=true;
  game g = new_game_ext(4,4);
  assert(g);
  add_monster(g, GHOST, 1, 1);
  add_monster(g, ZOMBIE, 1, 1);
  add_monster(g, ZOMBIE, 1, 2);
  add_monster(g, VAMPIRE, 1, 2);
  add_monster(g, VAMPIRE, 0, 3);
  add_monster(g, GHOST, 0, 3);
  assert(g);
  if(current_nb_monsters(g,GHOST)!=1 || current_nb_monsters(g,ZOMBIE)!=1 || current_nb_monsters(g,VAMPIRE)!=1){
    res=false;
  }

  restart_game(g);
  assert(g);
  add_monster(g, GHOST, 1, 1);
  if(current_nb_monsters(g, GHOST) != 1){
    res=false;
  }

  restart_game(g);
  add_monster(g, ZOMBIE, 1, 1);
  if(current_nb_monsters(g,ZOMBIE) != 1){
    res=false;
  }

  add_monster(g, VAMPIRE, 1, 1);
  if(current_nb_monsters(g,VAMPIRE) != 1){
    res=false;
  }
  printf(res ? "INFO:  test_current_nb_monster : success\n" : "ERROR: test_current_nb_monster failed\n");
  delete_game(g);
  return res;
}

//int current_nb_seen (cgame  game , direction  side , int  pos);
//void set_required_nb_seen(game game, direction side, int pos, int value);
bool test_current_nb_seen(){
  bool res=true;
  game g = new_game_ext(4,4);
  assert(g);
  add_monster(g, VAMPIRE, 1, 0);
  add_monster(g, ZOMBIE, 2, 0);
  add_monster(g, GHOST, 3, 0);
  if(current_nb_seen(g,S,1)!=1){
    res=false;
  }
  if(current_nb_seen(g,S,2)!=1){
    res=false;
  }
  if(current_nb_seen(g,S,3)!=0){
    res=false;
  }
  restart_game(g);
  add_mirror_ext(g,ANTIMIRROR,0,0);
  if(current_nb_seen(g,S,0)!=0){
    res=false;
  }
  restart_game(g);
  add_mirror_ext(g,MIRROR,0,0);
  add_monster(g, VAMPIRE, 1, 0);
  add_monster(g, ZOMBIE, 2, 0);
  add_monster(g, GHOST, 3, 0);
  if(current_nb_seen(g,S,0)!=2){
    res=false;
  }
  delete_game(g);
  g = new_game_ext(4,4);

  add_mirror_ext(g,ANTIMIRROR,0,0);
  add_mirror_ext(g,MIRROR,3,0);
  add_monster(g,VAMPIRE,1,0);
  add_monster(g,GHOST,2,0);

  if(current_nb_seen(g,N,0)!=1 || current_nb_seen(g,N,1)!=1 || current_nb_seen(g,N,2)!=0 || current_nb_seen(g,N,3)!=1){
    res=false;
  }
  if(current_nb_seen(g,S,0)!=0 || current_nb_seen(g,S,1)!=1 || current_nb_seen(g,S,2)!=0 || current_nb_seen(g,S,3)!=0){
    res=false;
  }
  if(current_nb_seen(g,W,0)!= 0 || current_nb_seen(g,E,0)!=0){
    res=false;
  }
  delete_game(g);
  g = new_game_ext(4,4);
  add_mirror_ext(g,ANTIMIRROR,0,0);
  add_mirror_ext(g,MIRROR,3,0);
  add_monster(g,ZOMBIE,1,0);

  if(current_nb_seen(g,N,0)!=1 || current_nb_seen(g,N,1)!=1 || current_nb_seen(g,N,2)!=0 || current_nb_seen(g,N,3)!=1){
    res=false;
  }
  if(current_nb_seen(g,S,0)!=0 || current_nb_seen(g,S,1)!=1 || current_nb_seen(g,S,2)!=0 || current_nb_seen(g,S,3)!=0){
    res=false;
  }
  if(current_nb_seen(g,W,0)!= 0 || current_nb_seen(g,E,0)!=0){
    res=false;
  }

  printf(res ? "INFO:  test_current_nb_seen : success\n" : "ERROR: test_current_nb_seen failed\n");
  delete_game(g);
  return res;
}

bool test_current_nb_seen_advanced(){
  bool res = true;
  game g = new_game_ext(4,4);
  assert(g);
  generate(g);
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(required_nb_seen(g,i,j) != current_nb_seen(g,i,j)){

        res=false;
      }
    }
  }
  printf(res ? "INFO:  test_current_nb_seen_advanced : ✓\n" : "INFO:  test_current_nb_seen_advanced ✕\n");
  delete_game(g);
  return res;
}

bool test_new_game_advanced(){
  bool res = true;
  game g= new_game_ext(4,4);
  assert(g);
  add_monster(g,GHOST,2,2);
  if(get_content(g,2,2) != GHOST){

    res=false;
  }
  delete_game(g);
  g=new_game_ext(4,4);
  add_monster(g,GHOST,2,2);
  restart_game(g);

  if(get_content(g,2,2) != EMPTY){

    res=false;
  }
  delete_game(g);
  g=new_game_ext(4,4);
  if(get_content(g,2,2) != EMPTY){

    res=false;
  }
  printf(res ? "INFO:  test_new_game_advanced : ✓\n" : "INFO:  test_new_game_advanced ✕\n");
  delete_game(g);
  return res;
}

//game new_game_ext(4,4);
bool test_new_game_ext(){
  bool res = true;
  res = test_new_game_advanced() && res;
  game g= new_game_ext(4,4);
  assert(g);
  if(g == NULL){
    res=false;
  }
  //printf("Address: %p\n", &g);
  //printf("Address: %p\n", (void *)g+4);
  //NOP : assert(get_content(g, 5, 5));
  for(unsigned int i = 0; i < g -> width; i++){
    for(unsigned int j = 0; j < g -> height; j++){
      if(get_content(g, i, j) != EMPTY){
        res=false;
      }
    }
  }

  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(required_nb_seen(g, j, i) != 0){
        res=false;
      }
    }
  }

  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if( current_nb_seen(g,i,j) != 0){
        res=false;
      }
    }
  }

  printf(res ? "INFO:  test_new_game_ext : success\n" : "ERROR: test_new_game_ext failed\n");
  delete_game(g);
  //printf("Address: %p\n", &g);
  //printf("Address: %p\n", (void *)g);
  return res;
}

bool test_delete_game_advanced(){
  bool res = true;
  game g = new_game_ext(4,4);
  assert(g);
  game g1 = new_game_ext(4,4);
  assert(g);
  add_monster(g, VAMPIRE, 0, 1);
  delete_game(g1);
  if(current_nb_monsters(g,VAMPIRE) != 1){
    res = false;
  }
  delete_game(g);
  assert(g);
  printf(res ? "INFO:  test_delete_game_advanced : ✓\n" : "INFO:  test_delete_game_advanced ✕\n");
  return res;
}

//void delete_game (game g);
bool test_delete_game(){
  bool res=true;
  res = test_delete_game_advanced()&&res;
  game g = new_game_ext(4,4);
  assert(g);
  add_monster(g, VAMPIRE, 0, 1);
  add_monster(g, ZOMBIE, 0, 1);
  add_monster(g, GHOST, 0, 1);
  delete_game(g);
  g = new_game_ext(4,4);
  assert(g);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);

  if(sum != 0){
    res=false;
  }
  delete_game(g);
  g=new_game_ext(4,4);
  //chech current nb seen etc
  add_monster(g,ZOMBIE,0,0);
  add_monster(g,GHOST,0,1);
  add_monster(g,VAMPIRE,0,2);
  sum = current_nb_seen(g,S,0)+current_nb_seen(g,S,1)+current_nb_seen(g,S,2);
  if(sum != 2){
    res=false;
  }
  printf(res ? "INFO:  test_delete_game : success\n" : "ERROR: test_delete_game failed\n");
  assert(g);
  delete_game(g);
  assert(g);
  return res;
}

//content get_content(cgame game, int col, int g -> height);
bool test_get_content(){
  bool res=true;
  game g = new_game_ext(4,4);
  assert(g);
  add_monster(g, GHOST, 0, 1);
  add_monster(g, VAMPIRE, 0, 2);
  add_monster(g, ZOMBIE, 0, 3);
  assert(g);
  if(get_content(g, 0, 1) != GHOST){
        res=false;
  }
  if(get_content(g, 0, 2) != VAMPIRE){
        res=false;
  }
  if(get_content(g, 0, 3) != ZOMBIE ) {
        res=false;
  }
  if(get_content(g, 1, 0) != EMPTY || get_content(g, 2, 0) != EMPTY || get_content(g, 3, 0) != EMPTY ) {
        res=false;
  }
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  assert(g);
  if(sum != 3){
    res=false;
  }
  printf(res ? "INFO:  test_get_content : success\n" : "ERROR: test_get_content failed\n");
  delete_game(g);
  return res;
}

//void add_mirror_ext(game game, int dir, int col, int g -> height);
bool test_add_mirror_ext(){
  bool res=true;
  game g = new_game_ext(4,4);
  assert(g);
  add_mirror_ext(g, MIRROR, 1, 2);
  if(get_content(g, 1, 2) != MIRROR) {
    assert(g);
    res=false;
  }
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 1 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          assert(g);
          res=false;
        }
      }
    }
  }

  //TEST ANTIMIRROR
  restart_game(g);
  assert(g);
  add_mirror_ext(g, ANTIMIRROR, 1, 2);
  if(get_content(g, 1, 2) != ANTIMIRROR) {
    assert(g);
    res=false;
  }
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x != 1 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          assert(g);
          res=false;
        }
      }
    }
  }
  printf(res ? "INFO:  test_add_mirror : success\n" : "ERROR: test_add_mirror failed\n");
  delete_game(g);
  assert(g);
  return res;
}

//void set_required_nb_seen(game game, direction side, int pos, int value);
//int required_nb_seen(cgame game, direction side, int pos);
bool test_set_required_nb_seen(){
  bool res = true;
  game g = new_game_ext(4,4);
  assert(g);
  set_required_nb_seen( g , N , 0 , 1);
  if(required_nb_seen(g,N,0) != 1){
    assert(g);
    res=false;
  }
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(j != 0 && i != 1){
        if(required_nb_seen(g ,j , i) != 0){
          assert(g);
          res=false;
        }
      }
    }
  }
//TEST 2

  restart_game(g);
  assert(g);
  set_required_nb_seen( g , N , 0 , 1);
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      set_required_nb_seen( g , j , i , i );
    }
  }
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      int tmp = required_nb_seen( g , j , i );
      if(tmp != i){
        assert(g);
        res=false;
      }
    }
  }
  printf(res ? "INFO:  test_set_required_nb_seen : success\n" : "ERROR: test_set_required_nb_seen failed\n");
  delete_game(g);
  assert(g);
  return res;
}

//void set_required_nb_monsters(game game, content monster, int value);
//int required_nb_monsters(cgame game, content monster);
bool test_set_required_nb_monsters(){
  bool res = true;
  game g = new_game_ext(4,4);
  assert(g);
  set_required_nb_monsters(g, ZOMBIE, 2);
  if(required_nb_monsters(g, ZOMBIE) != 2){
    res=false;
  }
  printf(res ? "INFO:  test_set_required_nb_monsters : success\n" : "ERROR: test_set_required_nb_monsters failed\n");
  delete_game(g);
  assert(g);
  return res;
}


//void restart_game(game g);
//on genere une game et on place un mob+miroir -> si mob a disparu && miroir restÃƒÂ© -> ok
//miroir pas ok car on le fait etape par etape
bool test_restart_game(){
  bool res = true;
  int sum = 0;
  game g = new_game_ext(4,4);
  assert(g);


  sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  restart_game(g);
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(get_content(g,x,y) != EMPTY){
        res=false;
      }
    }
  }
  assert(g);
  if(g == NULL){
    res=false;
  }
  if(sum != 0){
    res=false;
  }

  add_mirror_ext(g,MIRROR,2,1);
  restart_game(g);
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x !=2 && y !=1)
      if(get_content(g,x,y) != EMPTY){
        res=false;
      }
    }
  }

  add_mirror_ext(g, MIRROR, 1, 2);
  delete_game(g);
  g=new_game_ext(4,4);
  restart_game(g);
  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(x !=1 && y !=2)
      if(get_content(g,x,y) != EMPTY){
        res=false;
      }
    }
  }


  printf(res ? "INFO:  test_restart_game : success\n" : "ERROR: test_restart_game failed\n");
  delete_game(g);
  return res;
}

bool test_is_game_over(){
  bool res = true;
  game g = new_game_ext(4,4);
  assert(g);


  if(is_game_over(g) == false){
    res=false;
  }
  printf(res ? "INFO:  test_is_game_over : success\n" : "ERROR: test_is_game_over failed\n");
  delete_game(g);
  return res;
}

bool test_copy_game(){
  bool res = true;
  game g = new_game_ext(4,4);
  game g1 = copy_game(g);

  for(unsigned int x = 0; x < g -> width; x++){
    for(unsigned int y = 0; y < g -> height; y++){
      if(get_content(g1,x,y) != get_content(g, x, y)){
        res=false;
      }
    }
  }
  printf(res ? "INFO:  test_copy_game : success\n" : "ERROR: test_copy_game failed\n");
  delete_game(g);
  delete_game(g1);
  return res;
}


bool test_setup_new_game_ext(){
  bool res = true;
  int nb_ghosts = 2;
  int nb_vampires = 2;
  int nb_spirits = 0;
  int nb_zombies = 5;
  int valueNorth[] = {0, 3, 3, 0};
  int valueSouth[] = {0, 3, 2, 3};
  int valueEast[] = {0, 0, 3, 2};
  int valueWest[] = {0, 2, 3, 3};
  int *values [] = {valueNorth, valueSouth, valueEast, valueWest};
  content gameBoard[]={ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, ANTIMIRROR, MIRROR, ANTIMIRROR, EMPTY, EMPTY, EMPTY, ANTIMIRROR, EMPTY, EMPTY, MIRROR};
  game g = setup_new_game_ext(4,4, values, gameBoard, nb_ghosts, nb_vampires ,nb_zombies, nb_spirits);
  assert(g);
  add_monster(g,GHOST, 1, 1);
  add_monster(g,GHOST, 2, 0);
  add_monster(g,VAMPIRE,1,3);
  add_monster(g,VAMPIRE,2,3);
  add_monster(g,ZOMBIE, 0,1);
  add_monster(g,ZOMBIE, 1,0);
  add_monster(g,ZOMBIE, 1,2);
  add_monster(g,ZOMBIE, 2,2);
  add_monster(g,ZOMBIE, 3,2);
  if(!is_game_over(g)){
    res = false;
  }
  printf(res ? "INFO:  test_setup_new_game_ext : success\n" : "ERROR: test_setup_new_game_ext failed\n");
  delete_game(g);
  return res;
}

bool test_game_dimensions(){
  bool res = true;
  game g = new_game_ext(5,6);
  assert(g);
  if (g -> width < 0 || g -> height < 0){
    res = false;
  }
  if(g -> width != 5 || g -> height != 6){
    res = false;
  }
  printf(res ? "INFO : test_game_dimensions : success\n" : "ERROR: test_game_dimensions Failed\n");
  delete_game(g);
  return res;
}

int main(void){
  bool result = true;

  result = test_get_content() && result;
  result = test_add_mirror_ext() && result;
  result = test_set_required_nb_seen() && result;
  result = test_set_required_nb_monsters() && result;
  result = test_restart_game() && result;
  result = test_delete_game() && result;
  result = test_new_game_ext() && result;
  result = test_add_monster() && result;
  result = test_current_nb_monster() && result;

  result = test_current_nb_seen() && result;
  result = test_current_nb_seen_advanced() && result;

  result = test_is_game_over() && result;
  result = test_copy_game() && result;
  result = test_setup_new_game_ext() && result;
  result = test_game_dimensions() && result;

  if(result){
      printf("\nINFO:  All tests successfull\n\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("\nINFO:  A test failed\n\n");
      return EXIT_FAILURE;
  }
}
