#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "game.c"


typedef enum e_undead_solve {FIND_NONE, FIND_ONE, NB_SOL, FIND_ALL} e_solver;


//Display an empty line
void display_empty_line(game g){
		printf("|     ");
		for(int i=0; i<game_width(g) ; i++){
			printf("  ");
		}
		printf("      |\n");
}

//Display the numbers of monsters to place in top of the board
void display_required_nb_monsters(game g){
	if (game_width(g) <= 4){
		printf("|  Z:%d V:%d G:%d S:%d  |\n",
		required_nb_monsters(g, ZOMBIE),
		required_nb_monsters(g, VAMPIRE),
		required_nb_monsters(g, GHOST),
		required_nb_monsters(g, SPIRIT));
	}else{
		printf("|  ");
		int spaces = (game_width(g) + game_width(g) - 11)/2;   //Calculate the number of spaces to display (in each side of the text)
		for(int i=0; i<spaces; i++){													 //In order to center the text
			printf(" ");
		}
		printf(" Z:%d V:%d G:%d S:%d ",
		required_nb_monsters(g, ZOMBIE),
		required_nb_monsters(g, VAMPIRE),
		required_nb_monsters(g, GHOST),
		required_nb_monsters(g, SPIRIT));

		for(int i=0; i<spaces+1; i++){
			printf(" ");
		}
		printf("   |\n");
	}
}

void display_required_nb_seen_north(game g){
	printf("|      ");
	for(int i=0; i<game_width(g) ; i++){
		printf("%d ",required_nb_seen(g, N, i));
	}
	printf("     |\n");
}

void display_cellsContent_and_sideValues(game g){
	int tick_content;
	for(int x = game_height(g)-1; x >= 0; x--){
		//Left & right side of the board
		printf("|   %d  ", required_nb_seen(g, W, x));
		for(int y = 0; y < game_width(g) ; y++){
			tick_content = get_content(g,y,x);

			//Graphic show of cells content
			switch(tick_content){
				case EMPTY:
					printf("  ");
					break;
				case MIRROR:
					printf("/ ");
					break;
				case ANTIMIRROR:
					printf("\\ ");
					break;
				case VMIRROR:
					printf("| ");
					break;
				case HMIRROR:
					printf("_ ");
					break;
				case SPIRIT:
					printf("S ");
					break;
				case ZOMBIE:
					printf("Z ");
					break;
				case GHOST:
					printf("G ");
					break;
				case VAMPIRE:
					printf("V ");
					break;
			}
		}
//Right side && number of monsters to be seen
	printf(" %d   |\n",required_nb_seen (g, E, x));
	}
}

void display_required_nb_seen_south(game g){
		printf("|      ");
		for(int i=0; i<game_width(g) ; i++){
			printf("%d ",required_nb_seen(g, S, i));
		}
		printf("     |\n");
}

void display_start(game g){
	if (game_width(g) <= 4){
		printf("|       start       |");
	}else{
		printf("|  ");
		int spaces = game_width(g) + (game_width(g)-1) - 8;  //Give the number of space to add before and after the text
		for(int i = 0; i<spaces/2; i++){//Divided by 2 for left side
			printf(" ");
		}
		printf("     start      ");

		for(int i=0; i<spaces/2 + 1; i++){//Divided by 2 for the right side
			printf(" ");
		}
		printf("  |\n");
	}
}

//Calls each functions created to display all the element of the game board
void display(game g){
		display_required_nb_monsters(g);
		display_empty_line(g);

		display_required_nb_seen_north(g);
		display_empty_line(g);

		display_cellsContent_and_sideValues(g);
		display_empty_line(g);

		display_required_nb_seen_south(g);
		display_empty_line(g);
		display_empty_line(g);

		display_start(g);
		printf("\n\n");
}

