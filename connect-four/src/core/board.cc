#include <core/board.h>
#include <random>
#include <iostream>
#include <vector>
#include <math.h>
namespace connect {

Board::Board() {
  NewGame();
}
Board::Board(std::vector<std::vector<int>> board, int player) {
  my_board = board;
  current_player = player;
}

void Board::NewGame() {
  my_board = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}};
  current_player = 2;
}

BoardState Board::WinningMove() {
  int player = current_player;
  // checking horizontal
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 6; row++) {
      if (my_board[row][col] == player && my_board[row][col + 1] == player &&
          my_board[row][col + 2] == player &&
          my_board[row][col + 3] == player) {
        if (player == 1) {
          return BoardState::Playerwins;
        } else {
          return BoardState::AIwins;
        }
      }
    }
  }
  // checking vertical
  for (int col = 0; col < 7; col++) {
    for (int row = 0; row < 3; row++) {
      if (my_board[row][col] == player && my_board[row + 1][col] == player &&
          my_board[row + 2][col] == player &&
          my_board[row + 3][col] == player) {
        if (player == 1) {
          return BoardState::Playerwins;
        } else {
          return BoardState::AIwins;
        }
      }
    }
  }
  // checking upward slope
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      if (my_board[row][col] == player &&
          my_board[row + 1][col + 1] == player &&
          my_board[row + 2][col + 2] == player &&
          my_board[row + 3][col + 3] == player) {
        if (player == 1) {
          return BoardState::Playerwins;
        } else {
          return BoardState::AIwins;
        }
      }
    }
  }
  // checking downward slope
  for (int col = 0; col < 4; col++) {
    for (int row = 3; row < 6; row++) {
      if (my_board[row][col] == player &&
          my_board[row - 1][col + 1] == player &&
          my_board[row - 2][col + 2] == player &&
          my_board[row - 3][col + 3] == player) {
        if (player == 1) {
          return BoardState::Playerwins;
        } else {
          return BoardState::AIwins;
        }
      }
    }
  }
  return BoardState::NoWinner;
}

void Board::Move(int player, int col) {
   bool has_moved = false;
   while (has_moved == false) {
     if (IsMoveValid(col)) {
       for (int i = 5; i >= 0; i--) {
         if (my_board[i][col] == 0) {
           my_board[i][col] = player;
           current_player = 3 - current_player;
           has_moved = true;
           return;
         }
       }
     }
   }
}

std::vector<int> Board::GetValidMoves() {
  std::vector<int> to_return;
  for (int c = 0; c < 7; c++) {
    if (my_board[0][c] == 0) {
      to_return.push_back(c);
    }
  }
  return to_return;

}

