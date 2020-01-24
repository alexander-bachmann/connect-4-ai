#include "game.hpp"

Game::Game(int n, int m)
{
  set_n(n);
  set_m(m);
  this->player_one_turn = true;
}

void Game::generate_board()
{
  std::cout << "Generating board..." << std::endl;

  //resizing the board based off of n
  this->game_board.resize(this->n);
  for(long unsigned int i = 0; i < this->game_board.size(); ++i)
  {
    this->game_board[i].resize(this->n);
  }

  //populating the board with filler 0s
  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
      this->game_board[i][j] = 0;
    }
  }
}

void Game::print_board()
{
  std::string board_state;

  board_state.append("\n");

  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
      board_state.append("+---");
    }
    board_state.append("+");
    board_state.append("\n");

    for(int j = 0; j < this->n; ++j)
    {
      board_state.append("| ");

      if(this->game_board[i][j] == 1)
      {
          board_state.append("X");
      }
      else if(this->game_board[i][j] == 2)
      {
        board_state.append("O");
      }
      else
      {
        board_state.append("_");
      }

      board_state.append(" ");
    }
    board_state.append("|");
    board_state.append("\n");
  }

  for(int j = 0; j < this->n; ++j)
  {
    board_state.append("+---");
  }
  board_state.append("+");
  board_state.append("\n");

  std::cout << board_state << std::endl;
}

void Game::print_int_board()
{
  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
        std::cout << this->game_board[i][j] << " ";
    }

    std::cout << std::endl;
  }
}

bool Game::game_over()
{
  /*
    searches for a horizontal, vertical, or diagonal line
		check if numDisks == n * n
  */

  return false;
}

bool Game::check_vertical_win(int j)
{
  int consectutive = 1;

  for(int i = this->i; i <= this->n-1; ++i)
  {
    if(i != this->n - 1)
    {
      if(this->game_board[i][j] == this->game_board[i+1][j])
      {
        consectutive++;

        if(consectutive == this->m)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}

bool Game::check_horizontal_win(int j)
{
  int current_column = j;
  int consectutive = 1;

  for(int left_j = current_column; left_j >= 0; --left_j)
  {
    for(int right_j = left_j + 1; right_j < this->n; right_j++)
    {
      if(this->game_board[this->i][left_j] == this->game_board[this->i][right_j])
      {
        consectutive++;

        std::cout << consectutive << std::endl;

        if(consectutive == this->m)
        {
          return true;
        }
      }
    }

    consectutive = 1;
  }

  return false;
}

bool Game::check_diagonal_win(int j)
{

}

bool Game::check_all_wins(int j)
{
  return check_vertical_win(j) || check_horizontal_win(j) || check_diagonal_win(j);
}

void Game::add_disk_to_column(int j)
{
  if(j >= 0 && j < this->n)
  {
    for(int i = this->n-1; i >= 0; --i)
    {
      if(this->game_board[i][j] == 0)
      {
        if(player_one_turn == true)
        {
          this->game_board[i][j] = 1;
          player_one_turn = !player_one_turn;
          this->num_disks++;
          this->i = i;

          if(check_vertical_win(j) == true)
          {
            std::cout << "You win vertically!" << std::endl;
          }

          if(check_horizontal_win(j) == true)
          {
            std::cout << "You win horizontally!" << std::endl;
          }


          break;
        }
        else
        {
          this->game_board[i][j] = 2;
          player_one_turn = !player_one_turn;
          this->num_disks++;
          this-> i = i;

          if(check_vertical_win(j) == true)
          {
            std::cout << "You win vertically!" << std::endl;
          }

          if(check_horizontal_win(j) == true)
          {
            std::cout << "You win horizontally!" << std::endl;
          }
          break;
        }
      }
    }
  }
  else
  {
    std::cout << "Invalid column: out of range" << std::endl;
  }

}

void Game::set_n(int n)
{
  if(n >= 3 && n <= 10)
  {
    this->n = n;
  }
  else
  {
    int new_n = 0;

    std::cout << "Enter valid 'n' (3 - 10): ";
    std::cin >> new_n;
    std::cout << std::endl;

    set_n(new_n);
  }
}

void Game::set_m(int m)
{
  if(m > 1 &&  m <= this->n)
  {
    this->m = m;
  }
  else
  {
    int new_m = 0;

    std::cout << "Please enter valid 'm' (2 - n): ";
    std::cin >> new_m;
    std::cout << std::endl;

    set_m(new_m);
  }
}



/*
getters and setters for:

int num_disks;
bool player_one_turn;

vector<vector<int>> game_board;
*/
