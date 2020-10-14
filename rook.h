#ifndef ROOK_H
#define ROOK_H
#include "chessPiece.h"

class Rook : public ChessPiece {
 public:
  Rook(int rank, int file, Player const colour, ChessBoard* const board);

  ~Rook() override;

  /* Requires the position to a move a rook to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the rook can move to that position according to its
     indivdual movement ability. */
  bool verifyMove(std::string const pos_to,
		  ChessPiece* board_state[][BOARD_LEN]) override;    
};

#endif
