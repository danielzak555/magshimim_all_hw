#pragma once

#define BOARD_SIZE 8
#define ROW_SIZE 8
#define COL_SIZE 8

#define WHITE_PAWN_START_ROW 6
#define BLACK_PAWN_START_ROW 1
#define WHITE_PAWN_DIRECTION -1
#define BLACK_PAWN_DIRECTION 1
#define PAWN_ATTACK_DC 1
#define PAWN_DOUBLE_MOVE 2

#define PROMOTION_ROW_WHITE 0
#define PROMOTION_ROW_BLACK 7

#define KNIGHT_MOVE_PRODUCT 2
#define KNIGHT_MOVE_MAJOR 2
#define KNIGHT_MOVE_MINOR 1
#define KING_MOVE_MAX 1

enum PieceColor
{
  WHITE,
  BLACK
};

enum PieceType
{
  EMPTY = '#',
  KING = 'k',
  QUEEN = 'q',
  ROOK = 'r',
  BISHOP = 'b',
  KNIGHT = 'n',
  PAWN = 'p'
};

enum ReturnCode
{
  VALID = 0,
  VALID_AND_CHECK = 1,
  INVALID_NO_PIECE = 2,
  INVALID_OWN_PIECE = 3,
  INVALID_OWN_CHECK = 4,
  INVALID_INDEX = 5,
  INVALID_ILLEGAL_MOVE = 6,
  INVALID_SAME_POSITION = 7,
  CHECKMATE = 8
};
