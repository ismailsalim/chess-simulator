#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "player.h"
#include <exception>

class submitMoveError : public std::exception {
 public:
  submitMoveError(const std::string& msg);
  ~submitMoveError();
  const char* what() const noexcept override;
 protected:
  std::string _explanation;
};

class wrongPlayer : public submitMoveError {
 public:
  wrongPlayer(const std::string& msg, const Player player) ;
  ~wrongPlayer();
  std::string getPlayer() const;
 private:
  Player _player; 
};

class invalidDestination : public submitMoveError {
 public:
  invalidDestination(const std::string& msg, const std::string& dest,
		     const Player player) ;
  ~invalidDestination();
  std::string getDestination() const;
  std::string getPlayer() const;
 private:
  std::string _dest;
  Player _player;
};

class noPiece : public submitMoveError {
 public: 
  noPiece(const std::string& msg, const std::string& source) ;
  ~noPiece();
  std::string displayMessage() const;
 private:
  std::string _source;
};

class invalidSyntax : public submitMoveError {
 public:
  invalidSyntax(const std::string& msg, const std::string& pos) ;
  ~invalidSyntax();
  std::string getPos() const;
 private:
  std::string _pos;
};

class outsideBoardError : public submitMoveError {
 public:
  outsideBoardError(const std::string& msg, const std::string& pos) ;
  ~outsideBoardError();
  std::string getPos() const;
 private:
  std::string _pos;
};

#endif
