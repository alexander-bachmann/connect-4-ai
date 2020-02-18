
#include "aiplayer.hpp"

AIPlayer::AIPlayer()
{
  std::cout << "An AI has been created..." << std::endl;
}

AIPlayer::AIPlayer(Game* game, int disk_num)
{
  this->game = game;
  this->disk_num = disk_num;

  //used in heuristic_evaluation()
  if(this->disk_num == 1)
  {
    this->opponent_disk_num = 2;
  }
  else if(this->disk_num == 2)
  {
    this->opponent_disk_num = 1;
  }

  std::cout << "An AI has been created..." << std::endl;
}

void AIPlayer::take_turn()
{
  this->game->add_disk_to_column(minimax(this->game->get_game_board(), 3, true));
}

int AIPlayer::heuristic_evaluation(std::vector<std::vector<int>> game_board)
{
  int eval;
  int self_num_winning_moves = 0;
  int opponent_num_winning_moves = 0;

  //count the number of possible winning paths remaining
  //and subtract that from opponents number of winning paths remaining

  //check if a move results in a winning state for either player
  //favor longer rows (if time permits)

  self_num_winning_moves = count_num_horizontal_wins(this->disk_num) /*+ count_num_vertical_wins(this->disk_num) */+ count_num_diagonal_wins(this->disk_num);
  opponent_num_winning_moves = count_num_horizontal_wins(this->opponent_disk_num) /*+ count_num_vertical_wins(this->opponent_disk_num)*/ + count_num_diagonal_wins(this->opponent_disk_num);

  eval = self_num_winning_moves - opponent_num_winning_moves;

  std::cout << "Self num winning moves: " << self_num_winning_moves << std::endl;
  std::cout << "Opponent num winning moves: " << opponent_num_winning_moves << std::endl;

  std::cout << "Heuristic evaluation of board: " << eval << std::endl;

  return eval;
}

int AIPlayer::count_num_vertical_wins(int player_disk_num)
{
  int num_wins = 0;
  int consecutive = 0;

  for(int i = 0; i < this->game->get_n() - 1; i++)
  {
    for(int j = 0; j < this->game->get_n(); j++)
    {
      consecutive = 0;

      //GO DOWN THE COLUMN
      for(int k = i; k < this->game->get_n(); k++)
      {
        if(this->game->get_game_board()[k][j] == 0 || this->game->get_game_board()[k][j] == player_disk_num)
        {
          ++consecutive;
        }
        else
        {
          break;
        }
        if(consecutive == this->game->get_m())
        {
          ++num_wins;
          break;
        }
      }
    }
  }

  return num_wins;
}

int AIPlayer::count_num_horizontal_wins(int player_disk_num)
{
  int num_wins = 0;
  int consecutive = 0;

  for(int i = 0; i < this->game->get_n(); i++)
  {
    for(int j = 0; j < this->game->get_n() - 1; j++)
    {
      consecutive = 0;

      //GO ACROSS THE ROW
      for(int k = j; k < this->game->get_n(); k++)
      {
        if(this->game->get_game_board()[i][k] == 0 || this->game->get_game_board()[i][k] == player_disk_num)
        {
          ++consecutive;
        }
        else
        {
          break;
        }
        if(consecutive == this->game->get_m())
        {
          ++num_wins;
          break;
        }
      }
    }
  }


  return num_wins;
}

int AIPlayer::count_num_diagonal_wins(int player_disk_num)
{
  int num_wins = 0;

  return num_wins;
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
