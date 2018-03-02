#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"


//A winning board generation function
void generate(game g){

	set_required_nb_monsters (g, ZOMBIE,	5);
	set_required_nb_monsters (g, GHOST, 2);
	set_required_nb_monsters (g, SPIRIT, 0);
	set_required_nb_monsters (g, VAMPIRE,	2);

	add_mirror_ext(g,ANTIMIRROR,0,0);
	add_mirror_ext(g,ANTIMIRROR,0,2);
	add_mirror_ext(g,ANTIMIRROR,0,3);
	add_mirror_ext(g,ANTIMIRROR,3,0);
	add_mirror_ext(g,ANTIMIRROR,2,1);

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

	add_monster(g,GHOST,	1,1);
	add_monster(g,GHOST,	2,0);
	add_monster(g,VAMPIRE,1,3);
	add_monster(g,VAMPIRE,2,3);
	add_monster(g,ZOMBIE, 0,1);
	add_monster(g,ZOMBIE, 1,0);
	add_monster(g,ZOMBIE, 1,2);
	add_monster(g,ZOMBIE, 2,2);
	add_monster(g,ZOMBIE, 3,2);
}


/*All functions test_add_monster : Test if the content of the cell correspond to what we chose to add*/

bool test_add_monster_ghost(){
	bool res = true;
	game g =new_game_ext(4,4);
	assert(g);
	add_monster(g,GHOST,2,2);

	//Test the content of the cell where the ghost should be
	if(get_content(g,2,2) != GHOST){
		res=false;
	}

	//Test if the cells where the ghost shouldn't be is not empty
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 2 && y != 2){
				if(get_content(g,x,y) != EMPTY){
					res=false;
				}
			}
		}
	}

	printf(res ? "INFO:	test_add_monster_ghost : \u2713\n" : "INFO:	test_add_monster_ghost \u2715\n");	//Display of the test results
	delete_game(g);
	return res;
}

bool test_add_monster_spirit(){
	bool res = true;
	game g =new_game_ext(4,4);
	assert(g);
	add_monster(g,SPIRIT,2,2);

	//Test the content of the cell where the spirit should be
	if(get_content(g,2,2) != SPIRIT){
		res=false;
	}

	//Test if the cells where the spirit shouldn't be is not empty
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 2 && y != 2){
				if(get_content(g,x,y) != EMPTY){
					res=false;
				}
			}
		}
	}

	int tmp =0;
	if(game_width(g) > game_height(g))
	tmp = game_height(g);
	else
	tmp = game_width(g);

	for(unsigned int dir = 0; dir < NB_DIR; dir++){
		for(unsigned int pos = 0; pos < tmp; pos++){
			if(current_nb_seen(g,dir,pos) != 0){
				res= false;
				break;
			}
		}
	}
	printf(res ? "INFO:	test_add_monster_spirit : \u2713\n" : "INFO:	test_add_monster_spirit \u2715\n");
	delete_game(g);
	return res;
}

bool test_add_monster_zombie(){
	bool res = true;
	game g =new_game_ext(4,4);
	assert(g);
	add_monster(g,ZOMBIE,2,2);

	//Test the content of the cell where the zombie should be
	if(get_content(g,2,2) != ZOMBIE){
		res = false;
	}

 //Test if the cells where the zombie shouldn't be is not empty
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 2 && y != 2){
				if(get_content(g,x,y) != EMPTY){
					res = false;
				}
			}

		}
	}


	printf(res ? "INFO:	test_add_monster_zombie : \u2713\n" : "INFO:	test_add_monster_zombie \u2715\n");
	delete_game(g);
	return res;
}

bool test_add_monster_vampire(){
	bool res = true;
	game g =new_game_ext(4,4);
	assert(g);
	add_monster(g,VAMPIRE,2,2);

	//Test the content of the cell where the spirit should be
	if(get_content(g,2,2) != VAMPIRE){
		res = false;
	}

	//Test if the cells where the zombie shouldn't be is not empty
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 2 && y != 2){
				if(get_content(g,x,y) != EMPTY){
					res = false;
				}
			}

		}
	}

	printf(res ? "INFO:	test_add_monster_vampire : \u2713\n" : "INFO:	test_add_monster_vampire \u2715\n");
	delete_game(g);
	return res;
}


bool test_add_monster(){
	bool res = true;
	res = test_add_monster_vampire() && res;
	res = test_add_monster_zombie() && res;
	res = test_add_monster_ghost() && res;
	res = test_add_monster_spirit() && res;

	game g =new_game_ext(4,4);

	//If add_monster_zombie/ghost/vampire return false
	if(res == false){
		res=false;	//No return because we want to display text at the end of the function
	}

	assert(g);
	add_monster(g,VAMPIRE,1,2);

	//Test the content of the cell where the monster should be
	if(get_content(g, 1, 2) != VAMPIRE){
		res=false;
	}
	assert(g);


	//Test if there's not another monster adding himself to the board when it should not have
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 1 || y != 2)
			if(get_content(g,x,y) != EMPTY){
				res=false;
			}
		}
	}

	printf(res ? "INFO:	test_add_monster : success\n" : "ERROR: test_add_monster failed\n");	//Display of the result of the test
	delete_game(g);
	return res;
}

