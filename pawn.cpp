#include "pawn.h"
#include "chessBoardHelper.h"
#include <iostream>

Pawn::Pawn(int rank, int file, Player const colour, ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "Pawn";
  if (colour == White)
    _symbol = "W.p";
  else
    _symbol = "B.p";
}

Pawn::~Pawn() {
}

bool Pawn::verifyMove(std::string const pos_to,
		      ChessPiece* board_state [][BOARD_LEN]) {
  int from_rank = parseRank(_pos), from_file = parseFile(_pos);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);
  int rank_change = std::abs(to_rank - from_rank);
  int file_change = std::abs(to_file - from_file);

  return (!hittingOwnPiece(pos_to, board_state) &&
	  validRank(from_rank, to_rank) &&
	  file_change <= MAX_FILE_CHANGE &&
	  !isBlocked(to_rank, to_file, rank_change,
		     file_change, board_state) &&
	  !(file_change && !isTaking(to_rank, to_file, rank_change,
  				     file_change, board_state)));
}

bool Pawn::validRank(int const from_rank, int const to_rank) const {
  if (_colour == White)
    return validRankByColour(to_rank, from_rank);
  else
    return validRankByColour(from_rank, to_rank);
}

bool Pawn::validRankByColour(int const to_black, int const to_white) const { 
  if (to_black <= to_white) 
    return false;

  if (_alreadyMoved && (to_black > to_white + ALREADY_MOVED_RANK_CHANGE)) 
      return false;
  
  if (!_alreadyMoved && (to_black > to_white + FIRST_MOVE_RANK_CHANGE_MAX)) 
    return false;

  return true;
}


bool Pawn::isTaking(int const to_rank, int const to_file,
		    int const rank_change, int const file_change,
		    ChessPiece* board_state[][BOARD_LEN]) const {
  return (board_state[to_rank][to_file] &&
	  rank_change == TAKING_CHANGE && file_change == TAKING_CHANGE);
}

bool Pawn::isBlocked(int const to_rank, int const to_file,
		     int const rank_change, int const file_change,
		     ChessPiece* board_state[][BOARD_LEN]) const {
  return (!file_change && 
	  ((rank_change == FIRST_MOVE_RANK_CHANGE_MAX &&
	    !clearPath(formatPos(to_rank, to_file), board_state))
	   ||
	   (rank_change == ALREADY_MOVED_RANK_CHANGE &&
	   board_state[to_rank][to_file])));
}
