#pragma once
#include "Piece.h"

class Knight : public Piece
{
	public:
		Knight(PieceColor color);
		~Knight();

		bool isValidMove(int row, int col, int dRow, int dCol) const override;
};
