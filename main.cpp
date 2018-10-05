//
// Created by Kenny Daily on 10/4/2018.
// IMPORTANT NOTE: This program wrongly assumes the user will know what to enter based off prompts and
// that the user will enter that
//
#include <iostream>
#include <string>
#include "Board.h"
#include <algorithm>

int winner; //0 if no winner yet, 1 if player 1 is winner, 2 if player 2 or robot is winner, and 3 if draw
std::string input; //the input for the game and main menu
Board gameBoard; //the gameboard for playFriend() and playRobot()
int x, y; //positions for player & ai input
bool playerTurn; //false if player1's turn true if player2's or robots turn

void clearScreen(); //clears the screen by way of adding a great amount of white space
void playFriend(); //plays tic tac toe against a friend
void playRobot(); //plays tic tac toe against an ai
int posOfMinimax(int piece, Board mBoard);	//returns where the best score as int where tens digit is y, ones
											// digit is x for the minimax is given a piece
int minimax(int, int, int, Board); //minimax for tic tac toe

int main() {

	while(input != "EXIT") {
		clearScreen();
		std::cout << "Welcome to Tic Tac Toe!" << std::endl;
		std::cout << "Indicate your preferred game-mode by selected the corresponding number. Type \"EXIT\" if";
		std::cout << "you'd like to exit the program" << std::endl;
		std::cout << "1. Play Tic Tac Toe with a friend!" << std::endl;
		std::cout << "2. Play Tic Tac Toe with a robot!" << std::endl;
		std::getline(std::cin, input);
		if(input == "1") {
			clearScreen();
			playFriend();
		}
		else if(input == "2") {
			clearScreen();
			playRobot();
		}
	}
	return 0;
}

//clears the screen by way of adding a great amount of white space
void clearScreen() {
	std::cout << std::string(50, '\n');
}

//plays tic tac toe against a friend
void playFriend() {
	gameBoard = Board();
	playerTurn = false;
	winner = 0;
	while(winner == 0) {
		clearScreen();
		std::cout << "Player " << (playerTurn + 1) << "\'s turn!" << std::endl;
		gameBoard.printBoard();

		do {
			std::cout << "Please enter a valid position in format \"x y\" (example: 0 2): ";
			getline(std::cin, input);
			x = (int)input.at(0) - 48;
			y = (int)input.at(2) - 48;
		} while(!gameBoard.isPositionEmpty(x, y));

		if(!playerTurn) gameBoard.placePiece(x, y, 1);
		else gameBoard.placePiece(x, y, 2);

		playerTurn = !playerTurn;

		if(gameBoard.isBoardFull() && gameBoard.threeInARow() == 0) {
			winner = 3;
		}
		else {
			winner = gameBoard.threeInARow();
		}
	}

	clearScreen();
	if(winner == 3) {
		std::cout << "Congratulations! It was a draw!" << std::endl;
	}
	else {
		std::cout << "Congratulations! Player " << winner << " won!" << std::endl;
	}

	gameBoard.printBoard();

	std::cout << "Enter \"EXIT\" to exit. ";
	std::cout << "Enter anything else to continue to the main menu . . . " << std::endl;
	getline(std::cin, input);
	if(input == "2") {
		input = "";
	}
}

//plays tic tac toe against an ai
void playRobot() {
	int robotChoice = 0; //tens is y ones is x
	gameBoard = Board();
	//gameBoard.placePiece(0, 0, 1); where ill go
//	gameBoard.placePiece(1, 0, 1);
	//gameBoard.placePiece(2, 0, 2);

//	gameBoard.placePiece(0, 1, 2);
//	gameBoard.placePiece(1, 1, 1);
	//gameBoard.placePiece(2, 1, 2);

//	gameBoard.placePiece(0, 2, 1);
//	gameBoard.placePiece(1, 2, 2);
//	gameBoard.placePiece(2, 2, 2);


	playerTurn = false;
	winner = 0;
	while(winner == 0) {
		if(!playerTurn) {
			clearScreen();
			std::cout << "It's your turn!" << std::endl;
			gameBoard.printBoard();

			do {
				std::cout << "Please enter a valid position in format \"x y\" (example: 0 2): ";
				getline(std::cin, input);
				x = (int)input.at(0) - 48;
				y = (int)input.at(2) - 48;
			} while(!gameBoard.isPositionEmpty(x, y));

			gameBoard.placePiece(x, y, 1);
		}
		else {
			robotChoice = posOfMinimax(2, gameBoard);

			if(robotChoice < 10) y = 0; //if robot choice is less than 10, y digit is 0
			else if(robotChoice < 20) y = 1; //if robot choice is less than 20 and greater than or = 10, y digit is 1
			else if(robotChoice < 30) y = 2; //if robot choice is less than 30 and greater than or = 20, y digit is 2

			x = robotChoice - (y*10); //x is robotChoice - y*10 (could technically

			gameBoard.placePiece(x, y, 2);
		}

		playerTurn = !playerTurn;

		if(gameBoard.isBoardFull() && gameBoard.threeInARow() == 0) {
			winner = 3;
		}
		else {
			winner = gameBoard.threeInARow();
		}
	}

	clearScreen();
	if(winner == 3) std::cout << "Congratulations! It was a draw!" << std::endl;
	else if(winner == 2) std::cout << "I'm sorry! The robot has won!" << std::endl;
	else std::cout << "Congratulations! You have won!" << std::endl;

	gameBoard.printBoard();

	std::cout << "Enter \"EXIT\" to exit. ";
	std::cout << "Enter anything else to continue to the main menu . . . " << std::endl;
	getline(std::cin, input);
}

