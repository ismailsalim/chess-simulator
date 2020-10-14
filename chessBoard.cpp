#include "chessBoard.h"
#include "errors.h"
#include "exceptions.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <iostream>
#include <vector>
#include <assert.h>

ChessBoard::ChessBoard() :
  _playerToMove(White), _gameOver(false) {
  setupStartingBoard();
  std::cout << "A new chess game is started!\n";
}

ChessBoard::~ChessBoard() {
  cleanUpBoard();
}
      
void ChessBoard::resetBoard() {
  cleanUpBoard();
  setupStartingBoard();
  std::cout << "A new chess game is started!\n";
  _playerToMove = White;
  _gameOver = false;
}

void ChessBoard::cleanUpBoard() {
  for (int rank = 0; rank < BOARD_LEN; rank++) {
    for (int file = 0; file < BOARD_LEN; file++)
      delete _board[rank][file];
  }
}

/* SETUP BOARD IMPLEMENTATION */
void ChessBoard::setupStartingBoard() {
  for (int rank = 0; rank < BOARD_LEN; rank++) {
    switch (rank) {
    case WHITE_NOT_PAWN_RANK : setupNonPawns(rank, White); break;
    case WHITE_PAWN_RANK : setupPawns(rank, White); break;
    case BLACK_PAWN_RANK : setupPawns(rank, Black); break;
    case BLACK_NOT_PAWN_RANK : setupNonPawns(rank, Black); break;
    default : setEmptyRank(rank);
    }
  }
}

void ChessBoard::setupPawns(int const rank, Player const colour) {
  for (int file = 0; file < BOARD_LEN; file++) {
    if (rank == WHITE_PAWN_RANK || rank == BLACK_PAWN_RANK) 
      _board[rank][file] = new Pawn(rank, file, colour, this);
  }
}

void ChessBoard::setupNonPawns(int const rank, Player const colour) {
  for (int file = 0; file < BOARD_LEN; file++) {
    switch(file) {
    case 0 :  _board[rank][file] = new Rook(rank, file, colour, this);
      break;
    case 1 :  _board[rank][file] = new Knight(rank, file, colour, this);
      break;
    case 2 :  _board[rank][file] = new Bishop(rank, file, colour, this);
      break;
    case 3 :  _board[rank][file] = new Queen(rank, file, colour, this);
      break;
    case 4 :  _board[rank][file] = new King (rank, file, colour, this);
      break;
    case 5 :  _board[rank][file] = new Bishop(rank, file, colour, this);
      break;
    case 6 :  _board[rank][file] = new Knight(rank, file, colour, this);
      break;
    case 7 :  _board[rank][file] = new Rook(rank, file, colour, this);
      break;
    }
  }
}

void ChessBoard::setEmptyRank(int const rank) {
  for (int file = 0; file < BOARD_LEN; file++)
    setEmptySquare(rank, file);
}

void ChessBoard::setEmptySquare(int const rank, int const file) {
  _board[rank][file] = nullptr;
}
/* END OF IMPLEMENTATION */  

/* SUBMIT MOVE IMPLEMENTATION */
int ChessBoard::submitMove(std::string const piece_from,
			   std::string const piece_to) {
  int from_rank = parseRank(piece_from), from_file = parseFile(piece_from);

  if(_gameOver) {
    std::cerr << "Game is over. Reset the board before making another move!\n";
    return GAME_OVER;
  }

  if (invalidPositions(piece_from, piece_to))
    return POS_ERROR;

  ChessPiece* piece_to_move = _board[from_rank][from_file];
  if (inaccessibleMove(piece_to_move, piece_to))
    return MOVE_ERROR;
  
  ChessPiece* check_state[BOARD_LEN][BOARD_LEN];
  setCheckingState(check_state, _board, piece_from, piece_to);  
  bool self_check = isCheck(check_state, _playerToMove);
  if (self_check) {
    std::cerr << formatPlayer(_playerToMove)
	      << "'s " << _board[from_rank][from_file]->getName()
	      << " cannot move to " << piece_to << std::endl;
    undoState(_board, piece_from);
    return MOVE_ERROR;
  }

  printMove(piece_from, piece_to);  
  bool opp_in_check = isCheck(check_state, 1 - _playerToMove);
  if (gameOver(opp_in_check, check_state))
    return NO_ERROR;

  updateBoard(check_state, piece_to);     

  switchPlayerToMove();

  return NO_ERROR;
}

bool ChessBoard::inaccessibleMove(ChessPiece* const piece,
				  std::string const pos_to) {
  int from_rank = parseRank(piece->getPos());
  int from_file = parseFile(piece->getPos());
  if (!piece->verifyMove(pos_to, _board)) {
    std::cerr << formatPlayer(_playerToMove)
	      << "'s " << _board[from_rank][from_file]->getName()
	      << " cannot move to " << pos_to << std::endl;
    return true;
  } 
  return false;
}			    

