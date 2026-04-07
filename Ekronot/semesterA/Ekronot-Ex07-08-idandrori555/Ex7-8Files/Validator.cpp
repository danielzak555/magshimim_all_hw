#include "Validator.h"
#include "Board.h"
#include "Piece.h"
#include "const.h"
#include <algorithm> // For std::abs
#include <cmath>

Validator::Validator()
{
}
Validator::~Validator()
{
}

int Validator::isLegalMove(int fromRow, int fromCol, int toRow, int toCol,
                           Board *board, int currentPlayer)
{
  // Make sure positions are on board
  if (!isWithinBounds(fromRow, fromCol) || !isWithinBounds(toRow, toCol))
    return INVALID_INDEX;

  // Check move to the same spot
  if (!isSourceDifferentFromTarget(fromRow, fromCol, toRow, toCol))
    return INVALID_SAME_POSITION;

  // Check for own piece
  if (!hasPlayerPieceAtSource(fromRow, fromCol, board, currentPlayer))
    return INVALID_NO_PIECE;

  // Check attack your own pieces
  if (!isTargetNotOwnPiece(toRow, toCol, board, currentPlayer))
    return INVALID_OWN_PIECE;

  Piece *movingPiece = board->getPiece(fromRow, fromCol);

  // Check if the move si legal for the piece
  if (movingPiece->getType() == PAWN)
  {
    if (!isPawnMoveLegal(fromRow, fromCol, toRow, toCol, board, movingPiece))
      return INVALID_ILLEGAL_MOVE;
  }
  else
  {
    // move check
    if (!movingPiece->isValidMove(fromRow, fromCol, toRow, toCol))
      return INVALID_ILLEGAL_MOVE;

    // Check clear path
    if (movingPiece->getType() != KNIGHT && movingPiece->getType() != KING)
    {
      if (!isPathClear(fromRow, fromCol, toRow, toCol, board, movingPiece))
        return INVALID_ILLEGAL_MOVE;
    }
  }

  // Cant put your own king in check
  if (willCauseCheck(fromRow, fromCol, toRow, toCol, board, currentPlayer))
    return INVALID_OWN_CHECK;

  // Check if this puts opponent in check or checkmate
  Piece *capturedPiece = nullptr;
  makeTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);

  int opponent = 1 - currentPlayer;
  bool opponentInCheck = isPlayerKingInCheck(board, opponent);

  if (opponentInCheck)
  {
    // // Check if it's checkmate
    // if (isCheckmate(board, opponent)) // remove the note to enable checkmate detection
    // {
    //   undoTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);
    //   return CHECKMATE; // Checkmate!
    // }
    undoTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);
    return VALID_AND_CHECK;
  }

  undoTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);
  return VALID;
}

bool Validator::isWithinBounds(int row, int col) const
{
  return (row >= 0 && row < ROW_SIZE && col >= 0 && col < COL_SIZE);
}

bool Validator::hasPlayerPieceAtSource(int fromRow, int fromCol, Board *board, int currentPlayer) const
{
  if (board->isSquareEmpty(fromRow, fromCol))
    return false;

  return board->getPiece(fromRow, fromCol)->getColor() == currentPlayer;
}

bool Validator::isTargetNotOwnPiece(int toRow, int toCol, Board *board, int currentPlayer) const
{
  if (!board->isSquareEmpty(toRow, toCol))
    if (board->getPiece(toRow, toCol)->getColor() == currentPlayer)
      return false;

  return true;
}

bool Validator::isSourceDifferentFromTarget(int fromRow, int fromCol, int toRow, int toCol) const
{
  return !(fromRow == toRow && fromCol == toCol);
}

bool Validator::isPathClear(int fromRow, int fromCol, int toRow, int toCol, Board *board, Piece *piece) const
{
  int dr = (toRow - fromRow);
  int dc = (toCol - fromCol);

  // Get dir
  if (dr != 0)
    dr = dr / std::abs(dr);
  if (dc != 0)
    dc = dc / std::abs(dc);

  int r = fromRow + dr;
  int c = fromCol + dc;

  // Check nothing blocks the way
  while (r != toRow || c != toCol)
  {
    if (!board->isSquareEmpty(r, c))
      return false;

    r += dr;
    c += dc;
  }

  return true;
}

