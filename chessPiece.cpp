#include "chessPiece.h"
#include <iostream>

ChessPiece::ChessPiece(int rank, int file, Player const colour,
		       ChessBoard* const board) :
  _board(board), _colour(colour), _pos(""), _alreadyMoved(false) {
  _pos += file + 'A';
  _pos += rank + '1'; 
}

ChessPiece::~ChessPiece(){};

std::string ChessPiece::getSymbol() const {
  return _symbol;
}

std::string ChessPiece::getName() const {
  return _name;
}

Player ChessPiece::getColour() const {
  return _colour;
}

std::string ChessPiece::getPos() const {
  return _pos;
}

void ChessPiece::setPos(std::string pos) {
  _pos = pos;
}

bool ChessPiece::getAlreadyMoved() const {
  return _alreadyMoved;
}

void ChessPiece::setAlreadyMoved() {
  _alreadyMoved = true;
}

bool ChessPiece::hittingOwnPiece(std::string const pos_to,
				 ChessPiece* board_state[][BOARD_LEN]) const {
  int from_rank = parseRank(_pos), from_file = parseFile(_pos);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);

  if(!board_state[to_rank][to_file])
    return false;
      
  Player from_piece_colour = board_state[from_rank][from_file]->getColour();
  Player to_piece_colour = board_state[to_rank][to_file]->getColour();
  return from_piece_colour == to_piece_colour;
}

bool ChessPiece::validStraightMovement(std::string const pos_to,
				       ChessPiece* board_state[][BOARD_LEN]) const {
  int from_rank = parseRank(_pos), from_file = parseFile(_pos);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);
  int rank_change = std::abs(to_rank - from_rank);
  int file_change = std::abs(to_file - from_file);
  return (!rank_change || !file_change) && clearPath(pos_to, board_state);
}


bool ChessPiece::validDiagonalMovement(std::string const pos_to,
				       ChessPiece* board_state[][BOARD_LEN]) const {
  int from_rank = parseRank(_pos), from_file = parseFile(_pos);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);
  int rank_change = std::abs(to_rank - from_rank);
  int file_change = std::abs(to_file - from_file);
  return ((rank_change - file_change) == 0) && clearPath(pos_to, board_state);
}

bool ChessPiece::clearPath(std::string const pos_to,
			   ChessPiece* board_state[][BOARD_LEN]) const {
  int from_rank = parseRank(_pos), from_file = parseFile(_pos);
  int to_rank = parseRank(pos_to), to_file = parseFile(pos_to);

  int rank_step = setStep(from_rank, to_rank);
  int file_step = setStep(from_file, to_file);
  from_rank += rank_step;
  from_file += file_step;
  
  while (from_rank != to_rank || from_file != to_file) { 
    if (board_state[from_rank][from_file])
	return false;
    from_rank += rank_step;
    from_file += file_step;
  }
  return true;
}

int ChessPiece::setStep(int const from, int const to) const {
  if (to - from > 0)
    return 1;
  if (to - from < 0)
    return -1;
  else
    return 0;
}
		    