//Test if the current number of monster correspond to what is on the board
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
	printf(res ? "INFO:	test_current_nb_monster : success\n" : "ERROR: test_current_nb_monster failed\n");	//Display of the results
	delete_game(g);
	return res;
}

bool test_current_nb_seen_advanced(){
	bool res = true;
	game g = new_game_ext(4,4);
	assert(g);
	generate(g);
	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			if(required_nb_seen(g,i,j) != current_nb_seen(g,i,j)){

				res=false;
			}
		}
	}
	printf(res ? "INFO:	test_current_nb_seen_advanced : \u2713\n" : "INFO:	test_current_nb_seen_advanced \u2715\n");	 //Display of the results
	delete_game(g);
	return res;
}


bool test_current_nb_seen(){
	bool res=true;
	if(!res){
		//TMP TO DEBUG LINTER
	}
	res = test_current_nb_seen_advanced();
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

	printf(res ? "INFO:	test_current_nb_seen : success\n" : "ERROR: test_current_nb_seen failed\n");	//Display of the results
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
	printf(res ? "INFO:	test_new_game_advanced : \u2713\n" : "INFO:	test_new_game_advanced \u2715\n");	 //Display of the results
	delete_game(g);
	return res;
}

bool test_new_game_ext(){
	bool res = true;
	res = test_new_game_advanced() && res;
	game g= new_game_ext(4,4);
	assert(g);
	if(g == NULL){
		res=false;
	}
	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			if(get_content(g, i, j) != EMPTY){
				res=false;
			}
		}
	}

	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			if(required_nb_seen(g, j, i) != 0){
				res=false;
			}
		}
	}

	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			if( current_nb_seen(g,i,j) != 0){
				res=false;
			}
		}
	}

	printf(res ? "INFO:	test_new_game_ext : success\n" : "ERROR: test_new_game_ext failed\n");	 //Display of the results
	delete_game(g);
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
	printf(res ? "INFO:	test_delete_game_advanced : \u2713\n" : "INFO:	test_delete_game_advanced \u2715\n");	 //Display of the results
	return res;
}

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
	//check current nb seen etc
	add_monster(g,ZOMBIE,0,0);
	add_monster(g,GHOST,0,1);
	add_monster(g,VAMPIRE,0,2);
	sum = current_nb_seen(g,S,0)+current_nb_seen(g,S,1)+current_nb_seen(g,S,2);
	if(sum != 2){
		res=false;
	}
	printf(res ? "INFO:	test_delete_game : success\n" : "ERROR: test_delete_game failed\n");	 //Display of the results
	assert(g);
	delete_game(g);
	assert(g);
	return res;
}

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
	printf(res ? "INFO:	test_get_content : success\n" : "ERROR: test_get_content failed\n");	 //Display of the results
	delete_game(g);
	return res;
}


bool test_add_vmirror(){
	bool res=true;
	game g = new_game_ext(4,4);
	assert(g);
	add_mirror_ext(g, VMIRROR, 1, 2);
	if(get_content(g, 1, 2) != VMIRROR) {
		assert(g);
		res=false;
	}

	add_monster(g,GHOST,1,3);

	if(current_nb_seen(g,S,1) != 1){
		res = false;
	}

	delete_game(g);
	assert(g);
	printf(res ? "INFO:	test_add_vmirror : \u2713\n" : "INFO:	test_add_vmirror \u2715\n");	 //Display of the results
	return res;
}



bool test_add_hmirror(){
	bool res=true;
	game g = new_game_ext(4,4);
	assert(g);
	add_mirror_ext(g, HMIRROR, 1, 2);
	if(get_content(g, 1, 2) != HMIRROR) {
		assert(g);
		res=false;
	}

	add_monster(g,GHOST,1,3);

	if(current_nb_seen(g,S,1) != 0){
		res = false;
	}
	if(current_nb_seen(g,N,1) != 1){
		res = false;
	}

	delete_game(g);
	assert(g);
	printf(res ? "INFO:	test_add_hmirror : \u2713\n" : "INFO:	test_add_hmirror \u2715\n");	 //Display of the results
	return res;
}


bool test_add_mirror_ext(){
	bool res=true;
	res = test_add_vmirror() && test_add_hmirror() && res;
	game g = new_game_ext(4,4);
	assert(g);
	add_mirror_ext(g, MIRROR, 1, 2);
	if(get_content(g, 1, 2) != MIRROR) {
		assert(g);
		res=false;
	}
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
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
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x != 1 && y != 2){
				if(get_content(g,x,y) != EMPTY){
					assert(g);
					res=false;
				}
			}
		}
	}
	printf(res ? "INFO:	test_add_mirror : success\n" : "ERROR: test_add_mirror failed\n");	 //Display of the results
	delete_game(g);
	assert(g);
	return res;
}

