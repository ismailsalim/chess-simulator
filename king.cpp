#include "king.h"
#include "chessBoardHelper.h"

King::King(int rank, int file, Player const colour, ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "King";
  if (colour == White)
    _symbol = "W.K";
  else
    _symbol = "B.K";
}

King::~King(){}

bool King::verifyMove(std::string const pos_to,
		      ChessPiece* board_state [][BOARD_LEN]) {
  int rank_change = calcRankChange(_pos, pos_to);
  int file_change = calcFileChange(_pos, pos_to);
  return (!hittingOwnPiece(pos_to, board_state) &&
	  rank_change <= MOVE_MAX && file_change <= MOVE_MAX); 
}


