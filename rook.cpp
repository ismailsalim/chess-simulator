#include "rook.h"

Rook::Rook(int rank, int file, Player colour, ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "Rook";
  if (colour == White)
    _symbol = "W.r";
  else
    _symbol = "B.r";
}

Rook::~Rook(){}

bool Rook::verifyMove(std::string const pos_to,
		      ChessPiece* board_state [][BOARD_LEN])  {
  return (!hittingOwnPiece(pos_to, board_state) &&
	  validStraightMovement(pos_to, board_state));
}