bool Validator::isPawnMoveLegal(int fromRow, int fromCol, int toRow, int toCol, Board *board, Piece *pawn) const
{
  int direction = (pawn->getColor() == WHITE ? WHITE_PAWN_DIRECTION : BLACK_PAWN_DIRECTION);
  int dr = toRow - fromRow;
  int dc = toCol - fromCol;

  // Capturing diagonally
  if (std::abs(dc) == PAWN_ATTACK_DC && dr == direction)
  {
    if (!board->isSquareEmpty(toRow, toCol))
      return true;
    return false; // No diagonal to empty spot
  }

  // Straight ahead only
  if (dc != 0)
    return false;

  // One step forward
  if (dr == direction)
    return board->isSquareEmpty(toRow, toCol);

  // Two steps from start
  if (dr == PAWN_DOUBLE_MOVE * direction)
  {
    // White from row 6, black from row 1
    if ((pawn->getColor() == WHITE && fromRow == WHITE_PAWN_START_ROW) ||
        (pawn->getColor() == BLACK && fromRow == BLACK_PAWN_START_ROW))
    {
      int midRow = fromRow + direction;
      return board->isSquareEmpty(midRow, fromCol) && board->isSquareEmpty(toRow, toCol);
    }
  }

  return false;
}

bool Validator::willCauseCheck(int fromRow, int fromCol, int toRow, int toCol,
                               Board *board, int currentPlayer)
{
  Piece *capturedPiece = nullptr;
  makeTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);

  bool kingInCheck = isPlayerKingInCheck(board, currentPlayer);

  undoTemporaryMove(board, fromRow, fromCol, toRow, toCol, capturedPiece);

  return kingInCheck;
}

bool Validator::isPlayerKingInCheck(Board *board, int player) const
{
  int kingRow = -1, kingCol = -1;
  findKingPosition(board, player, kingRow, kingCol);

  if (kingRow == -1)
    return false; // Weird if no king

  return isSquareUnderAttack(kingRow, kingCol, board, 1 - player);
}

bool Validator::willOpponentBeInCheck(int fromRow, int fromCol, int toRow, int toCol,
                                      Board *board, int currentPlayer)
{
  Piece *captured = nullptr;
  makeTemporaryMove(board, fromRow, fromCol, toRow, toCol, captured);

  int opponent = 1 - currentPlayer;
  bool result = isPlayerKingInCheck(board, opponent);

  undoTemporaryMove(board, fromRow, fromCol, toRow, toCol, captured);

  return result;
}

bool Validator::isSquareUnderAttack(int row, int col, Board *board, int byPlayer) const
{
  for (int r = 0; r < ROW_SIZE; r++)
  {
    for (int c = 0; c < COL_SIZE; c++)
    {
      Piece *piece = board->getPiece(r, c);
      if (!piece || piece->getColor() != byPlayer)
        continue;

      int dr = row - r;
      int dc = col - c;
      int type = piece->getType();

      // Check if this piece can hit the square
      // Better than using move logic which has extra rules

      bool canAttack = false;

      if (type == PAWN)
      {
        int direction = (piece->getColor() == WHITE ? WHITE_PAWN_DIRECTION : BLACK_PAWN_DIRECTION);
        // Pawns take diagonally ahead
        if (dr == direction && std::abs(dc) == PAWN_ATTACK_DC)
        {
          canAttack = true;
        }
      }
      else if (type == KNIGHT)
      {
        if (std::abs(dr * dc) == KNIGHT_MOVE_PRODUCT)
          canAttack = true;
      }
      else if (type == KING)
      {
        if (std::max(std::abs(dr), std::abs(dc)) == KING_MOVE_MAX)
          canAttack = true;
      }
      else if (type == ROOK)
      {
        if (dr == 0 || dc == 0)
          canAttack = true;
      }
      else if (type == BISHOP)
      {
        if (std::abs(dr) == std::abs(dc))
          canAttack = true;
      }
      else if (type == QUEEN)
      {
        if ((dr == 0 || dc == 0) || (std::abs(dr) == std::abs(dc)))
          canAttack = true;
      }
      else
      {
        // Fallback for custom pieces if any, relying on their move logic
        if (piece->isValidMove(r, c, row, col))
          canAttack = true;
      }

      if (!canAttack)
        continue;

      // Sliders need clear path
      if (type != KNIGHT && type != KING && type != PAWN)
      {
        if (!isPathClear(r, c, row, col, board, piece))
          continue;
      }

      return true;
    }
  }
  return false;
}

