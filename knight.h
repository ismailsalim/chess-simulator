#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"

class Knight : public ChessPiece {
 public:
  Knight(int rank, int file, Player const colour, ChessBoard* const board);

  ~Knight() override;

  /* Requires the position to a move a the knight to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the knight can move to that position according to its
     indivdual movement ability. */
  bool verifyMove(std::string const pos_to, ChessPiece* board_state[][8]) override;      

 private:
  static const int CHANGE_MIN = 1;
  static const int CHANGE_MAX = 2;
};

#endif 
