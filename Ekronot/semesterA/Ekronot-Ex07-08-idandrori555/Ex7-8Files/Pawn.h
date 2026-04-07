#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
  bool _moved;

public:
  Pawn(PieceColor color);
  ~Pawn();

  bool isValidMove(int row, int col, int dRow, int dCol) const override;

  void setMoved(bool didMove);

  bool getMoved() const;
};
