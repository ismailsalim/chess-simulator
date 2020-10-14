#include "chessBoardHelper.h"
#include "chessPiece.h"
#include <iostream>

void printBoard(ChessPiece* board [][BOARD_LEN]) {
  for(int rank = BOARD_LEN - 1; rank >= 0; rank--) {
    std::cout << rank + 1 << "   ";
    for(int file = 0; file < BOARD_LEN; file++) {
      if(board[rank][file] == nullptr)
	std::cout << " -   ";
      else
	std::cout << board[rank][file]->getSymbol() << "  ";
    }
    std::cout << "\n\n";
  }
  std::cout <<  "     ";
  for(char ch = 'A'; ch <= 'H'; ch++)
    std::cout << ch << "    ";
  std::cout << "\n";
}

int parseRank(std::string const pos) {
  return pos[1] - '1';
}

int parseFile(std::string const pos) {
  return pos[0] - 'A';
}

int calcRankChange(std::string const pos_from, std::string const pos_to) {
  return std::abs(parseRank(pos_to) - parseRank(pos_from));
}

int calcFileChange(std::string const pos_from, std::string const pos_to) {
  return std::abs(parseFile(pos_to) - parseFile(pos_from));
}

std::string formatPos(int const rank, int const file) {
  std::string pos = "";
  pos += (file + 'A');
  pos += (rank + '1');
  return pos;
}

std::string formatPlayer(int const player) {
  return player ? "Black" : "White";
}
