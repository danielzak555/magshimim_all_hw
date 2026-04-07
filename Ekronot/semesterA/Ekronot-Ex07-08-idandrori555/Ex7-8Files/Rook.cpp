#include "Rook.h"
#include "const.h"

Rook::Rook(PieceColor color) : Piece(ROOK, color)
{
}

Rook::~Rook()
{
}

bool Rook::isValidMove(int row, int col, int dRow, int dCol) const
{
  // Rook moves in straight lines
  return (row == dRow || col == dCol) && !(row == dRow && col == dCol);
}