/**
	*	0	NORTH
	*	1	SOUTH
	*	2	EAST
	*	3	WEST
**/
bool ** init_array(game g){
 bool **res  = (bool **)malloc(sizeof(bool *) * NB_DIR);
 assert(res);
 bool *north = (bool *)malloc(sizeof(bool) * game_height(g));
 assert(north);
 bool *south = (bool *)malloc(sizeof(bool) * game_height(g));
 assert(south);
 bool *east = (bool *)malloc(sizeof(bool) * game_width(g));
 assert(east);
 bool *west = (bool *)malloc(sizeof(bool) * game_width(g));
 assert(west);
 res[0] = north;
 res[1] = south;
 res[2] = east;
 res[3] = west;

 return res;
}



//Creation of a new map containing the new monster
void generate(game g, int * nbMonsters){
	set_required_nb_monsters (g, ZOMBIE,  nbMonsters[2]);
	set_required_nb_monsters (g, GHOST,  nbMonsters[1]);
	set_required_nb_monsters (g, VAMPIRE,  nbMonsters[0]);
	set_required_nb_monsters (g, SPIRIT,  nbMonsters[3]);

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
}
















bool this_side_and_pos_see_this_cell (game g, direction d, int cell_pos,int side_pos){
  bool res = true;
  game g2 = copy_game(g);
  restart_game(g2);
  int x = cell_pos%game_width(g2);
  int y = cell_pos/game_height(g2);

  add_monster(g, ZOMBIE,x,y);

  if(current_nb_seen(g, d, side_pos) == 0)
    res = false;

  delete_game(g2);
  return res;
}

bool is_cell_after_mirror(game g, direction d, int cell_pos, int side_pos){
  bool res = true;
  if(!this_side_and_pos_see_this_cell(g, d, cell_pos, side_pos)){
    return false;
  }

  game g2 = copy_game(g);
  restart_game(g2);
  int x = cell_pos%game_width(g2);
  int y = cell_pos/game_height(g2);

  add_monster(g, GHOST,x,y);

  if(current_nb_seen(g, d, side_pos) == 0)
    res = false;

  delete_game(g2);
  return res;
}

int substract_currentNbSeen_and_requiredNbSeen(game g, direction d, int side_pos){
  int res = required_nb_seen(g,d,side_pos) - current_nb_seen(g, d, side_pos);

  return res;
}



struct s_solverUtility{
  direction d;
  int pos;
  int value; //requiredNbSeen - currentNbSeen
  bool see_this_cell;
  bool cell_after_mirror;
};
typedef struct s_solverUtility s_solverUtility;


struct s_monster_to_place{
  int vote_for_zombies;
  int vote_for_ghosts;
  int vote_for_vampires;
  int vote_for_spirits;
};
typedef struct s_monster_to_place s_monster_to_place;

//ZOMBIE VAMPIRE GHOST SPIRIT
struct s_priority_placement{
  content mobType;
  int priorityValue;
};
typedef struct s_priority_placement s_priority_placement;












s_solverUtility * solverUtility_alloc(game g){
  s_solverUtility * res = malloc(sizeof(direction) * ((game_width(g)+game_height(g))*2)
                                                  + (sizeof(int)* ((game_width(g)+game_height(g))*2))
                                                  + (sizeof(int)* ((game_width(g)+game_height(g))*2))
                                                  + (sizeof(bool)* ((game_width(g)+game_height(g))*2))
                                                  + (sizeof(bool)* ((game_width(g)+game_height(g))*2))
                                                  + (sizeof(s_solverUtility))
                                                  );
  return res;

}


int add_struct_to_solver_array(s_solverUtility * res, s_solverUtility toAdd, int pos){
  res[pos] = toAdd;
  return pos+=1;
}


s_priority_placement* monster_to_place_init(){
  s_priority_placement * res = malloc(sizeof(s_priority_placement*) *4);
  res[0].mobType = ZOMBIE;
  res[1].mobType = VAMPIRE;
  res[2].mobType = GHOST;
  res[3].mobType = SPIRIT;

  return res;
}

