#include "game.hpp"

Game::Game(int n, int m)
{
  this->n = n;
  this->m = m;

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
      this->game_board[i][j] = '_';
      std::cout << this->game_board[i][j] << std::endl;
    }
  }
}

void Game::print_board()
{

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
