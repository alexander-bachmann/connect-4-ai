/*
Human_Player(boolean isTurn)

	boolean isTurn
	int takeTurn(vector[][]) - returns an int of the selected column - set !isTurn
*/

#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "game.hpp"

#include <iostream>

class HumanPlayer
{
  public:
    HumanPlayer();
    HumanPlayer(Game* game);

    void take_turn();

  private:
    Game* game;
};

#endif