bool ChessBoard::invalidPositions(std::string const piece_from,
				 std::string const piece_to) const {
  int from_rank = parseRank(piece_from), from_file = parseFile(piece_from);
  try {validPositionsTests(piece_from, piece_to);}
  catch (const invalidSyntax& e) {
    std::cerr << e.what() << std::endl;
    return true;   
  }
  catch (const outsideBoardError& e) {
    std::cerr << e.what() << std::endl;
    return true;
  }
  catch (const noPiece& e) {
    std::cerr << e.displayMessage() << std::endl;
    return true;
  }
  catch (const wrongPlayer& e) {
    std::cerr << "It is not " << e.getPlayer() << std::endl;
    return true;
  }
  catch (const invalidDestination& e) {
    std::cerr << e.getPlayer() << _board[from_rank][from_file]->getName()
	      << " cannot move to " << e.getDestination() << std::endl;
    return true;
  }
  return false;
}
    
bool ChessBoard::validPositionsTests(std::string const pos_from,
				std::string const pos_to) const {
  if (!validSyntax(pos_from))
    throw invalidSyntax("Syntax error with source position", pos_from);

  if (!validSyntax(pos_to))
    throw invalidSyntax("Syntax error with destination position", pos_to);

  if (outsideBoard(pos_from))
    throw outsideBoardError("Source position is outside board", pos_from);

  if (outsideBoard(pos_to))
    throw outsideBoardError("Destination position is not within board", pos_to);

  if (!pieceExists(pos_from))
    throw noPiece("No piece exists at source position", pos_from);

  if (!correctPlayer(pos_from))
    throw wrongPlayer("Incorrect player moving", _playerToMove);

  if (notMoved(pos_from, pos_to))
    throw invalidDestination("Piece isn't actually moved", pos_to, _playerToMove);
  return true;
}

bool ChessBoard::validSyntax(std::string const pos) const {
  return pos.length() == 2 && isalpha(pos[0]) && isdigit(pos[1]);
}

bool ChessBoard::outsideBoard(std::string const pos) const {
  int rank = parseRank(pos), file = parseFile(pos);
  return file < 0 || file > BOARD_LEN || rank < 0 || rank > BOARD_LEN;
}

bool ChessBoard::pieceExists(std::string const pos) const {
  int rank = parseRank(pos), file = parseFile(pos);
  return _board[rank][file]; 
}

bool ChessBoard::correctPlayer(std::string const pos) const {
  int rank = parseRank(pos), file = parseFile(pos);
  Player selected_colour = _board[rank][file]->getColour();
  return selected_colour == _playerToMove;
}

bool ChessBoard::notMoved(std::string const pos_from,
			  std::string const pos_to) const {
  return pos_from == pos_to;
} 

/* END OF IMPLEMENTATION */

/* CHECK/CHECKMATE IMPLEMENTATION */
void ChessBoard::setCheckingState(ChessPiece* checking_state [][BOARD_LEN],
				  ChessPiece* current_state [][BOARD_LEN],
				  std::string const pos_from,
				  std::string const pos_to) const {
  copyState(checking_state, current_state);
  setPieceChange(checking_state, current_state, pos_from, pos_to);
}

void ChessBoard::copyState(ChessPiece* copy_to_state [][BOARD_LEN],
			   ChessPiece* copy_from_state [][BOARD_LEN]) const {
  for (int rank = 0; rank < BOARD_LEN; rank++) {
    for (int file = 0; file < BOARD_LEN; file++)
      copy_to_state[rank][file] = copy_from_state[rank][file];
  }  
}
				  
void ChessBoard::setPieceChange(ChessPiece* checking_state [][BOARD_LEN],
				ChessPiece* current_state [][BOARD_LEN],
				std::string const pos_from,
				std::string const pos_to) const {
  int from_rank = parseRank(pos_from), from_file = parseFile(pos_from);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);

  checking_state[to_rank][to_file] = current_state[from_rank][from_file];
  checking_state[to_rank][to_file]->setPos(formatPos(to_rank, to_file));
  checking_state[from_rank][from_file] = nullptr;
}


void ChessBoard::undoState(ChessPiece* original_state [][BOARD_LEN],
			   std::string const pos_from) const {
  int from_rank = parseRank(pos_from), from_file = parseFile(pos_from);
  original_state[from_rank][from_file]->setPos(pos_from);
}

