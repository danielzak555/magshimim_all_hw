#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
  Queen(PieceColor color);
  ~Queen();

  bool isValidMove(int row, int col, int dRow, int dCol) const override;
};
