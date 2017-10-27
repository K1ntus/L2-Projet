#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"
#include <time.h>   // pour rand 

#define COLONNE 4
#define LINE 4

/*
Vérifier la hauter/largeur du jeu généré
*/

bool test_add_monster(){
  bool res = true;
  game g =new_game();
  assert(g);
  add_monster(g,VAMPIRE,1,2);
  if(get_content(g, 1, 2) != VAMPIRE){
    fprintf(stderr,("ERROR: Basic test on test_add_monster failed\n"));
    delete_game(g);
    return false;
  }
  assert(g);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 1 || y != 2)
      if(get_content(g,x,y) != EMPTY){
        fprintf(stderr,("ERROR: Basic test on test_add_monster failed\n"));
        delete_game(g);
        return false;
      }
    }
  }
  printf("INFO: test_add_monster : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}


bool test_add_monster_ghost(){
  bool res = true;
  game g =new_game();
  assert(g);
  add_monster(g,GHOST,2,2);
  if(get_content(g,2,2) != GHOST){
    fprintf(stderr,("ERROR: Basic test on test_add_monster_ghost failed\n"));
    delete_game(g);
    return false;    
  }
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          fprintf(stderr,("ERROR: Basic test on test_add_monster_ghost failed\n"));
          delete_game(g);
          return false;    
        }
      }
    }
  }
  printf("INFO: test_add_monster_ghost : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;
}

bool test_add_monster_zombie(){
  bool res = true;
  game g =new_game();
  assert(g);
  add_monster(g,ZOMBIE,2,2);
  if(get_content(g,2,2) != ZOMBIE){
    fprintf(stderr, "ERROR: Basic test on test_add_monster_zombie failed\n");
    delete_game(g);
    return false;    
  }
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          fprintf(stderr, "ERROR: Basic test on test_add_monster_zombie failed\n");
          delete_game(g);
          return false;    
        }
      }
    }
  }
  printf("INFO: test_add_monster_zombie : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;
}

bool test_add_monster_vampire(){
  bool res = true;
  game g =new_game();
  assert(g);
  add_monster(g,VAMPIRE,2,2);
  if(get_content(g,2,2) != VAMPIRE){
    fprintf(stderr, "ERROR: Basic test on test_add_monster_vampire failed\n");
    delete_game(g);
    return false;    
  }
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 2 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          fprintf(stderr, "ERROR: Basic test on test_add_monster_vampire failed\n");
          delete_game(g);
          return false;    
        }
      }
    }
  }
  printf("INFO: test_add_monster_vampire : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;
}


