#ifndef KING_H
#define KING_H
#include "chessPiece.h"

class King : public ChessPiece {
 public:
  King(int rank, int file, Player const colour, ChessBoard* const board);

  ~King() override;

  /* Requires the position to a move a piece to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the piece can move to that position according to its
     indivdual movement ability. */
  bool verifyMove(std::string const pos_to,
		  ChessPiece* board_state [][BOARD_LEN]) override;    
  
 private:
  static const int MOVE_MAX = 1;
};

#endif
