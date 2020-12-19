#include <string>

#include "board.h"
#include <vector>
#ifndef CONNECT_FOUR_GAME_H
#define CONNECT_FOUR_GAME_H

namespace connect {

struct player {
  const std::string kName;
  const int kNumber;
  const std::string kColor;
};

class Game {
  Game() {
  }

 private:

  connect::Board my_board;
};
}
#endif  // CONNECT_FOUR_GAME_H
