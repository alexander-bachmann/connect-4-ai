/*
create tree for game state - tree is rebuilt after each move
tree is generated by placing a tile in all possible slots

maybe may tree all nodes just ints - indicating the number of possible winning paths
  node(int depth, vector game_board, ....), pass the game_board down through the tree.. USE THE SAME GAME_STATE VECTOR


every node will have n children
make move in vector then revert moves as the tree is traversed back upwards

each layer of depth does the same thing
board_state 4 x 4 board
  - 4 game states - 1 state for each tile selected - (turn 1)
    - 4 * 4 game states - 4 options for each possible choices from turn 1 - (turn 2)
      - 4 * 4 * 4 game states
        - etc

must decide how deep - only moving a few levels down in the game tree would be faster but likely will result in a weaker move than if allowed to explore for a longer period of time

a < b - no pruning

*/


/*

TO DO

create a general tree structure to simply hold the evaluation int's

void generate_tree(depth) - depth determines the size and number of children for the tree
  given board dimension aka n = 4, and depth = 3
    current game_board will have 4 children, those children will each have 4 children, and those children will each have 4 children

    meaning that there will be at most 4 * 4 * 4 = 64 game_boards that need to be analyzed

initial call: minimax(game_board, 3, true) //make a decision looking 3 turns in the future based off current game_board, and it's true that it is AI's turn when minimax is called
*/

#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "game.hpp"


#include <vector>
#include <iostream>
#include <cmath>

struct Node
{
  int eval;
  std::vector<Node*> child;
};

class AIPlayer
{
  public:

    AIPlayer();
    AIPlayer(Game* game, int disk_num); //disk_num X's = 1, O's = 2

    int heuristic_evaluation(std::vector<std::vector<int>>); //game_board
    int count_num_vertical_wins(int);
    int count_num_horizontal_wins(int);
    int count_num_diagonal_wins(int);

    int min(int, int);
    int max(int, int);
    int minimax(std::vector<std::vector<int>>, int, bool); //game_board, depth, maximizing_player -- add alpha and beta too

    void take_turn();

    // Node* new_node(int);
    // void generate_children(Node*, int);
    // void generate_tree(int);



  private:
    Game* game;
    int disk_num;
    int opponent_disk_num;

};

#endif
