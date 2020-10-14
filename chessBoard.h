#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chessBoardHelper.h"
#include "player.h"
#include <string>

class ChessPiece;

class ChessBoard {
 public:
  ChessBoard();
  
  ~ChessBoard();

  /* Resets the chessboard to its starting mode and announces this.
     Cleans up the dynamically allocated pieces from the previous board. */
  void resetBoard();

  /* Requires the position on the board to move a piece from and the position
     to move it to. Attempts to make the move, and update the game and board
     accordingly.
     Returns an appropriate error code. */
  int submitMove(std::string const piece_from, std::string const piece_to);

 private:
  static constexpr int WHITE_NOT_PAWN_RANK = 0, WHITE_PAWN_RANK = 1;
  static constexpr int BLACK_PAWN_RANK = 6, BLACK_NOT_PAWN_RANK = 7;
  ChessPiece* _board [BOARD_LEN][BOARD_LEN];
  Player _playerToMove;
  bool _gameOver;

  /* Helper function for resetBoard() that frees dynamically allocated
     memory. */
  void cleanUpBoard();

  /* Sets up the chessboard to its starting mode. */
  void setupStartingBoard();

  /* Helper function to set up the non-pawns on the starting board. */
  void setupNonPawns(int const rank, Player const colour);

  /* Helper function to set up the pawns on the starting board. */
  void setupPawns(int const rank, Player const colour);

  /* Helper function to set up the empty ranks on the starting board. */
  void setEmptyRank(int const rank);

  /* Helper function to set a square on the board as empty. */
  void setEmptySquare(int const rank, int const file);

  
  /* Requires the piece that is being moved and the position that is 
     submitted for it to go to. Checks if the piece is able to reach 
     that position according to its defined movement ability.
     Returns true if the position can't be reached.
  */
  bool inaccessibleMove(ChessPiece* const piece,
			std::string const pos_to);

  /* Requires the positions to move a piece from and to. Checks if these
     are valid positions before looking at the piece's movement ability.
     Returns true if the position(s) are invalid. */
  bool invalidPositions(std::string const pos_from,
			std::string const pos_to) const;
  
  /* Helper function for invalidPositions() to catch exceptions. 
     Returns true if all six validity tests specifed below pass. */
  bool validPositionsTests(std::string const pos_from,
			   std::string const pos_to) const;

  /* 1. Returns true if syntax of submitted position is correct. */
  bool validSyntax(std::string const pos) const;

  /* 2. Returns true if submitted position is not within the board. */
  bool outsideBoard(std::string const pos) const;

  /* 3. Returns true if a piece exists in the submitted position to move
     a piece from. */
  bool pieceExists(std::string const pos) const;

  /* 4. Returns true if the submitted position accords to the correct player
     to move during that turn. */
  bool correctPlayer(std::string const pos) const;

  /* 5. Return true if the positions are the same (i.e. piece not being moved) */
  bool notMoved(std::string const pos_from,
		std::string const pos_to) const;

  
  /* Requires a blank board checking state (i.e. the positions of all the pieces 
     on the board after a move is made) and the current state (i.e. the state 
     before a move is made) and the positions involved for a move.
     Copies over the current state to the checking state and accounts for the
     move. */
  void setCheckingState(ChessPiece* checking_state [][BOARD_LEN],
			ChessPiece* current_state [][BOARD_LEN],
			std::string const pos_from, 
			std::string constpos_to) const;

  /* Helper function for setCheckingState() to copy over a state. */
  void copyState(ChessPiece* copy_from [][BOARD_LEN],
		 ChessPiece* copy_to [][BOARD_LEN]) const;

  /* Helper function for setCheckingState() to account for the piece move. */
  void setPieceChange(ChessPiece* checking_state [][BOARD_LEN],
		      ChessPiece* current__state [][BOARD_LEN],
		      std::string const pos_from,
		      std::string const pos_to) const;

  /* Requires the original board state (before a move is made) and resets the
     board from the checking state back to the original state. */
  void undoState(ChessPiece* original_state [][BOARD_LEN],
		 std::string const pos_from) const;

  /* Requires the board state and the player to test if in check. Tests if the
     king of the player is being threated by an opponent piece.
     Returns true if that player is in check. */ 
  bool isCheck(ChessPiece* board_state [][BOARD_LEN],
	       int const threatened_player) const;

  /* Helper function for isCheck() that returns the king's position for the 
     played being tested if in check. */
  std::string findKingPos(ChessPiece* board_state [][BOARD_LEN],
			  int const threatened_player) const;

  /* Helper function for isCheck() that returns true if the king of the player
     being tested if in check is being threated by an opponent piece. */
  bool kingThreatened(ChessPiece* board_state[][BOARD_LEN],
		      int const threatened_player,
		      std::string const king_pos) const;  

  /* Requires the checking state of a board. 
     Returns true if a player can't make a move. */
  bool noFurtherMoves(ChessPiece* checking_state[][BOARD_LEN]) const;
  
  /* Requires whether the opponent is in check or not and the checking state.
     Return true if the game is in checkmate or stalemate.
  */ 
  bool gameOver(bool const opp_in_check,
		ChessPiece* checking_state [][BOARD_LEN]);


  /* Prints a valid move that is submitted. */
  void printMove(std::string const piece_from,
		 std::string const piece_to) const;

  /* Updates the board after a valid moves is submitted. */
  void updateBoard(ChessPiece* checking_state [][BOARD_LEN],
		   std::string const pos_to);

  /* Helper function for updateBoard() that updates the moved piece's position.
   */
  void updateMovedPiece(ChessPiece* piece_to_update,
			std::string const pos_to) const; 

  /* Switches the player who's turn is next. */
  void switchPlayerToMove();
};
#endif

