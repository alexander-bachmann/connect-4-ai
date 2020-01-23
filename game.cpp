#include "game.hpp"

Game::Game(int n, int m)
{
  this->n = n;
  this->m = m;
  this->player_one_turn = true;

  /*
  validate: m = (>1 && <= n)
  validate: n = (>= 3 && <= 10)  (grid size = n*n)
  */
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

  //populating the board with filler underscores '_'
  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
      this->game_board[i][j] = "_";
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
      board_state.append(this->game_board[i][j]);
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

bool Game::game_over()
{
  /*
    searches for a horizontal, vertical, or diagonal line
		check if numDisks == n * n
  */

  return false;
}

void Game::add_disk_to_column(int j)
{
  //place in bottom (highest i available in column j)

  for(int i = this->n-1; i >= 0; --i)
  {
    if(this->game_board[i][j] == "_")
    {
      if(player_one_turn == true)
      {
        this->game_board[i][j] = "X";
        break;
      }
      else
      {
        this->game_board[i][j] = "O";
        break;
      }
    }
  }

  player_one_turn = !player_one_turn;
  this->num_disks++;
}


/*
getters and setters for:

int m;
int n;
int num_disks;
bool player_one_turn;

vector<vector<char>> game_board;
*/