#include "Game.h"

Game::Game()
{
  board = new Board();
  currentPlayer = WHITE; // White first
}

Game::~Game()
{
  delete board;
}

void Game::initializeGame()
{
  delete board;
  board = new Board();
  currentPlayer = WHITE; // White first
}

std::string Game::getBoardState() const
{
  return board->getBoardString();
}

std::string Game::getBoardStateWithPlayer(int curr) const
{
  return board->getBoardString() + std::to_string(curr);
}

std::string Game::processMove(const std::string &move)
{
  int fromRow = -1, fromCol = -1, toRow = -1, toCol = -1;
  Validator validator;
  convertNotationToIndices(move.substr(0, 2), fromRow, fromCol);
  convertNotationToIndices(move.substr(2, 2), toRow, toCol);

  Piece *movingPiece = board->getPiece(fromRow, fromCol);

  int code = validator.isLegalMove(fromRow, fromCol, toRow, toCol, board, currentPlayer);

  if (code == VALID || code == VALID_AND_CHECK)
  {
    // move
    board->movePiece(fromRow, fromCol, toRow, toCol);

    // Check if pawn promotes
    if (movingPiece && movingPiece->getType() == PAWN)
    {
      // White prom at row 0, black at 7
      if ((currentPlayer == WHITE && toRow == PROMOTION_ROW_WHITE) ||
          (currentPlayer == BLACK && toRow == PROMOTION_ROW_BLACK))
      {
        board->promotePawn(toRow, toCol, currentPlayer);
      }
    }

    // Switch turns
    switchPlayer();
  }
  return std::to_string(code);
}

void Game::convertNotationToIndices(const std::string &notation, int &row, int &col) const
{
  col = notation[0] - 'a';
  row = BOARD_SIZE - (notation[1] - '0');
}

PieceColor Game::getCurrentPlayer() const
{
  return currentPlayer;
}

void Game::switchPlayer()
{
  currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
}
