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

  Game game = Game(n, m); //5x5, connect 3
  game.generate_board();


  // int num_humans;
  // //ADD INPUT VALIDATION
  // std::cout << "Enter number of human players (0 - 2): ";
  // std::cin >> num_humans;

  // std::cout << "made it here" << std::endl;

  Game* gameptr = &game;

  HumanPlayer player1(gameptr);
  //HumanPlayer player2(gameptr);
  AIPlayer player2(gameptr, 2);

  //EVENTUALLY IMPLEMENT
  // if(num_humans == 1)
  // {
  //   player1 = HumanPlayer(game);
  //   player2 = AIPlayer(game);
  // }
  // else if(num_humans == 2)
  // {
  //   HumanPlayer player1(game);
  //   HumanPlayer player2(game);
  // }
  // else if(num_humans == 0)
  // {
  //   AIPlayer player1(game);
  //   AIPlayer player2(game);
  // }

  game.print_board();


  do {

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
