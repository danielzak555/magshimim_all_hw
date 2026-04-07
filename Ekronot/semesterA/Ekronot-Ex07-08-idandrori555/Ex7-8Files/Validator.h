#pragma once
#include "Board.h"

class Validator
{
public:
  Validator();
  ~Validator();

  int isLegalMove(int fromRow, int fromCol, int toRow, int toCol, Board *board, int currentPlayer);

  // On the board?
  bool isWithinBounds(int row, int col) const;

  // Your piece there?
  bool hasPlayerPieceAtSource(int fromRow, int fromCol, Board *board, int currentPlayer) const;

  // Not your own piece at target?
  bool isTargetNotOwnPiece(int toRow, int toCol, Board *board, int currentPlayer) const;

  // Different squares?
  bool isSourceDifferentFromTarget(int fromRow, int fromCol, int toRow, int toCol) const;

  // Path clear?
  bool isPathClear(int fromRow, int fromCol, int toRow, int toCol, Board *board, Piece *piece) const;

  // Special pawn rules
  bool isPawnMoveLegal(int fromRow, int fromCol, int toRow, int toCol, Board *board, Piece *pawn) const;

  // Puts own king in check?
  bool willCauseCheck(int fromRow, int fromCol, int toRow, int toCol, Board *board, int currentPlayer);

  // King in check?
  bool isPlayerKingInCheck(Board *board, int player) const;

  // Opponent in check after move?
  bool willOpponentBeInCheck(int fromRow, int fromCol, int toRow, int toCol, Board *board, int currentPlayer);

  // Square attacked?
  bool isSquareUnderAttack(int row, int col, Board *board, int byPlayer) const;

  // Checkmate?
  bool isCheckmate(Board *board, int player) const;

  // Any legal moves left?
  bool hasLegalMove(Board *board, int player) const;

private:
  // Find the king
  void findKingPosition(Board *board, int player, int &kingRow, int &kingCol) const;

  // Temp move for testing
  void makeTemporaryMove(Board *board, int fromRow, int fromCol, int toRow, int toCol, Piece *&capturedPiece) const;

  // Undo temp move
  void undoTemporaryMove(Board *board, int fromRow, int fromCol, int toRow, int toCol, Piece *capturedPiece) const;
};
