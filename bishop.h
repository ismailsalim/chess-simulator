#ifndef BISHOP_H
#define BISHOP_H
#include "chessPiece.h"

class Bishop : public ChessPiece {
 public:
  Bishop(int rank, int file, Player const colour, ChessBoard* const board);

  ~Bishop() override;

  /* Requires the position to a move a bishop to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the bishop can move to that position according to its
     indivdual movement ability. */
  bool verifyMove(std::string const pos_to,
		  ChessPiece* board_state[][8]) override;     
};

#endif
