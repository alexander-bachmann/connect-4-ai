#ifndef GAME_HPP
#define GAME_HPP

//#include "humanplayer.hpp"
//#include "aiplayer.hpp"
#include <iostream>
#include <string>
#include <vector>
//include string stream?

class Game
{
  public:
    Game(int, int);
    void generate_board(); //initialize empty board
    void print_board(); //prints board state after each turn
    bool game_over(); //checks if winning board state has been reached
    void add_disk_to_column(int); //int - column number to drop disk in

  private:
    int n; //row and column length
    int m; //number on consectutive disks needed to achieve victory
    int num_disks; //number of disks that have been played (used to stop game if no winner)
    bool player_one_turn; //rotation of turns
    std::vector<std::vector<std::string>> game_board;
};

#endif
