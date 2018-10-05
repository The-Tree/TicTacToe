//
// Created by Kenny Daily on 10/4/2018.
//

#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H


class Board {
public:
	const static int HEIGHT = 3;
	const static int WIDTH = 3;
	Board(); //initializes the board to be empty
	Board(int[HEIGHT][WIDTH]); //initializes the board given an array of size HEIGHT,WIDTH
	void printBoard(); //prints the board
	int givePiece(int, int); //is given coordinates, returns the piece at that position
	void placePiece(int, int , int); 	//is given coordinates and piece, places the piece on the board at that
	// position
	void removePiece(int, int); //removes the piece given coordinates, setting the position to empty
	bool isPositionEmpty(int, int); 	//is given coordinates, returns true if position is empty and false otherwise
	//(including if it is not a valid position)
	bool isBoardFull(); //returns true if board is entirely full and false otherwise
	int threeInARow(); 	//returns 0 if there is no team with three in a row. returns the team that has three in a row if
	//there is a team with three in a row

private:
	int board[HEIGHT][WIDTH];
};


#endif //TICTACTOE_BOARD_H
