#include "queen.h"

Queen::Queen(int rank, int file, Player const colour, ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "Queen"; 
  if (colour == White)
    _symbol = "W.q";
  else
    _symbol = "B.q";

}

Queen::~Queen(){}

bool Queen::verifyMove(std::string const pos_to, ChessPiece* board_state[][8]) {
  return (!hittingOwnPiece(pos_to, board_state) &&
	  (validStraightMovement(pos_to, board_state) ||
	   validDiagonalMovement(pos_to, board_state)));
}