bool Board::IsMoveValid(int col) {
  std::vector<int> valid_moves = GetValidMoves();
  for (int i = 0; i < valid_moves.size(); i++) {
    if (col == valid_moves[i]) {
      return true;
    }
  }
  return false;
}
std::vector<std::vector<int>> Board::GetBoard() {
  return my_board;
}
void Board::PrintBoard() {
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 7; col++) {
      std::cout << my_board[row][col];
      std::cout << "  ";
    }
    std::cout << "\n";
  }
}
int Board::IsGameEnd() {
  switch (WinningMove()) {
    case BoardState::NoWinner:
      return 0;
    case BoardState::Playerwins:
      return 1;
    case BoardState::AIwins:
      return 2;
  }
}
int Board::ScoreAtPosition(connect::Board board, int player) {
  int score = 0;
  //more pieces on the center column is better, so I am giving it a score base on how many pieces on the center column
  for (int i = 0; i < 6; i++) {
    if (my_board[i][3] == player) {
      score += 3;
    }
  }
  //horizontal
  for (int r = 0; r < 6; r++) {
    for (int c = 0; c < 4; c++) {
      score += EvaluateScore(my_board[r][c], my_board[r][c + 1], my_board[r][c + 2], my_board[r][c + 3], player);
    }
  }
  //vertical
  for (int c = 0; c < 7; c++) {
    for (int r = 0; r < 3; r++) {
      score += EvaluateScore(my_board[r][c], my_board[r + 1][c], my_board[r + 2][c], my_board[r + 3][c], player);
    }
  }
  //positive slope
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++) {
      score += EvaluateScore(my_board[r][c], my_board[r + 1][c + 1], my_board[r + 1][c + 2], my_board[r + 1][c + 3], player);
    }
  }
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++) {
      score += EvaluateScore(my_board[r + 3][c], my_board[r + 2][c - 1], my_board[r + 1][c - 2], my_board[r][c - 3], player);
    }
  }
  return score;
}
int Board::EvaluateScore(int one, int two, int three, int four, int player) {
  int score = 0;
  int count = 0;
  int opp_count = 0;
  int empty_count = 0;

  if (one == 0) {
    empty_count += 1;
  }
  if (two == 0) {
    empty_count += 1;
  }
  if (three == 0) {
    empty_count += 1;
  }
  if (four == 0) {
    empty_count += 1;
  }

  if (one == player) {
    count += 1;
  }
  if (two == player) {
    count += 1;
  }
  if (three == player) {
    count += 1;
  }
  if (four == player) {
    count += 1;
  }

  if (one == 3 - player) {
    opp_count += 1;
  }
  if (two == 3 - player) {
    opp_count += 1;
  }
  if (three == 3 - player) {
    opp_count += 1;
  }
  if (four == 3 - player) {
    opp_count += 1;
  }

  if (count == 4) {
    score += 100;
  }
  else if (count == 3 && empty_count == 1) {
    score += 5;
  }
  else if (count == 2 && empty_count == 2) {
    score += 2;
  }

  if (opp_count == 4) {
    score -= 100;
  }
  if (opp_count == 3 && empty_count == 1) {
    score -= 5;
  }

  return score;
}

std::vector<int> Board::Minimax(Board board, int depth, int alpha, int beta, bool maximize) {
  std::vector<int> valid_moves = GetValidMoves();
  std::vector<int> to_return;
  if (depth == 0 or IsGameEnd()) {
    if (IsGameEnd()) {
      if (board.WinningMove() == BoardState::AIwins) {
        to_return.push_back(10000);
        to_return.push_back(4);
        return to_return;
      } else if (board.WinningMove() == BoardState::Playerwins) {
        to_return.push_back(-10000);
        to_return.push_back(4);
        return to_return;
      } else {
        to_return.push_back(0);
        to_return.push_back(4);
        return to_return;
      }
    } else {
      to_return.push_back(ScoreAtPosition(board, current_player));
      to_return.push_back(3);
      return to_return;
    }
  }
  //maximizing AI move
  if (maximize) {
    int score = -100000;
    int column = 3;//static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/7));
    for (int i = 0; i < GetValidMoves().size(); i++) {
      Board copy = board;
      copy.Move(2, i);
      int new_score = copy.Minimax(copy, depth - 1, alpha, beta, false)[1];
      if (new_score > score) {
        score = new_score;
        column = GetValidMoves()[i];
      }
      alpha = std::max(alpha, score);
      if (alpha >= beta) {
        break;
      }
    }
    to_return.push_back(score);
    to_return.push_back(column);
    return to_return;
  } else {
    int score = 100000;
    int column = 6;//static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/7));
    for (int i = 0; i < GetValidMoves().size(); i++) {
      Board copy = board;
      copy.Move(1, i);
      int new_score = copy.Minimax(copy, depth - 1, alpha, beta, true)[1];
      if (new_score < score) {
        score = new_score;
        column = GetValidMoves()[i];
      }
      beta = std::min(beta, score);
      if (alpha >= beta) {
        break;
      }
      to_return.push_back(score);
      to_return.push_back(column);
      return to_return;
    }
  }
  to_return.push_back(0);
  to_return.push_back(static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/7)));
  return to_return;
}

void Board::SetCurrentPlayer(int player) {
  current_player = player;
}
int Board::GetCurrentPlayer() {
  return current_player;
}
bool Board::IsTerminalNode() {
  return true;
}

}  // namespace naivebayes