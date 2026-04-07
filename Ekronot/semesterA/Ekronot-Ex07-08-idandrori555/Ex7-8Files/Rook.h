#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
  Rook(PieceColor color);
  ~Rook();

  bool isValidMove(int row, int col, int dRow, int dCol) const override;
};
