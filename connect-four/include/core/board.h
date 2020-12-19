#include <string>
#include <vector>

namespace connect {

enum class BoardState {
  NoWinner,
  Playerwins,
  AIwins,

};

class Board {
 public:
  Board();

  Board(std::vector<std::vector<int>> board, int player);

  void NewGame();

  /**
   * Evaluates the state of the board.
   */
  BoardState WinningMove();

  void Move(int player, int col);

  std::vector<std::vector<int>> GetBoard();

  void PrintBoard() ;

  int IsGameEnd();

  /**
     *
     * @param board the current board
     * @param player the player that calls this method to give a score to its
     * moves (the AI player)
     * @return a score for the player of this board passed in
     *            For any board, I am looking for if there is any 4-in-a-row,
     * 3-in-a-row or 2-in-a-row. This method is going to look at the entire
     * board in horizontals, verticals, and diagnoses, and calls EvaluateScore
     * function to score them.
     *
     */
  int ScoreAtPosition(Board board, int player) ;

  /**
   *
   * @param four_pieces Giving by the ScoreAtPosition method, four connected pieces for this method to check.
   *        It will look for any 4-in-a-row, 3-in-a-row or 2-in-a-row.
   * @param player The player that calls this method (AI player).
   * @return A score of this four connected pieces. This method will be called multiple times by ScoreAtPosition
   *         and in that it will cumulate the scores in to a total score of the current board.
   */
  //int EvaluateScore(std::vector<int> four_pieces, int player) ;

  std::vector<int> Minimax(Board board, int depth, int alpha,int beta, bool maximize);

  //int RunGameLoop();

  void SetCurrentPlayer(int player);

  int GetCurrentPlayer();

 private:

  bool IsMoveValid(int col);

  std::vector<int> GetValidMoves();

  std::vector<std::vector<int>> my_board;

  int current_player;

  int EvaluateScore(int one, int two, int three, int four, int player);

  bool IsTerminalNode();
};
}  // namespace naivebayes


