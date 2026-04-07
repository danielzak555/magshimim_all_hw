#pragma once
#include "Piece.h"

class King : public Piece
{
private:
  bool _isChecked;
  bool _moved;

public:
  King(PieceColor color);
  ~King();

  bool isValidMove(int row, int col, int dRow, int dCol) const override;

  void setChecked(bool checked);
  void setMoved(bool didMove);

  bool getChecked() const;
  bool getMoved() const;
};
