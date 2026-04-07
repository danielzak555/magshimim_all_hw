#pragma once
#include "Board.h"
#include "Validator.h"
#include <string>

class Game
{
private:
  Board *board;
  PieceColor currentPlayer;

public:
  Game();
  ~Game();

  void initializeGame();

  std::string getBoardState() const;

  std::string getBoardStateWithPlayer(int curr) const;

  std::string processMove(const std::string &move);

  // Turns moves like e2 into numbers
  void convertNotationToIndices(const std::string &notation, int &row, int &col) const;

  PieceColor getCurrentPlayer() const;

  void switchPlayer();
};
