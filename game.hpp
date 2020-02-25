#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>

class Game
{
  public:
    Game();
    Game(int, int);
    void generate_board();
    void print_board(); //prints ASCII board
    void print_int_board(); //prints actual vector[][] int values
    bool is_game_over();

    bool add_disk_to_column(int);
    void pop_from_column(int);

    bool check_vertical_win(int);
    bool check_horizontal_win(int);
    bool check_diagonal_win(int);
    bool check_all_wins(int);

    int get_n();
    int get_m();
    int get_winning_disk_num();

    std::vector<std::vector<int>> get_game_board();

  private:
    int n; //row and column length
    int m; //number on consectutive disks needed to achieve victory
    int i; //i of most recent disk
    int num_disks; //number of disks that have been played (used to stop game if no winner)
    bool player_one_turn; //rotation of turns
    bool game_over;

    int winning_disk_num = 0;
    /*
      -1 = board has been filled with no winners
      0 = no current winners
      1 = player 1 has won
      2 = player 2 has won
    */
    int most_recent_row;
    int most_recent_col;

    std::vector<std::vector<int>> game_board;
    void set_n(int); //includes validation
    void set_m(int); //includes validation
};

#endif
