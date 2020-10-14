#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"

class Pawn : public ChessPiece {
 public:
  Pawn(int rank, int file, Player const colour, ChessBoard* const board);
  
  ~Pawn() override;

  /* Requires the position to a move a pawn to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the pawn can move to that position according to its
     indivdual movement ability. */
  bool verifyMove(std::string const pos_to,
		  ChessPiece* board_state[][BOARD_LEN]) override;    
  
 private:
  static const int TAKING_CHANGE = 1;
  static const int FIRST_MOVE_RANK_CHANGE_MAX = 2;
  static const int ALREADY_MOVED_RANK_CHANGE = 1;
  static const int MAX_FILE_CHANGE = 1;  

  /* Helper function for verifyMove() that checks if the specified rank
     to move to is possible considering the piece's attributes. 
     Returns true if it is. */
  bool validRank(int const from_rank, int const to_rank) const;

  /* Helper function for validRank() that checks if the rank is valid 
     according to its colour. */
  bool validRankByColour(int const from, int const to) const ;

  /* Helper function for verifyMove() that checks if the pawn is taking 
     an opponent piece. 
     Returns true if it is. */ 
  bool isTaking(int const to_rank, int const to_file,
		int const rank_change, int const file_change,
		ChessPiece* board_state [][BOARD_LEN]) const;

  /* Helper function for verifyMove() that checks if the pawn is blocked
     by another piece. 
     Returns true if it is. */
  bool isBlocked(int const to_rank , int const to_file,
		 int const rank_change, int const file_change,
		 ChessPiece* board_state[][BOARD_LEN]) const;
};


#endif
