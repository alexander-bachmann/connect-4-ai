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

void HumanPlayer::take_turn()
{
  int col_num;

  std::cout << "Enter column number: ";
  std::cin >> col_num;
  std::cout << std::endl;

  this->game->add_disk_to_column(col_num);
}
