#include <core/board.h>

#include <iostream>


using namespace connect;
int main() {
  Board game;
  game.NewGame();
  game.Move(1, 3);
  game.Move(2, game.Minimax(game, 6, 0, 0, 2)[0]);
  game.PrintBoard();
  game.Move(1, 3);
  game.Move(2, game.Minimax(game, 6, 0, 0, 2)[0]);
  game.PrintBoard();
  //game.Move(1, 2);
  game.Move(2, game.Minimax(game, 3, 0, 0, 2)[0]);
  game.PrintBoard();
  game.GetCurrentPlayer();

}
