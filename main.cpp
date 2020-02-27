#include "game.hpp"
#include "aiplayer.hpp"
#include "humanplayer.hpp"

#include<iostream>
#include<cstdlib>

int main(int argc, char** argv)
{
  int n = std::atoi(argv[1]);
  int m = std::atoi(argv[2]);

  // std::cout << "Enter dimension size (n x n): ";
  // std::cin >> n;
  // std::cout << "Enter number of consectutive disks: ";
  // std::cin >> m;

  Game game = Game(n, m);
  game.generate_board();

  Game* gameptr = &game;

  HumanPlayer player1(gameptr);
  //HumanPlayer player2(gameptr);
  //AIPlayer player1(gameptr, 1);
  AIPlayer player2(gameptr, 2);

  game.print_board();

  do{

    if(!player1.take_turn())
    {
      //if unsuccessful turn, repeat
      continue;
    }
    if(game.is_game_over())
    {
      std::cout << "Player 1 wins!" << std::endl;
      game.print_board();
      player1.print_moves_taken();
      player2.print_moves_taken();
      return 0;
    }
    game.print_board();

    if(!player2.take_turn())
    {
      //if unsuccessful turn, repeat
      continue;
    }
    if(game.is_game_over())
    {
      std::cout << "Player 2 wins!" << std::endl;
      game.print_board();
      player1.print_moves_taken();
      player2.print_moves_taken();
      return 0;
    }
    game.print_board();

  } while(!game.is_game_over());

  return 0;
}
