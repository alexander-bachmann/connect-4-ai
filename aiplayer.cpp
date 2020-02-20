
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
  // print_all_boards(this->game->get_game_board(), 3);
  std::pair<int, int> alpha(-1000000, 0);
  std::pair<int, int> beta(1000000, 0);
  std::pair<int, int> chosen_column = minimax(this->game->get_game_board(), 4, true, alpha, beta);

  std::cout << "Chosen column heuristic evaluation score: " << chosen_column.first << std::endl;
  std::cout << "Chosen column: " <<  chosen_column.second << std::endl;
  // std::cout << "Number of minimax calls: " << this->num_minimax_calls << std::endl;

  this->game->add_disk_to_column(chosen_column.second);
}


std::pair<int, int> AIPlayer::heuristic_evaluation(std::vector<std::vector<int>> game_board)
{
  //TODO TO MAKE IT BETTER
  //check if a move results in a winning state for either player
  //favor longer rows

  std::pair<int, int> eval;
  int self_num_winning_moves = 0;
  int opponent_num_winning_moves = 0;


  //count the number of possible winning paths remaining
  //and subtract that from opponents number of winning paths remaining
  self_num_winning_moves = count_num_horizontal_wins(this->disk_num) + count_num_vertical_wins(this->disk_num) + count_num_diagonal_wins(this->disk_num);
  opponent_num_winning_moves = count_num_horizontal_wins(this->opponent_disk_num) + count_num_vertical_wins(this->opponent_disk_num) + count_num_diagonal_wins(this->opponent_disk_num);

  eval.first = self_num_winning_moves - opponent_num_winning_moves;
  eval.second = this->current_first_turn_branch;

  // this->heuristic_branch_pair_vector.push_back(std::make_pair(this->current_column, eval));

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
  //
   // std::cout << "Heuristic evaluation of board: " << eval.first << std::endl;

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
  int consecutive = 0;

  //checking all right diags
  for(int i = 0; i < this->game->get_n() - 1; i++)
  {
    for(int j = 0; j < this->game->get_n() - 1; j++)
    {
      consecutive = 0;

      //GOING DOWN DIAGONALLY
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

      //0,2 -> 1,1 -> 2,0

      //GOING DOWN DIAGONALLY
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

/*
std::pair<int, int> -- heuristic eval, first branch


*/

//minimizing the possible loss for a maximum loss (worst case) scenario.
std::pair<int, int> AIPlayer::minimax(std::vector<std::vector<int>> game_board, int depth, bool maximizing_player, std::pair<int, int> alpha, std::pair<int, int> beta)
{
  //used to test if AB pruning was working
  this->num_minimax_calls++;

  //USE PAIRS TO KEEP TRACK OF BRANCH ONE FROM ROOT
  //GET IT WORKING BEFORE CHECKING IF AB PRUNING WORKS - pretty sure it works

  std::pair<int, int> eval;

  // std::cout << "Alpha: " << alpha << std::endl;
  // std::cout << "Beta: " << beta << std::endl;
  //
  //this->game->print_board();

  if(depth == 0 || this->game->is_game_over() == true)
  {
    //NEED TO CARE ABOUT WHO WON
    //this->game->print_board();
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
          // std::cout << "First turn from max's side" << std::endl;
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

    // std::cout << "max eval " << max_eval.first << " from branch " << max_eval.second << std::endl;
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

    // std::cout << "min eval " << min_eval.first << " from branch " << min_eval.second << std::endl;
    return min_eval;
  }


}

//used to test that the boards can be printed recursively
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