bool ChessBoard::isCheck(ChessPiece* board_state [][8],
			 int const threatened_player) const {
  std::string king_pos = findKingPos(board_state, threatened_player);
  return kingThreatened(board_state, threatened_player, king_pos);
}

std::string ChessBoard::findKingPos(ChessPiece* board_state[][BOARD_LEN],
			     int const threatened_player) const {
  for (int rank = 0; rank < BOARD_LEN; rank++) {
    for (int file =  0; file < BOARD_LEN; file++) {
      ChessPiece* piece = board_state[rank][file];
      if(piece && piece->getColour() == threatened_player &&
	 piece->getName() == "King")
	return piece->getPos();
    }
  }
  assert(false && "King should always be found!");
}

bool ChessBoard::kingThreatened(ChessPiece* board_state[][BOARD_LEN],
				int const threatened_player,
				std::string const king_pos) const {
  for (int rank = 0; rank < BOARD_LEN; rank++) {
    for (int file = 0; file < BOARD_LEN; file++) {
      ChessPiece* piece = board_state[rank][file];
      if (piece && piece->getColour() == (1 - threatened_player) &&
	  piece->verifyMove(king_pos, board_state))
	return true;
    }
  }
  return false;
}

bool ChessBoard::noFurtherMoves(ChessPiece* checking_state[][8]) const {
  std::string king_pos = "";

  for (int rank_from = 0; rank_from < BOARD_LEN; rank_from++) {
    for (int file_from = 0; file_from < BOARD_LEN; file_from++) {
      ChessPiece* piece_from = checking_state[rank_from][file_from];      

      if (piece_from && piece_from->getColour() == (1 - _playerToMove))
	for (int rank_to = 0; rank_to < BOARD_LEN; rank_to++) {
	    for (int file_to = 0; file_to < BOARD_LEN; file_to++) {
	      std::string pos_to = formatPos(rank_to, file_to);
	      
	      if (piece_from -> verifyMove(pos_to, checking_state)) {
		ChessPiece* final_checking_state [BOARD_LEN][BOARD_LEN];
		std::string pos_from = formatPos(rank_from, file_from);
		setCheckingState(final_checking_state, checking_state,
				 pos_from, pos_to);
		
		if(!isCheck(final_checking_state, 1 - _playerToMove)) {
		  undoState(checking_state, pos_from);
		  return false;
		}
		undoState(checking_state, pos_from);
	      }
	    }
	}
    }
  }
  return true;  
}

bool ChessBoard::gameOver(bool const opp_in_check,
			  ChessPiece* checking_state [][BOARD_LEN]) {
  if (opp_in_check) {
    if (noFurtherMoves(checking_state)) {
      std::cout << formatPlayer(1 - _playerToMove)
		<< " is in checkmate\n";
      _gameOver = true;
      return true;
    }
    else {
      std::cout << formatPlayer(1 - _playerToMove)
		<< " is in check\n";
      return false;
    }
  }
  else if (!opp_in_check && noFurtherMoves(checking_state)) {
    std::cout << "\nIt is stalemate\n";
    _gameOver = true;
    return true;
  }
  return false;
}
/* END OF IMPLEMENTATION */

/* UPDATE BOARD AFTER CHECKING TESTS */
void ChessBoard::printMove(std::string const piece_from,
			   std::string const piece_to) const {
  int from_rank = parseRank(piece_from), from_file = parseFile(piece_from);
  int to_rank = parseRank(piece_to), to_file = parseFile(piece_to);
  std::cout << formatPlayer(_playerToMove) << "'s "
	    << _board[from_rank][from_file]->getName() << " moves from "
	    << piece_from << " to " << piece_to;
  if (_board[to_rank][to_file])
    std::cout << " taking " << formatPlayer(1 - _playerToMove) << "'s "
	      << _board[to_rank][to_file]->getName();
  std::cout << "\n";

}

void ChessBoard::updateBoard(ChessPiece* checking_state [][BOARD_LEN],
			     std::string const pos_to) {
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);

  ChessPiece* piece_to_remove = _board[to_rank][to_file]; 
  if (piece_to_remove)
    delete piece_to_remove;

  copyState(_board, checking_state);

  ChessPiece* piece_to_update = _board[to_rank][to_file];
  updateMovedPiece(piece_to_update, pos_to);
}

void ChessBoard::updateMovedPiece(ChessPiece* piece_to_update,
				  std::string const pos_to) const {
  piece_to_update->setPos(pos_to);
  if (!piece_to_update->getAlreadyMoved())
    piece_to_update->setAlreadyMoved();  
}

void ChessBoard::switchPlayerToMove() {
  switch(_playerToMove) {
  case White: _playerToMove = Black; break;
  case Black: _playerToMove = White; break;
  }
}
/* END OF IMPLEMENTATION */

