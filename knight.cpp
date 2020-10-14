#include "knight.h"
#include "chessBoardHelper.h"
#include <iostream>

Knight::Knight(int rank, int file, Player const colour, ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "Knight";
  if (colour == White)
    _symbol = "W.k";
  else
    _symbol = "B.k";
}

Knight::~Knight(){}

bool Knight::verifyMove(std::string const pos_to, ChessPiece* board_state[][8]) {
  int rank_change = calcRankChange(_pos, pos_to);
  int file_change = calcFileChange(_pos, pos_to);
  return (!hittingOwnPiece(pos_to, board_state) &&
	  ((rank_change == CHANGE_MIN && file_change == CHANGE_MAX) ||
	   (rank_change == CHANGE_MAX && file_change == CHANGE_MIN))); 
}


