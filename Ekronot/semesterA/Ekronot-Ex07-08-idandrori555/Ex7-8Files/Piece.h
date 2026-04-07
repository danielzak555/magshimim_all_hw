#pragma once

#include "const.h"

class Piece
{
protected:
  PieceType _type;
  PieceColor _color;

public:
  Piece(PieceType type, PieceColor color);
  virtual ~Piece();

  virtual bool isValidMove(int row, int col, int dRow, int dCol) const = 0;

  PieceType getType() const;
  PieceColor getColor() const;

  void setType(PieceType type);
  void setColor(PieceColor color);
};
