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
6. Ba3 Nd7
7. Qe2 dxe4
8. Bxe4 Ngf6
9. Bd3 b6
10. Qxe6+ fxe6
11. Bg6#

### Output
A new chess game is started!

White’s Pawn moves from E2 to E4

Black’s Pawn moves from E7 to E6

White’s Pawn moves from D2 to D4

Black’s Pawn moves from D7 to D5

White’s Knight moves from B1 to C3

Black’s Bishop moves from F8 to B4

White’s Bishop moves from F1 to D3

Black’s Bishop moves from B4 to C3 taking White’s Knight

White is in check

White’s Pawn moves from B2 to C3 taking Black’s Bishop

Black’s Pawn moves from H7 to H6

White’s Bishop moves from C1 to A3

Black’s Knight moves from B8 to D7

White’s Queen moves from D1 to E2

Black’s Pawn moves from D5 to E4 taking White’s Pawn

White’s Bishop moves from D3 to E4 taking Black’s Pawn

Black’s Knight moves from G8 to F6

White’s Bishop moves from E4 to D3

Black’s Pawn moves from B7 to B6

White’s Queen moves from E2 to E6 taking Black’s Pawn

Black is in check

Black’s Pawn moves from F7 to E6 taking White’s Queen

White’s Bishop moves from D3 to G6

Black is in checkmate
