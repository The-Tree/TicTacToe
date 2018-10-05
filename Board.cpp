//
// Created by Kenny Daily on 10/4/2018.
//

#include <iostream>
#include "Board.h"

//initializes the board
Board::Board(){
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			board[y][x] = 0; //declares all of board as empty
		}
	}
}

//initializes the board given an array of size HEIGHT,WIDTH
Board::Board(int otherBoard[HEIGHT][WIDTH]) {
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			board[y][x] = otherBoard[y][x]; //declares all of board as other board
		}
	}
}

//prints the board
void Board::printBoard() {
	for(int y = 0; y < HEIGHT; y++) {
		std::cout << "|";
		for(int x = 0; x < WIDTH; x++) {
			std::cout << board[y][x] << "|";
		}
		std::cout << std::endl;
	}
}

//is given coordinates, returns the piece at that position
int Board::givePiece(int x, int y) {
	return board[y][x];
}

//is given coordinates and piece, places the piece on the board at that position
void Board::placePiece(int x, int y, int piece) {
	board[y][x] = piece;
}

//removes the piece given coordinates, setting the position to empty
void Board::removePiece(int x, int y) {
	board[y][x] = 0;
}

//is given coordinates, returns true if position is empty and false otherwise (including if it is not a valid position)
bool Board::isPositionEmpty(int x, int y) {
	//if(x >= WIDTH || x, y < 0 || y >= HEIGHT) return false; (commented out bc i am not implementing checking
	//if the user is messing with me
	return board[y][x] == 0;
}

//returns true if board is entirely full and false otherwise
bool Board::isBoardFull() {
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(board[y][x] == 0) return false;
		}
	}
	return true;
}

//returns 0 if there is no team with three in a row. returns the team that has three in a row if
//there is a team with three in a row
int Board::threeInARow() {
	//if diagonal 3 in a row (y,x)
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) return board[0][0];
	else if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][0] != 0) return board[0][2];

	//if horizontal 3 in a row (y,x)
	else if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != 0) return board[0][0];
	else if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != 0) return board[1][0];
	else if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != 0) return board[2][0];

	//if vertical 3 in a row (y,x)
	else if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != 0) return board[0][0];
	else if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != 0) return board[0][1];
	else if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != 0) return board[0][2];

	//if no 3 in a row
	else return 0;
}