bool Validator::isCheckmate(Board *board, int player) const
{
  int kingRow = -1, kingCol = -1;
  findKingPosition(board, player, kingRow, kingCol);

  if (kingRow == -1)
    return false;

  // King has to be in check
  if (!isSquareUnderAttack(kingRow, kingCol, board, 1 - player))
  {
    return false;
  }

  // Any way out?
  if (hasLegalMove(board, player))
  {
    return false;
  }

  return true;
}

// See if player can make any legal move
bool Validator::hasLegalMove(Board *board, int player) const
{
  // Go through all player's pieces
  for (int r = 0; r < ROW_SIZE; r++)
  {
    for (int c = 0; c < COL_SIZE; c++)
    {
      Piece *piece = board->getPiece(r, c);
      if (!piece || piece->getColor() != player)
        continue;

      // Check every possible spot
      for (int tr = 0; tr < ROW_SIZE; tr++)
      {
        for (int tc = 0; tc < COL_SIZE; tc++)
        {
          // Skip same square
          if (r == tr && c == tc)
            continue;

          // Check if move is possible
          if (piece->getType() == PAWN)
          {
            if (!isPawnMoveLegal(r, c, tr, tc, board, piece))
              continue;
          }
          else
          {
            if (!piece->isValidMove(r, c, tr, tc))
              continue;

            // Path clear for sliders
            if (piece->getType() != KNIGHT && piece->getType() != KING)
            {
              if (!isPathClear(r, c, tr, tc, board, piece))
                continue;
            }
          }

          // Cant capture own piece (same color)
          Piece *target = board->getPiece(tr, tc);
          if (target && target->getColor() == player)
            continue;

          // Test move to see if king is safe
          Piece *captured = nullptr;
          makeTemporaryMove(board, r, c, tr, tc, captured);

          bool stillInCheck = isPlayerKingInCheck(board, player);

          undoTemporaryMove(board, r, c, tr, tc, captured);

          if (!stillInCheck)
          {
            return true; // can move
          }
        }
      }
    }
  }
  return false;
}

// Find where the king is
void Validator::findKingPosition(Board *board, int player,
                                 int &kingRow, int &kingCol) const
{
  kingRow = -1;
  kingCol = -1;

  for (int r = 0; r < ROW_SIZE; r++)
  {
    for (int c = 0; c < COL_SIZE; c++)
    {
      Piece *piece = board->getPiece(r, c);
      if (piece && piece->getType() == KING && piece->getColor() == player)
      {
        kingRow = r;
        kingCol = c;
        return;
      }
    }
  }
}

// Tmp move for testing
void Validator::makeTemporaryMove(Board *board, int fromRow, int fromCol,
                                  int toRow, int toCol, Piece *&capturedPiece) const
{
  capturedPiece = board->getPiece(toRow, toCol);
  Piece *movingPiece = board->getPiece(fromRow, fromCol);

  board->setPiece(toRow, toCol, movingPiece);
  board->clearSquare(fromRow, fromCol);
}

// Undo tmp move
void Validator::undoTemporaryMove(Board *board, int fromRow, int fromCol,
                                  int toRow, int toCol, Piece *capturedPiece) const
{
  Piece *movingPiece = board->getPiece(toRow, toCol);

  board->setPiece(fromRow, fromCol, movingPiece);

  if (capturedPiece)
    board->setPiece(toRow, toCol, capturedPiece);
  else
    board->clearSquare(toRow, toCol);
}
