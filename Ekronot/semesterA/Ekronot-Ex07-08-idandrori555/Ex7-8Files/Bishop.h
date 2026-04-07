#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
  Bishop(PieceColor color);
  ~Bishop();

  bool isValidMove(int row, int col, int dRow, int dCol) const override;
};
