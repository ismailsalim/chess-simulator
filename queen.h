#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"

class Queen : public ChessPiece {
 public:
  Queen(int rank, int file, Player const colour, ChessBoard* const board);

  ~Queen() override;

  bool verifyMove(std::string const pos_to,
		  ChessPiece* board_state[][BOARD_LEN]) override;      
};

#endif
