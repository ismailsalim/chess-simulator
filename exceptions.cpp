#include "exceptions.h"

/* submit move (parent) exception */
submitMoveError::submitMoveError(const std::string& msg) : _explanation(msg) {}
const char* submitMoveError::what() const noexcept {
  return _explanation.c_str();
}

submitMoveError::~submitMoveError(){}

/* wrong player's turn exception */
wrongPlayer::wrongPlayer(const std::string& msg, const Player player) :
  submitMoveError(msg), _player(player) {}

std::string wrongPlayer::getPlayer() const {
  return _player ? "White's turn to move!" : "Black's turn to move!"; 
}

wrongPlayer::~wrongPlayer(){}

/* invalid destination position exception */
invalidDestination::invalidDestination(const std::string& msg,
				       const std::string& dest,
				       const Player player)
  : submitMoveError(msg), _dest(dest), _player(player) {}

std::string invalidDestination::getDestination() const {
  return _dest + "!";
}

std::string invalidDestination::getPlayer() const {
  return _player ? "Black's " : "White's "; 
}

invalidDestination::~invalidDestination(){}

/* no piece at source position exception */
noPiece::noPiece(const std::string& msg, const std::string& source)
  : submitMoveError(msg), _source(source) {}

std::string noPiece::displayMessage() const {
  return "There is no piece at position " + _source + "!";
}

noPiece::~noPiece(){}

/* invalid position syntax exception */
invalidSyntax::invalidSyntax(const std::string& msg, const std::string& pos)
  : submitMoveError(msg), _pos(pos) {}

std::string invalidSyntax::getPos() const {
  return _pos;
}

invalidSyntax::~invalidSyntax(){}

/* position out of board exception */
outsideBoardError::outsideBoardError(const std::string& msg,
				     const std::string& pos)
  : submitMoveError(msg), _pos(pos) {}

std::string outsideBoardError::getPos() const {
  return _pos;
}

outsideBoardError::~outsideBoardError(){}
