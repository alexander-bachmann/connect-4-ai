
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

  generate_tree(3); //probs wont have it here -- regenerate tree?? or rewrite tree?? probs rewrite

  std::cout << "An AI has been created..." << std::endl;
}

void AIPlayer::take_turn()
{
  this->game->add_disk_to_column(minimax(this->game->get_game_board(), 3, true));
}

int AIPlayer::heuristic_evaluation(std::vector<std::vector<int>> game_board)
{
  //TODO TO MAKE IT BETTER
  //check if a move results in a winning state for either player
  //favor longer rows

  int eval;
  int self_num_winning_moves = 0;
  int opponent_num_winning_moves = 0;

  //count the number of possible winning paths remaining
  //and subtract that from opponents number of winning paths remaining
  self_num_winning_moves = count_num_horizontal_wins(this->disk_num) + count_num_vertical_wins(this->disk_num) + count_num_diagonal_wins(this->disk_num);
  opponent_num_winning_moves = count_num_horizontal_wins(this->opponent_disk_num) + count_num_vertical_wins(this->opponent_disk_num) + count_num_diagonal_wins(this->opponent_disk_num);

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




// 
// Node* AIPlayer::new_node(int eval)
// {
//   Node* new_node = new Node;
//   new_node->eval = eval;
//   return new_node;
// }
//
// void AIPlayer::generate_children(Node* current_child, int num_children)
// {
//   for(int i = 0; i < num_children; i++)
//   {
//     current_child->child.push_back(new_node(0));
//   }
// }
//
// void AIPlayer::generate_tree(int depth)
// {
//   Node* root = new_node(0);
//   int number_of_nodes = 1;
//
//   //for each turn to look ahead
//
//   std::vector<Node*> current_child;
//
//   current_child = root;
//
//   // for(int i = 0; i < depth; i++)
//   // {
//   //   generate_children(current_child->child);
//   //
//   //   for(int j = 0; j < this->game->get_n(); j++)
//   //   {
//   //     current_child = current_child->child[j];
//   //     generate_children(current_child);
//   //   }
//   // }
//
//   /*
//   for each layer (depth), create n children
//
//     for each child
//
//   */
//
//
//   //
//   // for(int i = 0; i < depth; i++)
//   // {
//   //   current_child->push_back(new_node(0));
//   //
//   //   for(int j = 0; j < this->game->get_n(); j++)
//   //   {
//   //
//   //   }
//   // }
//   //   root->child[i]->child->push_back(new_node(0));
//   //
//
//
//
//   std::cout << "Number of nodes in tree: " << number_of_nodes << std::endl;
// }
//



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
