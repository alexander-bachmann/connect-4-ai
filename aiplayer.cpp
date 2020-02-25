#include "aiplayer.hpp"

AIPlayer::AIPlayer()
{
  std::cout << "An AI has been created..." << std::endl;
}

AIPlayer::AIPlayer(Game* game, int disk_num)
{
  this->game = game;
  this->disk_num = disk_num;

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
  this->num_boards_explored = 0;

  std::pair<int, int> alpha(-1000000, 0);
  std::pair<int, int> beta(1000000, 0);
  std::pair<int, int> chosen_column = minimax(this->game->get_game_board(), 4, true, alpha, beta);

  std::cout << "Board evaluation score: " << chosen_column.first << std::endl;
  std::cout << "Chosen column: " <<  chosen_column.second << std::endl;
  std::cout << "Number of boards explored: " << this->num_boards_explored << std::endl;
  // std::cout << "Number of minimax calls: " << this->num_minimax_calls << std::endl;

  this->game->add_disk_to_column(chosen_column.second);
  this->moves_taken.push_back(chosen_column.second);
}

std::pair<int, int> AIPlayer::heuristic_evaluation(std::vector<std::vector<int>> game_board)
{
  std::pair<int, int> eval;
  int self_num_winning_moves = 0;
  int opponent_num_winning_moves = 0;

  //count the number of possible winning paths remaining and subtract that from opponents number of winning paths remaining
  self_num_winning_moves = count_num_horizontal_wins(this->disk_num) + count_num_vertical_wins(this->disk_num) + count_num_diagonal_wins(this->disk_num);
  opponent_num_winning_moves = count_num_horizontal_wins(this->opponent_disk_num) + count_num_vertical_wins(this->opponent_disk_num) + count_num_diagonal_wins(this->opponent_disk_num);

  eval.first = self_num_winning_moves - opponent_num_winning_moves;
  eval.second = this->current_first_turn_branch;

  if(this->game->is_game_over() == true)
  {
    if(this->disk_num == this->game->get_winning_disk_num())
    {
      // std::cout << "---WINNING STATE FOUND---" << std::endl;
      eval.first = 10000;
    }
    else if(this->disk_num != this->game->get_winning_disk_num())
    {
      if((this->disk_num == 1 && this->game->get_winning_disk_num() == 2) || (this->disk_num == 2 && this->game->get_winning_disk_num() == 1))
      {
        // std::cout << "---LOSING STATE FOUND---" << std::endl;
        eval.first = -10001;
      }
      else
      {
        // std::cout << "---BOARD HAS BEEN FILLED---" << std::endl;
      }
    }
  }

  // std::cout << "Self num winning moves: " << self_num_winning_moves << std::endl;
  // std::cout << "Opponent num winning moves: " << opponent_num_winning_moves << std::endl;
  // std::cout << "Heuristic evaluation of board: " << eval.first << std::endl;

  return eval;
}

//minimizing the possible loss for a maximum loss (worst case) scenario.
std::pair<int, int> AIPlayer::minimax(std::vector<std::vector<int>> game_board, int depth, bool maximizing_player, std::pair<int, int> alpha, std::pair<int, int> beta)
{
  this->num_minimax_calls++;

  std::pair<int, int> eval;

  if(depth == 0 || this->game->is_game_over() == true)
  {
    //this->game->print_board();
    this->num_boards_explored++;
    return heuristic_evaluation(game_board);
  }

  if(maximizing_player == true) //is AI's turn to move
  {
    std::pair<int, int> max_eval(-1000000, 0);

    for(int i = 1; i <= this->game->get_n(); ++i)
    {
      bool successful_add = this->game->add_disk_to_column(i);

      if(successful_add == true)
      {
        if(depth == 4)
        {
          this->current_first_turn_branch = i;
        }

        eval = minimax(game_board, depth - 1, false, alpha, beta);
        max_eval = max(max_eval, eval);
        alpha = max(alpha, eval);
        this->game->pop_from_column(i);

        if(beta.first <= alpha.first)
        {
          break;
        }
      }
    }

    return max_eval;
  }
  else //is Human's turn to move
  {
    std::pair<int, int> min_eval(1000000, 0);

    for(int i = 1; i <= this->game->get_n(); ++i)
    {
      bool successful_add = this->game->add_disk_to_column(i);

      if(successful_add == true)
      {
        eval = minimax(game_board, depth - 1, true, alpha, beta);
        min_eval = min(min_eval, eval);
        beta = min(beta, eval);
        this->game->pop_from_column(i);

        if(beta.first <= alpha.first)
        {
          break;
        }
      }
    }

    return min_eval;
  }
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
  int consecutive = 0;

  //checking all right diags
  for(int i = 0; i < this->game->get_n() - 1; i++)
  {
    for(int j = 0; j < this->game->get_n() - 1; j++)
    {
      consecutive = 0;

      //going down diagonally
      for(int k = i; k < this->game->get_n(); k++)
      {
        for(int l = j; l < this->game->get_n(); l++)
        {
          int diag_row = abs(i - k);
          int diag_col = abs(j - l);

          if(diag_row == diag_col)
          {
            if(this->game->get_game_board()[k][l] == 0 || this->game->get_game_board()[k][l] == player_disk_num)
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
    }
  }

  consecutive = 0;

  //checking all left diags
  for(int i = 0; i < this->game->get_n(); i++)
  {
    for(int j = 0; j < this->game->get_n(); j++)
    {
      consecutive = 0;

      //going down diagonally
      for(int k = i; k < this->game->get_n(); k++)
      {
        for(int l = j; l >= 0; l--)
        {
          int diag_row = abs(i - k);
          int diag_col = abs(j - l);

          if(diag_row == diag_col)
          {

            if(this->game->get_game_board()[k][l] == 0 || this->game->get_game_board()[k][l] == player_disk_num)
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
    }
  }




  return num_wins;
}

//used to print all boards recursively (basically how the exploration part of minimax works)
void AIPlayer::print_all_boards(std::vector<std::vector<int>> game_board, int depth)
{
  this->game->print_board();

  if(depth == 0)
  {
    return;
  }

  for(int i = 1; i <= this->game->get_n(); ++i)
  {
    bool successful_add = this->game->add_disk_to_column(i);

    if(successful_add == true)
    {
      print_all_boards(game_board, depth - 1);
      this->game->pop_from_column(i);
    }
  }
}

std::pair<int, int> AIPlayer::min(std::pair<int, int> num_1, std::pair<int, int> num_2)
{
  if(num_1.first <= num_2.first)
  {
    return num_1;
  }
  else
  {
    return num_2;
  }
}

std::pair<int, int> AIPlayer::max(std::pair<int, int> num_1, std::pair<int, int> num_2)
{
  if(num_1.first >= num_2.first)
  {
    return num_1;
  }
  else
  {
    return num_2;
  }
}

void AIPlayer::print_moves_taken()
{
  std::cout << "AI moves taken = [";

  for(long unsigned int i = 0; i < this->moves_taken.size(); ++i)
  {
    if(i < this->moves_taken.size() - 1)
    {
      std::cout << this->moves_taken[i] << ", ";
    }
    else
    {
      std::cout << this->moves_taken[i];
    }

  }

  std::cout << "]" << std::endl;
}
