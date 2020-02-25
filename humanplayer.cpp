#include "humanplayer.hpp"


HumanPlayer::HumanPlayer()
{
  std::cout << "A human has been born..." << std::endl;
}

HumanPlayer::HumanPlayer(Game* game)
{
  std::cout << "A human has been born..." << std::endl;
  this->game = game;
}

bool HumanPlayer::take_turn()
{
  int col_num;

  std::cout << "Enter column number: ";
  std::cin >> col_num;
  std::cout << std::endl;

  moves_taken.push_back(col_num);
  bool successful_add = this->game->add_disk_to_column(col_num);

  return successful_add;
}

void HumanPlayer::print_moves_taken()
{
  std::cout << "Human moves taken = [";

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
