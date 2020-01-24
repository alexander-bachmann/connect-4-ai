#ifndef GAME_HPP
#define GAME_HPP

//#include "humanplayer.hpp"
//#include "aiplayer.hpp"
#include <iostream>
#include <string>
#include <vector>

class Game
{
  public:
    Game(int, int);
    void generate_board(); //initialize empty board
    void print_board(); //prints ASCII board
    void print_int_board(); //prints actual vector[][] values
    bool game_over(); //checks if winning board state has been reached
    void add_disk_to_column(int); //int - column number to drop disk in
    bool check_vertical_win(int);
    bool check_horizontal_win(int);
    bool check_diagonal_win(int);
    bool check_all_wins(int);

  private:
    int n; //row and column length
    int m; //number on consectutive disks needed to achieve victory
    int i; //i of most recent disk
    int num_disks; //number of disks that have been played (used to stop game if no winner)
    bool player_one_turn; //rotation of turns
    std::vector<std::vector<int>> game_board;
    void set_n(int); //includes validation
    void set_m(int); //includes validation
};

#endif
