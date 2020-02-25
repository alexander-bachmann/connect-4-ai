#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "game.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <utility>

class AIPlayer
{
  public:
    AIPlayer();
    AIPlayer(Game* game, int disk_num); //disk_num X's = 1, O's = 2

    std::pair<int, int> heuristic_evaluation(std::vector<std::vector<int>>);
    int count_num_vertical_wins(int);
    int count_num_horizontal_wins(int);
    int count_num_diagonal_wins(int);

    std::pair<int, int> min(std::pair<int, int>, std::pair<int, int>);
    std::pair<int, int> max(std::pair<int, int>, std::pair<int, int>);
    std::pair<int, int> minimax(std::vector<std::vector<int>>, int, bool, std::pair<int, int>, std::pair<int, int>);

    void print_all_boards(std::vector<std::vector<int>>, int);
    bool take_turn();
    void print_moves_taken();

  private:
    Game* game;
    int disk_num;
    int opponent_disk_num;
    int current_first_turn_branch = 0;
    int current_column = 0;
    int max_col = 0;
    int min_col = 0;
    int num_minimax_calls = 0;
    int num_boards_explored = 0;
    std::vector<int> moves_taken;

    std::vector<std::pair<int, int>> heuristic_branch_pair_vector;
};

#endif
