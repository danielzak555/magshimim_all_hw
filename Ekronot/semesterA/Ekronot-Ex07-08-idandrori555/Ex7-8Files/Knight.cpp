#include "Knight.h"
#include "const.h"
#include <cmath>
#include <cstdlib>

Knight::Knight(PieceColor color)
    : Piece(KNIGHT, color)
{
}

Knight::~Knight()
{
}

bool Knight::isValidMove(int row, int col, int dRow, int dCol) const
{
  int dr = dRow - row;
  int dc = dCol - col;

  // L shaped move
  return (std::abs(dr) == KNIGHT_MOVE_MAJOR && std::abs(dc) == KNIGHT_MOVE_MINOR) ||
         (std::abs(dr) == KNIGHT_MOVE_MINOR && std::abs(dc) == KNIGHT_MOVE_MAJOR);
}
