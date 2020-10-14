#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "chessBoardHelper.h"
#include "player.h"
#include <string>

class ChessBoard;

class ChessPiece {
 public:
  ChessPiece(int rank, int file, Player const colour, ChessBoard* const board);

  virtual ~ChessPiece();

  /* Requires the position to a move a piece to and the state of the board
     (i.e. how the other pieces are arranged on the board). 
     Returns true if the piece can move to that position according to its
     indivdual movement ability. */
  virtual bool verifyMove(std::string const pos_to,
			  ChessPiece* board_state [][BOARD_LEN]) = 0;

  /* Getter and setter function called by ChessBoard */
  virtual std::string getSymbol() const;

  virtual std::string getName() const;

  Player getColour() const;
  
  std::string getPos() const;
  
  void setPos(std::string pos);
  
  bool getAlreadyMoved() const;

  void setAlreadyMoved();

 protected:
  ChessBoard* _board;
  std::string _symbol;
  std::string _name;
  Player const _colour;
  std::string _pos;
  bool _alreadyMoved;

  /* Requires the postition to a move piece to and the board state. 
     Returns true if the position is occupied by a piece of the same colour. */
  bool hittingOwnPiece(std::string const pos_to,
		       ChessPiece* board_state[][BOARD_LEN]) const;

  /* Requires the postition to a move piece to and the board state. 
     Returns true if position involves straight movement (N.B only for movement
     greater than one square) along the board without colliding into any pieces 
     on the way to the specified position. */
  bool validStraightMovement(std::string const pos_to,
			     ChessPiece* board_state[][BOARD_LEN]) const;

  /* Requires the postition to a move piece to and the board state. 
     Returns true if position involves diagonal movement (N.B only for movemet 
     greater than one square) along the board without colliding into any pieces 
     on the way to the specified. */
  bool validDiagonalMovement(std::string const pos_to,
			     ChessPiece* board_state[][BOARD_LEN]) const;

  /* Helper function for valid directional movement functions above. 
     Returns true if the piece doesn't collide into another piece en route. */
  bool clearPath(std::string const pos_to,
		 ChessPiece* board_state[][BOARD_LEN]) const;

  /* Helper function for valid directional movement functions above.
     Returns an integer corresponding to a direction the piece is set to move. */
  int setStep(int const from, int const to) const;

};

#endif 
