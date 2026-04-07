#include "Bishop.h"
#include "const.h"
#include <cmath>

Bishop::Bishop(PieceColor color)
    : Piece(BISHOP, color)
{
}

Bishop::~Bishop()
{
}

bool Bishop::isValidMove(int row, int col, int dRow, int dCol) const
{
  int dr = dRow - row;
  int dc = dCol - col;

  return (std::abs(dr) == std::abs(dc)) && (dr != 0);
}
