#include "Pawn.h"
#include "const.h"
#include <cmath>

Pawn::Pawn(PieceColor color) : Piece(PAWN, color), _moved(false)
{
}

Pawn::~Pawn()
{
}

bool Pawn::isValidMove(int row, int col, int dRow, int dCol) const
{
  if (row < 0 || row >= ROW_SIZE || col < 0 || col >= COL_SIZE)
    return false;

  int dr = dRow - row;
  int dc = dCol - col;
  int absDr = std::abs(dr);
  int absDc = std::abs(dc);

  return ((dc == 0) &&
          ((getColor() == WHITE && ((dr == WHITE_PAWN_DIRECTION) || (dr == WHITE_PAWN_DIRECTION * PAWN_DOUBLE_MOVE && !_moved))) ||
           (getColor() == BLACK && ((dr == BLACK_PAWN_DIRECTION) || (dr == BLACK_PAWN_DIRECTION * PAWN_DOUBLE_MOVE && !_moved))))) ||
         (absDc == PAWN_ATTACK_DC &&
          ((getColor() == WHITE && dr == WHITE_PAWN_DIRECTION) ||
           (getColor() == BLACK && dr == BLACK_PAWN_DIRECTION)));
}

void Pawn::setMoved(bool didMove)
{
  _moved = didMove;
}

bool Pawn::getMoved() const
{
  return _moved;
};
