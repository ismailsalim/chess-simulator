#ifndef CHESSBOARD_HELPER
#define CHESSBOARD_HELPER
#include <string>

#define BOARD_LEN 8

class ChessPiece;

/* Requires the state of the board i.e. all the pieces posistions and 
   print out a board using each piece's symbol. */
void printBoard(ChessPiece* board [][BOARD_LEN]); 

/* Requires a position string and returns the corresponding board rank index. */
int parseRank(std::string const pos);

/* Requires a position string and returns the corresponding board rank index. */
int parseFile(std::string const pos);

/* Requires two position string and returns the difference in board ranks. */
int calcRankChange(std::string const pos_from, std::string const pos_to);

/* Requires two position string and returns the difference in board files. */
int calcFileChange(std::string const pos_from, std::string const pos_to); 

/* Requires rank and file indices and returns the corresponding board position.
*/
std::string formatPos(int const rank, int const file);

/* Requires a player index and return the corresponding player string. */
std::string formatPlayer(int const player);

#endif
