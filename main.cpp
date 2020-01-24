#include "game.hpp"

#include<iostream>

int main()
{
  Game game = Game(5, 3); //5x5, connect 3
  game.generate_board();

  game.print_board();

  int col_num;

  do {
    std::cout << "Enter column number: ";
    std::cin >> col_num;
    std::cout << std::endl;

    game.add_disk_to_column(col_num);

    game.print_board();
    //game.print_int_board();

  } while(!game.game_over());

  return 0;
}


/*
main():

	get n, m from user


	Game game(n, m)

	How many human players?
		if == 1
			Human_Player player1(true)
			AI_Player player2(false)

		if == 2
			Human_Player player1(true)
			Human_Player player2(false)

		if == 0
			AI_Player player1(true)
			AI_Player player2(false)


	while !gameOver

		game.printBoard()

		int decidedColumn

		if(player1.isTurn())
			decidedColumn =	player1.takeTurn()

		else
			decidedColumn = player2.takeTurn()


		game.addToBoard(decidedColumn)
*/
