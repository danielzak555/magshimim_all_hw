#pragma once

#include "Piece.h"
#include "const.h"
#include <string>
class Board
{
protected:
	

	Piece *board[ROW_SIZE * COL_SIZE];

public:
    Board();
    ~Board();

    Piece* getPiece(int row, int col) const;

    void setPiece(int row, int col, Piece* piece);

    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isSquareEmpty(int row, int col) const;

    void clearSquare(int row, int col);

    std::string getBoardString() const;

    void promotePawn(int row, int col, PieceColor player);

};
