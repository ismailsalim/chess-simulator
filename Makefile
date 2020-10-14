OBJ = chessMain.o chessBoard.o chessBoardHelper.o chessPiece.o pawn.o knight.o bishop.o rook.o queen.o king.o exceptions.o
EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean
