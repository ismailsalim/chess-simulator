# Chess Simulator

A program that simulates and manages chess games. It accept moves in the format (source square, destination square), where a square is referred to using a letter in the range A-H and a number in the range 1-8. It validates each move and keeps track of the state of the game, detecting when the game is over and producing appropriate output to the user.

## Example 
The specific game which is simulated in the main function found in ChessMain.cpp is a short game played between Alexander Alekhine, and his opponent Vasic in 1931. In algebraic chess notation, the game played out as follows:

### Input
1. e4 e6
2. d4 d5
3. Nc3 Bb4
4. Bd3 Bxc3+
5. bxc3 h6
2
6. Ba3 Nd7
7. Qe2 dxe4
8. Bxe4 Ngf6
9. Bd3 b6
10. Qxe6+ fxe6
11. Bg6#

### Output
A new chess game is started!
It is not Black’s turn to move!
There is no piece at position D4!
White’s Pawn moves from D2 to D4
Black’s Bishop cannot move to B4!