bool test_current_nb_monster(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, GHOST, 1, 1);
  add_monster(g, ZOMBIE, 1, 1);
  add_monster(g, ZOMBIE, 1, 2);
  add_monster(g, VAMPIRE, 1, 2);
  add_monster(g, VAMPIRE, 0, 3);
  add_monster(g, GHOST, 0, 3);
  assert(g);
  if(current_nb_monsters(g,GHOST)!=1 || current_nb_monsters(g,ZOMBIE)!=1 || current_nb_monsters(g,VAMPIRE)!=1){
    fprintf(stderr, "ERROR: Basic test on current_nb_monster failed\n");
    delete_game(g);
    return false; 
  }

  restart_game(g);

  add_monster(g, GHOST, 1, 1);
  if(current_nb_monsters(g, GHOST) != 1){
    fprintf(stderr, "Basic test on current_nb_monster failed\n");
    delete_game(g);
    return false; 
  }

  restart_game(g);

  add_monster(g, ZOMBIE, 1, 1);
  if(current_nb_monsters(g,ZOMBIE) != 1){
    fprintf(stderr, "Basic test on current_nb_monster failed\n");
    delete_game(g);
    return false; 
  }

  add_monster(g, VAMPIRE, 1, 1);
  if(current_nb_monsters(g,VAMPIRE) != 1){
    fprintf(stderr, "Basic test on current_nb_monster failed\n");
    delete_game(g);
    return false; 
  }

  printf("INFO: test_current_nb_monster: ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;


}
//int current_nb_seen (cgame  game , direction  side , int  pos);
//void set_required_nb_seen(game game, direction side, int pos, int value);
bool test_current_nb_seen(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, VAMPIRE, 1, 0);
  add_monster(g, ZOMBIE, 2, 0);
  add_monster(g, GHOST, 3, 0);
  if(current_nb_seen(g,S,1)!=1){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  if(current_nb_seen(g,S,2)!=1){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  if(current_nb_seen(g,S,3)!=0){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  restart_game(g);
  add_mirror(g,1,0,0);
  if(current_nb_seen(g,S,0)!=0){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  restart_game(g);
  add_mirror(g,0,0,0);
  if(current_nb_seen(g,S,0)!=0){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  add_monster(g, VAMPIRE, 1, 0);
  add_monster(g, ZOMBIE, 2, 0);
  add_monster(g, GHOST, 3, 0);
  if(current_nb_seen(g,S,0)!=2){
    fprintf(stderr, "ERROR: Basic test on test_current_nb_seen failed\n");
    delete_game(g);
    return false; 
  }
  printf("INFO: test_current_nb_seen : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;

}

//game new_game();
bool test_new_game(){
  bool res = true;
  game g= new_game();
  assert(g);
  if(g == NULL){
    fprintf(stderr,("ERROR: Basic test on test_new_game failed\n"));
    delete_game(g);
    return false;       
  }
  //assert(get_content(g, 5, 5));
  for(unsigned int i = 0; i < COLONNE; i++){
    for(unsigned int j = 0; j < LINE; j++){
      if(get_content(g, i, j) != EMPTY){
        fprintf(stderr,("ERROR: Basic test on test_new_game failed\n"));
        delete_game(g);
        return false;            
      }
    }
  }

  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(required_nb_seen( g , j , i ) != 0){
        fprintf(stderr,("ERROR: Basic test on test_new_game failed\n"));
        delete_game(g);
        return false;     
      }
    }
  }

  printf("INFO: test_new_game : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;
}

//void delete_game (game g);
bool test_delete_game(){
  bool res=true;
  game g = new_game();
  assert(g);
  delete_game(g);
  g = new_game();

  add_monster(g, VAMPIRE, 0, 1);
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);

  if(sum != 1){
      fprintf(stderr,("ERROR: Basic test on test_delete_game failed\n"));
        delete_game(g);
        return false;    
  }

  assert(g);  
  add_monster(g, GHOST, 0, 2);
  assert(g);
  printf("INFO: test_delete_game : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

//content get_content(cgame game, int col, int line);
bool test_get_content(){
  bool res=true;
  game g = new_game();
  assert(g);
  add_monster(g, GHOST, 0, 1);
  add_monster(g, VAMPIRE, 0, 2);
  add_monster(g, ZOMBIE, 0, 3);
  assert(g);
  if(get_content(g, 0, 1) != GHOST){
      fprintf(stderr,("ERROR: Basic test on get_content failed\n"));
        delete_game(g);
        return false; 
  }
  if(get_content(g, 0, 2) != VAMPIRE){
      fprintf(stderr,("ERROR: Basic test on get_content failed\n"));
        delete_game(g);
        return false; 
  }
  if(get_content(g, 0, 3) != ZOMBIE ) {
      fprintf(stderr,("ERROR: Basic test on get_content failed\n"));
        delete_game(g);
        return false; 
  }
  if(get_content(g, 1, 0) != EMPTY || get_content(g, 2, 0) != EMPTY || get_content(g, 3, 0) != EMPTY ) {
      fprintf(stderr,("ERROR: Basic test on get_content failed\n"));
        delete_game(g);
        return false; 
  }
  int sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  assert(g);
  if(sum != 3){
    fprintf(stderr,("ERROR: Basic test on test_get_content failed\n"));
    delete_game(g);
    return false;
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
        delete_game(g);
        return false;    
  }
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 1 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          fprintf(stderr,("ERROR: Basic test on test_add_mirror failed\n"));
          delete_game(g);
          return false;    
        }
      }
    }
  }

  //TEST ANTIMIRROR
  restart_game(g);
  add_mirror(g, 1, 1, 2);
  if(get_content(g, 1, 2) != ANTIMIRROR) {
    fprintf(stderr,"ERROR: Basic test on add_mirror failed\n");
    delete_game(g);
    return false;    
  }
  for(unsigned int x = 0; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(x != 1 && y != 2){
        if(get_content(g,x,y) != EMPTY){
          fprintf(stderr,("ERROR: Basic test on test_add_mirror failed\n"));
          delete_game(g);
          return false;    
        }
      }
    }
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

//TEST 1

  assert(g);
  set_required_nb_seen( g , N , 0 , 1);
  if(required_nb_seen(g,N,0) != 1){
    fprintf(stderr,("ERROR: Basic test on test_current_nb_seen failed\n"));
    delete_game(g);
    return false; 
  }
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(j != 0 && i != 1){
        if(required_nb_seen(g ,j , i) != 0){
          delete_game(g); 
          return false;
        }
      }
    }
  }
  restart_game(g);

