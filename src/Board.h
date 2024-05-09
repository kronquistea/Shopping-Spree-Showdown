/***********************************
 * Class Name: Board
 * 
 * Description: This header file contains the class declaration for Board
 * and it's constructors, getters and setters
 * A Board has a 2D array/vector of Cells
 * A Board has a vector of Token pointers
***********************************/

#ifndef BOARD_H
#define BOARD_H

#include "Token.h"
#include "Cell.h"
#include <iostream>
   using std::ostream;
#include <array>
   using std::array;
#include <vector>
   using std::vector;

extern int turnCounter;

class Board {
   friend ostream& operator << (ostream& output, Board& gameBoard);
   public:
      // Constructors
      /* @brief Default constructor for Board, will never be used*/
      Board();
      /* @brief Parameterized constructor for Board, will create token pointers based on how many players/computer should be in the game
      @param int itemInitializationOption
      @param int players
      @param int computers*/
      explicit Board(int itemInitializationOption, int players, int computers);

      // Getters
      // @brief Gets the 2D vector of Cells
      // @return array2DCells cellsOnBoard
      array<array<Cell, 5>, 5> getCellsOnBoard();
      // @brief Gets the vector of Token pointers
      // @return vector<Token*> tokenPtrs
      vector<Token*> getTokenPtrs();

      // Setters
      // @brief Sets each Cell for the game board (5x5)
      // @param array2DCells cellsOnBoard
      void setCellsOnBoard(array<array<Cell, 5>, 5> cellsOnBoard);
      // @brief Sets the vector of Token pointers
      // @param vector<Token*> tokenPtrs
      void setTokenPtrs(vector<Token*> tokenPtrs);

      // Other Functions
      // @brief Creates each cell on the board, is only called in the constructor
      // @param int int itemInitializationOption
      // @return array<array<Cell, 5>, 5> arrayOfCells
      array<array<Cell, 5>, 5> createCellsOnBoard(int itemInitializationOption);
      // @brief Creates new Token ptrs and is only called in the constructor
      // @param int players
      // @param int computers*/
      void createTokenPtrs(int players, int computers);
      // @brief Initiates the movement phase for each Token in the game
      // @param array2DCells cellsVector
      // @param vector<Token*> tokenPtrVector*
      void move(array<array<Cell, 5>, 5> &cellsArray, vector<Token*> &tokenPtrVector);
      // @brief Checks that the Player is moving to an adjacent Cell and is not just jumping around
      // @param Token* playerToMove
      // @param int row
      // @param int col
      // @return bool adjacentCell
      bool movementToAdjacentCell(const Token* playerToMove, int rowToMoveTo, int colToMoveTo);
      // @brief Checks if the game is over - either all Tokens have maxed out their budgets OR all ItemBoxes have been opened
      // @param vector<Item*> vectorOfTokens
      // @return gameOver
      bool gameOverCheck(vector<Token*> vectorOfTokens);
      // @brief Prints out the summary card of the winner at the end of the game
      void printSummaryCard();
      // @brief Prints out more in-depth statistics of the winner to the terminal and all Tokens' statistics to GameSummary.txt
      void printStatistics();
      // @brief Check if Player is boxed out by opponents and then move them to a random location
      // @param currentRow
      // @param currentCol
      // @return bool boxedOut
      bool playerBoxedOut(const int currentRow, const int currentCol);
   private:
         // Member Variables
         array<array<Cell, 5>, 5> cellsOnBoard; 
         vector<Token*> tokenPtrs;
};

#endif