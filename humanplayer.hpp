#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "game.hpp"

#include <iostream>
#include <vector>

class HumanPlayer
{
  public:
    HumanPlayer();
    HumanPlayer(Game* game);

    void take_turn();
    void print_moves_taken();

  private:
    Game* game;
    std::vector<int> moves_taken;
};

#endif