//TEST 2

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
        fprintf(stderr,("ERROR: Basic test on test_current_nb_seen failed\n"));
        delete_game(g);
        return false;         
      }
    }
  }
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
        delete_game(g);
        return false;    
  }
  printf("INFO: test_set_required_nb_monsters : ");
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
  int sum = 0;
  game g = new_game();
  assert(g);

  for(unsigned int x = 1; x < COLONNE; x++){
    for(unsigned int y = 0; y < LINE; y++){
      if(get_content(g,x,y) != EMPTY){
        fprintf(stderr,("ERROR: Basic test on test_restart_game failed\n"));
        delete_game(g);
        return false;
      }
    }
  }
  sum = current_nb_monsters(g, VAMPIRE);
  sum += current_nb_monsters(g, GHOST);
  sum += current_nb_monsters(g, ZOMBIE);
  restart_game(g);
  if(g == NULL){
    fprintf(stderr, "Basic test on test_restart_game failed\n");
    delete_game(g);
    return false; 
    
  }
  if(sum != 0){
      fprintf(stderr,("ERROR: Basic test on test_restart_game failed\n"));
      delete_game(g);
      return false; 
    }
  printf("INFO: test_restart_game : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return res;
}

bool test_current_nb_seen_advanced(){
  bool res = true;
  game g = new_game();
  assert(g);
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

//AntiMirror
  add_mirror(g,1,0,0);
  add_mirror(g,1,0,2);
  add_mirror(g,1,0,3);
  add_mirror(g,1,3,0);
  add_mirror(g,1,2,1);
//Mirror
  add_mirror(g,0,3,3);
  add_mirror(g,0,3,1);

//  add_monster(g,VAMPIRE,2,2);
 add_monster(g,GHOST, 1, 1);
 add_monster(g,GHOST, 2, 0);
 add_monster(g,VAMPIRE,1,3);
 add_monster(g,VAMPIRE,2,3);
 add_monster(g,ZOMBIE, 0,1);
 add_monster(g,ZOMBIE, 1,0);
 add_monster(g,ZOMBIE, 1,2);
 add_monster(g,ZOMBIE, 2,2);
 add_monster(g,ZOMBIE, 3,2);

  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0; j < 4; j++){
      if(required_nb_seen(g,i,j) != current_nb_seen(g,i,j)){
        fprintf(stderr,("ERROR: Basic test on test_current_nb_seen_advanced failed\n"));
        delete_game(g);
        return false;            
      }
    }
  }
  printf("INFO: test_current_nb_seen_advanced : ");
  printf(res ? "true\n" : "false\n");
  delete_game(g);
  return true;
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
  result = test_add_monster() && result;
  result = test_add_monster_vampire() && result;
  result = test_add_monster_ghost() && result;
  result = test_add_monster_zombie() && result;
  result = test_current_nb_monster() && result;
  result = test_current_nb_seen() && result;
  result = test_current_nb_seen_advanced() && result;
  
  if(result){
      printf("\nINFO: All tests successfull\n\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("\nINFO: A test failed\n\n");
      return EXIT_FAILURE;
  }
}
