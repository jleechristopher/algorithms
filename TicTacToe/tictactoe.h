// TIC TAC TOE
// This program simulates a game of tic tac toe. Input is validated to be an integer within the bounds of [1,9]. 
// The program keeps an array of possible win conditions (one for each way to get 3 in a row) and adds the player
// ID in the corresponding entries. If one of the entries reaches 3x a player's ID, that player is pronounced the 
// winner and the game ends. For example, if X's ID is 1 and O's ID is 4, X wins if an entry reaches 3. O wins if 
// an entry reaches 12.
// 
// Example win condition array and placement
//     0
// 123|1
// 456|2
// 789|3
//---- 4
// 765 
// Player X places a piece on the 1 spot. Player X is represented by the number "1" so 1 is added to the
// corresponding win condition entries 1 (horizontal line win), 4 (diagonal line win), 7 (vertical line win)
//
// Author: Chris Lee
// Date: June 8th, 2018
// Last Edited: June 8th, 2018

#ifndef __TIC_TAC_TOE__
#define __TIC_TAC_TOE__

#include <iostream>
#include <sstream>
#include <array>
#include <limits> // numeric_limits

#define NUM_COL 3
#define NUM_TILES 9
#define WAYS_TO_WIN 8
#define X_PLAYER 1
#define O_PLAYER 4
#define X_WIN_CONDITION 3 // sum of 3 X_PLAYER moves
#define O_WIN_CONDITION 12 // sum of 3 O_PLAYER moves
#define CONTINUE 0
#define DRAW -1

class TicTacToe
{
public:
	TicTacToe(): m_currentPlayer{X_PLAYER}, m_numMoves{0}
	{
		for (int ii = 0; ii < NUM_TILES; ++ii)
		{
			m_gameBoard[ii] = 0;
		}
		for (int ii = 0; ii < WAYS_TO_WIN; ++ii)
		{
			m_moveSums[ii] = 0;
		}
	}
	void play()
	{
		drawBoard();
		while(gameStatus() == CONTINUE)
		{
			getMove();
			if (!placePiece())
			{
				std::cout << "That spot is occupied. Please choose another space." << std::endl;
				continue;
			}
			togglePlayer();
			drawBoard();
		}
		int status = gameStatus();
		if (status == DRAW)
		{
			std::cout << "The game is a draw." << std::endl;
		}
		else if (status == X_PLAYER)
		{
			std::cout << "X wins!" << std::endl;
		}
		else
		{
			std::cout << "O wins!" << std::endl;
		}
	}
private:
	std::array<int, NUM_TILES> m_gameBoard;
	std::array<int, WAYS_TO_WIN> m_moveSums; 
	std::stringstream m_output;
	int m_nextMove;
	int m_currentPlayer;
	int m_numMoves;

	void getMove()
	{
		std::cout << "Please enter a move. ";
		if (m_currentPlayer == X_PLAYER)
		{
			std::cout << "(X's move)" << std::endl;
		}
		else
		{
			std::cout << "(O's move)" << std::endl;
		}				
		while(true)
		{
			std::cin >> m_nextMove;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a valid move." << std::endl;
			}
			else if ((m_nextMove > 9) || (m_nextMove < 1))
			{
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a valid move." << std::endl;
			}
			else
			{
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any further input
				break;
			}
		}
	}

	void togglePlayer()
	{
		if (m_currentPlayer == X_PLAYER)
		{
			m_currentPlayer = O_PLAYER;
		}
		else
		{
			m_currentPlayer = X_PLAYER;
		}
	}
	void drawBoard()
	{
		m_output.str(std::string());
		m_output.clear();
		m_output << std::endl;
		for (int ii = 0; ii < NUM_TILES; ++ii)
		{
			if (m_gameBoard[ii] == X_PLAYER)
			{
				m_output << "X";
			}
			else if (m_gameBoard[ii] == O_PLAYER)
			{
				m_output << "O";
			}
			else
			{
				m_output << ii + 1;
			}
			if ((ii == 2) || (ii == 5))
			{
				m_output << std::endl;
				m_output << "-   -   -" << std::endl;
			}
			else if (ii != 8)
			{
				m_output << " | ";
			}
		}
		m_output << std::endl;
		std::cout << m_output.str();
	}
	int gameStatus()
	{
		if (m_numMoves < 5) // a win can't occur before the 5th move
		{
			return CONTINUE;
		}
		for (int ii = 0; ii < WAYS_TO_WIN; ++ii)
		{
			if (m_moveSums[ii] == X_WIN_CONDITION)
			{
				return X_PLAYER;
			}
			if (m_moveSums[ii] == O_WIN_CONDITION)
			{
				return O_PLAYER;
			}
		}
		if (m_numMoves == NUM_TILES)
		{
			return DRAW;
		}
		return CONTINUE;
	}

	bool placePiece()
	{
		if (m_gameBoard[m_nextMove - 1]) // subtract 1 because m_nextMove is 1-indexed
		{
			return false;
		}
		else
		{
			m_gameBoard[m_nextMove - 1] = m_currentPlayer; 
		}

		if (m_nextMove == 1)
		{
			m_moveSums[1] += m_currentPlayer;
			m_moveSums[4] += m_currentPlayer;
			m_moveSums[7] += m_currentPlayer;
		}
		else if (m_nextMove == 2)
		{
			m_moveSums[1] += m_currentPlayer;
			m_moveSums[6] += m_currentPlayer;
		}
		else if (m_nextMove == 3)
		{
			m_moveSums[0] += m_currentPlayer;
			m_moveSums[1] += m_currentPlayer;
			m_moveSums[5] += m_currentPlayer;
		}
		else if (m_nextMove == 4)
		{
			m_moveSums[2] += m_currentPlayer;
			m_moveSums[7] += m_currentPlayer;
		}
		else if (m_nextMove == 5)
		{
			m_moveSums[0] += m_currentPlayer;
			m_moveSums[2] += m_currentPlayer;
			m_moveSums[4] += m_currentPlayer;
			m_moveSums[6] += m_currentPlayer;
		}
		else if (m_nextMove == 6)
		{
			m_moveSums[2] += m_currentPlayer;
			m_moveSums[5] += m_currentPlayer;
		}
		else if (m_nextMove == 7)
		{
			m_moveSums[0] += m_currentPlayer;
			m_moveSums[3] += m_currentPlayer;
			m_moveSums[7] += m_currentPlayer;
		}
		else if (m_nextMove == 8)
		{
			m_moveSums[3] += m_currentPlayer;
			m_moveSums[6] += m_currentPlayer;
		}
		else
		{
			m_moveSums[3] += m_currentPlayer;
			m_moveSums[4] += m_currentPlayer;
			m_moveSums[5] += m_currentPlayer;
		}

		++m_numMoves;
		return true;
	}
};

#endif