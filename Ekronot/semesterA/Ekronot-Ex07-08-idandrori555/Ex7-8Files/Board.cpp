#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <string>

Board::Board()
{
  std::string initialBoard = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";

  for (int i = 0; i < ROW_SIZE; ++i)
  {
    for (int j = 0; j < COL_SIZE; ++j)
    {
      int index = i * COL_SIZE + j;
      char pieceChar = initialBoard[index];

      if (pieceChar == '#')
      {
        board[index] = nullptr;
      }
      else
      {
        PieceColor color = isupper(pieceChar) ? WHITE : BLACK;

        PieceType type;
        switch (tolower(pieceChar))
        {
        case 'r':
          type = ROOK;
          break;
        case 'n':
          type = KNIGHT;
          break;
        case 'b':
          type = BISHOP;
          break;
        case 'q':
          type = QUEEN;
          break;
        case 'k':
          type = KING;
          break;
        case 'p':
          type = PAWN;
          break;
        default:
          type = EMPTY;
          break;
        }

        switch (type)
        {
        case ROOK:
          board[index] = new Rook(color);
          break;
        case KNIGHT:
          board[index] = new Knight(color);
          break;
        case BISHOP:
          board[index] = new Bishop(color);
          break;
        case QUEEN:
          board[index] = new Queen(color);
          break;
        case KING:
          board[index] = new King(color);
          break;
        case PAWN:
          board[index] = new Pawn(color);
          break;
        default:
          board[index] = nullptr;
          break;
        }
      }
    }
  }
}

Board::~Board()
{
  for (int i = 0; i < ROW_SIZE * COL_SIZE; ++i)
  {
    delete board[i];
  }
}

Piece *Board::getPiece(int row, int col) const
{
  return board[row * COL_SIZE + col];
}

void Board::setPiece(int row, int col, Piece *piece)
{
  board[row * COL_SIZE + col] = piece;
}

bool Board::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
  Piece *capturedPiece = getPiece(toRow, toCol);
  if (capturedPiece != nullptr)
  {
    delete capturedPiece;
  }
  setPiece(toRow, toCol, getPiece(fromRow, fromCol));
  setPiece(fromRow, fromCol, nullptr);
  return true;
}

bool Board::isSquareEmpty(int row, int col) const
{
  return (getPiece(row, col) == nullptr);
}

void Board::clearSquare(int row, int col)
{
  setPiece(row, col, nullptr);
}

std::string Board::getBoardString() const
{
  std::string boardStr = "";
  for (int i = 0; i < ROW_SIZE; ++i)
  {
    for (int j = 0; j < COL_SIZE; ++j)
    {
      Piece *piece = getPiece(i, j);
      if (piece == nullptr)
      {
        boardStr += "#";
      }
      else
      {
        PieceType type = piece->getType(); // 'r', 'n', 'b', etc.
        if (piece->getColor() == WHITE)
        {
          boardStr += toupper(type);
        }
        else
        {
          boardStr += tolower(type);
        }
      }
    }
  }
  return boardStr;
}

void Board::promotePawn(int row, int col, PieceColor player)
{
  // rm pawn
  delete getPiece(row, col);

  // Make a new queen with the same colr
  PieceColor color = player;
  Piece *newQueen = new Queen(color);

  // Put the queen there
  setPiece(row, col, newQueen);
}
