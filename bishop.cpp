#include "bishop.h"

Bishop::Bishop(int rank, int file, Player const colour,
	       ChessBoard* const board)
  : ChessPiece(rank, file, colour, board) {
  _name = "Bishop";
  if (colour == White)
    _symbol = "W.b";
  else
    _symbol = "B.b";

}

Bishop::~Bishop(){}

bool Bishop::verifyMove(std::string const pos_to,
			ChessPiece* board_state [][8])  {
  return (!hittingOwnPiece(pos_to, board_state) &&
	  validDiagonalMovement(pos_to, board_state));
}


