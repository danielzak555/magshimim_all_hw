#include "Piece.h"

Piece::Piece(PieceType type, PieceColor color)
    : _type(type), _color(color)
{
}

Piece::~Piece()
{
}

PieceType Piece::getType() const
{
  return _type;
};

PieceColor Piece::getColor() const
{
  return _color;
};

void Piece::setType(PieceType type)
{
  _type = type;
};

void Piece::setColor(PieceColor color)
{
  _color = color;
};