// Test if the required nb seen are correctly set on the board
bool test_set_required_nb_seen(){
	bool res = true;
	game g = new_game_ext(4,4);
	assert(g);
	set_required_nb_seen( g , N , 0 , 1);
	if(required_nb_seen(g,N,0) != 1){
		assert(g);
		res=false;
	}
	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
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
	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			set_required_nb_seen( g , j , i , i );
		}
	}
	for(unsigned int i = 0; i < game_width(g); i++){
		for(unsigned int j = 0; j < game_height(g); j++){
			int tmp = required_nb_seen( g , j , i );
			if(tmp != i){
				assert(g);
				res=false;
			}
		}
	}
	printf(res ? "INFO:	test_set_required_nb_seen : success\n" : "ERROR: test_set_required_nb_seen failed\n");	 //Display of the results
	delete_game(g);
	assert(g);
	return res;
}


bool test_set_required_nb_monsters(){
	bool res = true;
	game g = new_game_ext(4,4);
	assert(g);
	set_required_nb_monsters(g, ZOMBIE, 2);
	if(required_nb_monsters(g, ZOMBIE) != 2){
		res=false;
	}
	printf(res ? "INFO:	test_set_required_nb_monsters : success\n" : "ERROR: test_set_required_nb_monsters failed\n");	//Display of the results
	delete_game(g);
	assert(g);
	return res;
}


// Test if the game restart well, if the board is clean and the display of numbers ok
bool test_restart_game(){
	bool res = true;
	int sum = 0;
	game g = new_game_ext(4,4);
	assert(g);

	int requiredNbMonsters[] = {required_nb_monsters(g,ZOMBIE),required_nb_monsters(g,GHOST),required_nb_monsters(g,VAMPIRE),required_nb_monsters(g,SPIRIT)};

	sum = current_nb_monsters(g, VAMPIRE);
	sum += current_nb_monsters(g, GHOST);
	sum += current_nb_monsters(g, ZOMBIE);
	restart_game(g);
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(get_content(g,x,y) != EMPTY){
				res=false;
			}
		}
	}
	if(required_nb_monsters(g,ZOMBIE) != requiredNbMonsters[0] || required_nb_monsters(g,GHOST) != requiredNbMonsters[1]
				|| required_nb_monsters(g,VAMPIRE) != requiredNbMonsters[2] || required_nb_monsters(g,SPIRIT) != requiredNbMonsters[3]){
					res = false;
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
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
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
	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(x !=1 && y !=2)
			if(get_content(g,x,y) != EMPTY){
				res=false;
			}
		}
	}


	printf(res ? "INFO:	test_restart_game : success\n" : "ERROR: test_restart_game failed\n");	//Display of the results
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
	printf(res ? "INFO:	test_is_game_over : success\n" : "ERROR: test_is_game_over failed\n");	//Display of the results
	delete_game(g);
	return res;
}

bool test_copy_game(){
	bool res = true;
	game g = new_game_ext(4,4);
	game g1 = copy_game(g);

	for(unsigned int x = 0; x < game_width(g); x++){
		for(unsigned int y = 0; y < game_height(g); y++){
			if(get_content(g1,x,y) != get_content(g, x, y)){
				res=false;
			}
		}
	}
	printf(res ? "INFO:	test_copy_game : success\n" : "ERROR: test_copy_game failed\n");	//Display of the results
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
	printf(res ? "INFO:	test_setup_new_game_ext : success\n" : "ERROR: test_setup_new_game_ext failed\n");	//Display of the results
	delete_game(g);
	return res;
}

//Test if the dimensions of the game created correspond to what we chose
bool test_game_dimensions(){
	bool res = true;
	game g = new_game_ext(5,6);
	assert(g);
	if (game_width(g) < 0 || game_height(g) < 0){
		res = false;
	}
	if(game_width(g) != 5 || game_height(g) != 6){
		res = false;
	}
	printf(res ? "INFO:	test_game_dimensions : success\n" : "ERROR: test_game_dimensions failed\n");	//Display of the results
	delete_game(g);
	return res;
}

int main(void){
	bool result = true;

	result = test_get_content() && result;

	result = test_set_required_nb_seen() && result;
	result = test_set_required_nb_monsters() && result;


	result = test_add_monster() && result;
	result = test_add_mirror_ext() && result;

	result = test_current_nb_monster() && result;
	result = test_current_nb_seen() && result;
	result = test_is_game_over() && result;

	result = test_copy_game() && result;
	result = test_restart_game() && result;
	result = test_delete_game() && result;

	result = test_new_game_ext() && result;
	result = test_setup_new_game_ext() && result;

	result = test_game_dimensions() && result;

	if(result){
		printf("\nINFO:	All tests successfull\n\n");	//Display of the results
		return EXIT_SUCCESS;
	}
	else{
		printf("\nINFO:	A test failed\n\n");	//Display of the results
		return EXIT_FAILURE;
	}
}
