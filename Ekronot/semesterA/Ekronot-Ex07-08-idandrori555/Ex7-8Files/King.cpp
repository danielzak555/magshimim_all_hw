#include "King.h"
#include "const.h"
#include <cmath>

King::King(PieceColor color) : Piece(KING, color), _moved(false), _isChecked(false)
{
}

King::~King()
{
}

bool King::isValidMove(int row, int col, int dRow, int dCol) const
{
  int dr = dRow - row;
  int dc = dCol - col;

  // just one step
  if (dr == 0 && dc == 0)
    return false;

  // one square in any way
  return std::abs(dr) <= KING_MOVE_MAX && std::abs(dc) <= KING_MOVE_MAX;
}

void King::setChecked(bool checked)
{
  _isChecked = checked;
}

void King::setMoved(bool didMove)
{
  _moved = didMove;
}

bool King::getChecked() const
{
  return _isChecked;
};

bool King::getMoved() const
{
  return _moved;
};
