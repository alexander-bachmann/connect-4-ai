#include "game.hpp"
#include "aiplayer.hpp"
#include "humanplayer.hpp"

#include<iostream>

int main()
{
  int n;
  int m;
  std::cout << "Enter dimension size (n x n): ";
  std::cin >> n;
  std::cout << "Enter number of consectutive disks: ";
  std::cin >> m;

  Game game = Game(n, m);
  game.generate_board();

  Game* gameptr = &game;

  //HumanPlayer player1(gameptr);
  //HumanPlayer player2(gameptr);
  AIPlayer player1(gameptr, 1);
  AIPlayer player2(gameptr, 2);

  game.print_board();

  do{

    player1.take_turn();
    if(game.is_game_over())
    {
      std::cout << "Player 1 wins!" << std::endl;
      game.print_board();
      return 0;
    }
    game.print_board();

    player2.take_turn();
    if(game.is_game_over())
    {
      std::cout << "Player 2 wins!" << std::endl;
      game.print_board();
      return 0;
    }
    game.print_board();

  } while(!game.is_game_over());

  return 0;
}
