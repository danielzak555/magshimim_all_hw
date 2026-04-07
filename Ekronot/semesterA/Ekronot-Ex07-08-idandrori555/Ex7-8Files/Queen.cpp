#include "Queen.h"
#include "const.h"
#include <cmath>

Queen::Queen(PieceColor color) : Piece(QUEEN, color)
{
}

Queen::~Queen()
{
}

bool Queen::isValidMove(int row, int col, int dRow, int dCol) const
{
  int dr = dRow - row;
  int dc = dCol - col;

  if (dr == 0 && dc == 0)
  {
    return false;
  }

  // Queen moves straight or diagonal
  return (dr == 0 || dc == 0) || (std::abs(dr) == std::abs(dc));
}