void the_solverUtility_filler(game g, s_solverUtility res, int cell_pos, s_solverUtility * array){
  //int x = cell_pos%game_width(g);
  //int y = cell_pos/game_height(g);

  int sum = 0;
  for(unsigned int i = 0; i < game_width(g); i++){
    if(this_side_and_pos_see_this_cell(g,N, cell_pos, i)){
      res.see_this_cell = true;
      res.pos = i;
      res.value = substract_currentNbSeen_and_requiredNbSeen(g,N,i);
      res.cell_after_mirror = is_cell_after_mirror(g,N,cell_pos,i);
      res.d = N;
      sum = add_struct_to_solver_array(array, res, sum);
    }
    if(this_side_and_pos_see_this_cell(g,S, cell_pos, i)){
      res.see_this_cell = true;
      res.pos = i;
      res.value = substract_currentNbSeen_and_requiredNbSeen(g,S,i);
      res.cell_after_mirror = is_cell_after_mirror(g,S,cell_pos,i);
      res.d = S;
      sum = add_struct_to_solver_array(array, res, sum);
    }
  }


  for(unsigned int i = 0; i < game_height(g); i++){
    if(this_side_and_pos_see_this_cell(g,E, cell_pos, i)){
      res.see_this_cell = true;
      res.pos = i;
      res.value = substract_currentNbSeen_and_requiredNbSeen(g,E,i);
      res.cell_after_mirror = is_cell_after_mirror(g,E,cell_pos,i);
      res.d = E;
      sum = add_struct_to_solver_array(array, res, sum);
    }
    if(this_side_and_pos_see_this_cell(g,W, cell_pos, i)){
      res.see_this_cell = true;
      res.pos = i;
      res.value = substract_currentNbSeen_and_requiredNbSeen(g,W,i);
      res.cell_after_mirror = is_cell_after_mirror(g,W,cell_pos,i);
      res.d = W;
      sum = add_struct_to_solver_array(array, res, sum);
    }
  }

    return;
}

int max (int a, int b){
  if (a > b){
    return a;
  }
  return b;
}


int getMaximumVoteForAMonster(s_monster_to_place s_monster){
  int maximum = max(s_monster.vote_for_ghosts, max(s_monster.vote_for_zombies, max(s_monster.vote_for_spirits, s_monster.vote_for_vampires)));
  printf("Le maximum de vote pour un monstre est :%d\n",maximum);
	return maximum;
}

content which_mstr_have_a_lot_of_votes(s_monster_to_place res){
  int maximum = getMaximumVoteForAMonster(res);
  int spirit = res.vote_for_spirits, vampire = res.vote_for_vampires, ghost = res.vote_for_ghosts, zombie = res.vote_for_zombies;

	printf("%d; %d; %d; %d\n", spirit, vampire, ghost, zombie);
	printf("%d will be placed!\n", maximum);
  if(maximum == spirit){
    return SPIRIT;
  }else if (maximum == vampire){
    return VAMPIRE;
  }else if (maximum == ghost){
    return GHOST;
  }else if (maximum == zombie){
    return ZOMBIE;
  }
  return EMPTY;
}


s_priority_placement *voting_to_choose_a_mob(game g, s_solverUtility* s_array){

  s_priority_placement * res = monster_to_place_init();

  int s_size =  sizeof(s_array)/sizeof(s_solverUtility*);

  for(unsigned int i = 0; i < s_size; i++){
    if(s_array[i].value > 0)
      if(s_array[i].cell_after_mirror)
        res[2].priorityValue +=2;
        res[0].priorityValue +=1;
    if(s_array[i].value > 0)
      if(!s_array[i].cell_after_mirror)
        res[1].priorityValue +=2;
        res[0].priorityValue +=1;

    if(s_array[i].value == 0)
      if(s_array[i].cell_after_mirror)
        res[2].priorityValue +=2;
        res[3].priorityValue +=1;
    if(s_array[i].value == 0)
      if(!s_array[i].cell_after_mirror)
        res[1].priorityValue +=2;
        res[3].priorityValue +=1;
  }

  return res;
}
