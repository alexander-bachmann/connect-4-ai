
#include "aiplayer.hpp"

AIPlayer::AIPlayer()
{
  std::cout << "An AI has been created..." << std::endl;
}

AIPlayer::AIPlayer(Game* game)
{
  this->game = game;
  std::cout << "An AI has been created..." << std::endl;
}

void AIPlayer::take_turn()
{
  this->game->add_disk_to_column(minimax(this->game->get_game_board(), 3, true));
}

int AIPlayer::heuristic_evaluation(std::vector<std::vector<int>> game_board)
{
  int eval;
  int player_1_num_winning_moves = 0;
  int player_2_num_winning_moves = 0;

  //count the number of possible winning paths remaining and subtract that from opponents number of winning paths remaining
  //check if a move results in a winning state for either player

  /*
    for i
      for j



  */

  std::cout << "Player 1 num winning moves: " << player_1_num_winning_moves << std::endl;
  std::cout << "Player 2 num winning moves: " << player_2_num_winning_moves << std::endl;

  eval = player_1_num_winning_moves - player_2_num_winning_moves;
  std::cout << "heuristic_evaluation: " << eval << std::endl;

  return eval;

}

//minimizing the possible loss for a maximum loss (worst case) scenario.
int AIPlayer::minimax(std::vector<std::vector<int>> game_board, int depth, bool maximizing_player)
{

  heuristic_evaluation(game_board);


  // if depth == 0 || is_game_over in game_board
  //   return static evaluation of game_board -- CALL heuristic_evaluation() HERE - must factor in whose turn it is when counting, probably just base it off player_one_turn
  //
  // if maximizing_player (is AIs turn to move)
  //   max_eval = -INF
  //   for each child (all future game_boards one turn from now, stemming from current game_board) - columns 1 through N
  //     //this is where piece is placed in each successive column
  //
  //     eval = minimax(child_game_board, depth - 1, false)
  //     max_eval = max_value(max_eval, eval)
  //
  //     //this is where previous piece is popped
  //
  //   return max_eval
  //
  //
  // else (is human's turn to move)
  //   min_eval = +INF
  //   for each child (all future game_boards one turn from now, stemming from current game_board)
  //     //this is where piece is placed in each sucessive column
  //
  //     eval = minimax(child_game_board, depth - 1, true)
  //     min_eval = min(min_eval, eval)
  //
  //     //this is where previous piece is popped
  //
  //   return min_eval
}

int AIPlayer::min(int num_1, int num_2)
{
  if(num_1 <= num_2)
  {
    return num_1;
  }
  else
  {
    return num_2;
  }
}

int AIPlayer::max(int num_1, int num_2)
{
  if(num_1 >= num_2)
  {
    return num_1;
  }
  else
  {
    return num_2;
  }
}