//returns where the best score as int where tens digit is y, ones digit is x for the minimax is given a piece
//how it works
//traverse all places on board and add piece if empty
//minimax with that board, compare to highest score
//if greater than highest score, change highest score and pos to this one
//remove the piece at that position
//return pos
int posOfMinimax(int piece, Board mBoard) {
	int pos = 0; //tens digit is y, ones digit is x
	int max = -1000;
	int score = -1500;
	int nextPiece = piece;
	//if(piece == 1) nextPiece = 2;
	//else if(piece == 2) nextPiece = 1;

	for(int y = 0; y < mBoard.HEIGHT; y++) {
		for(int x = 0; x < mBoard.WIDTH; x++) {
			if(mBoard.isPositionEmpty(x, y)) {
				mBoard.placePiece(x, y, piece);
				score = minimax(0, piece, nextPiece, mBoard);
				if(max < score) {
					max = score;
					pos = (y * 10) + (x * 1);
				}
				mBoard.removePiece(x, y);

				std::cout << "Pos(x,y)=(" << x << "," << y << ") Score=" << score << " Max=" << max << std::endl;
			}
		}
	}
	return pos;
}

//minimax for tic tac toe
//how it works:
//if game is still going
	//if currpiece == maximizing player
		//traverse all places on board and add piece if empty
		//minimax with that board, compare to highest score
		//if greater than highest score, change highest score
		//remove the piece at that position
	//else
		//traverse all places on board and add piece if empty
		//minimax with that board, compare to lowest score
		//if lower than lowest score, change lowest score
		//remove the piece at that position
	//return either highest or lowest score depending
//else if maximizing player wins return 15 - depth
//else if board is full (draw) return 0 - depth
//else (if the game is over, its not a draw, and the maximizing player did not win) return -15 + depth
int minimax(int depth, int maximizingPlayer, int currPiece, Board mBoard) {
	int bestScore;
	int nextPiece;
	if(currPiece == 1) nextPiece = 2;
	else nextPiece = 1;

	if(mBoard.threeInARow() == 0) {
		if(currPiece == maximizingPlayer) {
			bestScore = -1000;

			for(int y = 0; y < mBoard.HEIGHT; y++) {
				for(int x = 0; x < mBoard.WIDTH; x++) {
					if(mBoard.isPositionEmpty(x, y)) {
						mBoard.placePiece(x, y, nextPiece);
						bestScore = std::max(bestScore, minimax(depth+1, maximizingPlayer,
																nextPiece, mBoard));
						mBoard.removePiece(x, y);
					}
				}
			}
		}
		else {
			bestScore = 1000;

			for(int y = 0; y < mBoard.HEIGHT; y++) {
				for(int x = 0; x < mBoard.WIDTH; x++) {
					if(mBoard.isPositionEmpty(x, y)) {
						mBoard.placePiece(x, y, nextPiece);
						bestScore = std::min(bestScore, minimax(depth + 1, maximizingPlayer,
																nextPiece, mBoard));
						mBoard.removePiece(x, y);
					}
				}
			}
		}
		return bestScore;
	}
	else if(mBoard.threeInARow() == maximizingPlayer) return 15 - depth;
	else if(mBoard.isBoardFull()) return 0;
	else return -20 + depth;
}