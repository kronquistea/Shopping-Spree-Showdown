/*********************************************************
* Summary: This file includes the implementation for the Board class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       22 Apr 2024 - Created Board.cpp
*       23 Apr 2024 - Changed the 2D Vector to a 2D Array
*       24 Apr 2024 - Stopped deleting new Tokens, was causing problems
*       24 Apr 2024 - Included openItemBox for all Tokens when being created a being moved
*       24 Apr 2024 - Exception handling to ensure the Player wants to move to a valid cell
*       24 Apr 2024 - Ensuring the Player is being created at a valid location on the Board
*       25 Apr 2024 - Added userPowerUp function call inside move function
*       25 Apr 2024 - Added functionality for movement ban status inside move function, also created global variable turnCounter
*       26 Apr 2024 - Created printSummaryCard function
*       27 Apr 2024 - Print all Tokens' statistics to the GameSummary.txt file
********************************************************/

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;
#include <iomanip>
    using std::setw;
    using std::setfill;
    using std::left;
    using std::right;
#include <fstream>
    using std::ofstream;
#include "Board.h"
#include "Player.h"
#include "Computer.h"

const int BOARDSIZE = 5;

// Constructors
Board::Board() {
    setCellsOnBoard(createCellsOnBoard(1));
    createTokenPtrs(0, 0);
}

Board::Board(int itemInitializationOption, int players, int computers) {
    setCellsOnBoard(createCellsOnBoard(itemInitializationOption));
    createTokenPtrs(players, computers);
}

// Overloaded Operators
ostream& operator << (ostream& output, Board& gameBoard) {
    // PRINTS OUT HEADER
    output << "\n---------- BOARD STATE AT END OF TURN " << turnCounter << " ----------" << endl;
    // PRINTS OUT ITEM BOXES
    for(int i = 0; i < gameBoard.getCellsOnBoard().size(); i++) {
        for(int j = 0; j < gameBoard.getCellsOnBoard()[i].size(); j++) {
            if(gameBoard.getCellsOnBoard()[i][j].getItemBox() == nullptr) {
                output << "x";
            }
            else if(gameBoard.getCellsOnBoard()[i][j].getItemBox() != nullptr) {
                output << "i";
            }
            if(gameBoard.getCellsOnBoard()[i][j].getTokenPtr() == nullptr) {
                output << "n ";
            }
            else if(gameBoard.getCellsOnBoard()[i][j].getTokenPtr()->getTokenType() == "PLAYER") {
                output << "P" << gameBoard.getCellsOnBoard()[i][j].getTokenPtr()->getTokenNum();
            }
            else if(gameBoard.getCellsOnBoard()[i][j].getTokenPtr()->getTokenType() == "COMPUTER"){
                output << "C" << gameBoard.getCellsOnBoard()[i][j].getTokenPtr()->getTokenNum();
            }
            output << " ";
        }
        output << endl;
    }
    // PRINTS OUT ENDING DASHES
    if(turnCounter < 10) {
        output << setw(50) << setfill('-') << "-" << endl;
    }
    else {
        output << setw(51) << setfill('-') << "-" << endl;
    }
    return output;
}

// Getters
array<array<Cell, 5>, 5> Board::getCellsOnBoard() {
    return this->cellsOnBoard;
}

vector<Token*> Board::getTokenPtrs() {
    return this->tokenPtrs;
}

// Setters
void Board::setCellsOnBoard(array<array<Cell, 5>, 5> cellsOnBoard) {
    this->cellsOnBoard = cellsOnBoard;
}

void Board::setTokenPtrs(vector<Token*> tokenPtrs) {
    this->tokenPtrs = tokenPtrs;
}

// Other Functions
array<array<Cell, 5>, 5> Board::createCellsOnBoard(int itemInitializationOption) {
    // Creates a 2D array of Cells using the parameterized constructor
    array<array<Cell, 5>, 5> cells {{
        {Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption)},
        {Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption)},
        {Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption)},
        {Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption)},
        {Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption), Cell(itemInitializationOption)}
    }};

    return cells;
}

void Board::createTokenPtrs(int players, int computers) {
    array<array<Cell, 5>, 5> cells = getCellsOnBoard();
    vector<Token*> tokenPtrsStart;

    if(players > 0) {
        cout << "\n-------------------- CREATING PLAYERS --------------------" << endl;
        for(int i = 0; i < players; i++) {
            cout << "---------- PLAYER " << i + 1 << " ----------" << endl;

            int row = 1;
            int col = 1;

            cout << "Enter the Y coordinate you would like to start on (1 - 5) (Top -> Bottom): ";
            cin >> row;
            cout << "Enter the X coordinate you would like to start on (1 - 5) (Left -> Right): ";
            cin >> col;
            row--;
            col--;

            Player* newPlayerPtr = nullptr;

            bool playerMade = false;
            while(!playerMade) {
                if(row <= 4 && row >= 0 && col <= 4 && col >= 0 && getCellsOnBoard()[row][col].cellIsFree()) {
                    newPlayerPtr = new Player(i + 1, row, col);
                    tokenPtrsStart.push_back(newPlayerPtr);

                    Cell desiredCell = getCellsOnBoard()[row][col];
                    desiredCell.setTokenPtr(newPlayerPtr);
                    cells[row][col] = desiredCell;

                    playerMade = true;
                }
                else {
                    cout << "Please enter a valid Cell!" << endl;
                    cout << "Enter the Y coordinate you would like to start on (1 - 5) (Top -> Bottom): ";
                    cin >> row;
                    cout << "Enter the X coordinate you would like to start on (1 - 5) (Left -> Right): ";
                    cin >> col;
                    row--;
                    col--;
                }
            }

            if(cells[row][col].getItemBox() != nullptr) {
                cells[row][col].openItemBox(newPlayerPtr);
            }

            setCellsOnBoard(cells);
        }
    }
    if(computers > 0) {
        cout << "\n-------------------- CREATING COMPUTERS --------------------" << endl;
        for(int i = 0; i < computers; i++) {
            cout << "---------- COMPUTER " << i + 1 << " ----------" << endl;
            int randomRow;
            int randomCol;

            bool cellIsTaken = false;
            while(!cellIsTaken) {
                try {
                    randomRow = rand() % 5;
                    randomCol = rand() % 5;

                    // cout << "Computer randomRow & randomCol : " << randomRow << " & " << randomCol << endl;

                    if(cells[randomRow][randomCol].cellIsFree()) {
                        cout << "Computer " << i + 1 << " is spawning on Cell (" << randomRow << "," << randomCol << ")" << endl;
                        cellIsTaken = true;
                    }
                }
                catch(const char* e) {
                    cout << e << " - Generating a new Cell for the Computer" << endl;
                }
            }

            Computer* newComputerPtr = new Computer(i + 1, randomRow, randomCol);
            tokenPtrsStart.push_back(newComputerPtr);

            Cell desiredCell = getCellsOnBoard()[newComputerPtr->getTokenRow()][newComputerPtr->getTokenCol()];
            desiredCell.setTokenPtr(newComputerPtr);
            cells[newComputerPtr->getTokenRow()][newComputerPtr->getTokenCol()] = desiredCell;

            if(cells[randomRow][randomCol].getItemBox() != nullptr) {
                cells[randomRow][randomCol].openItemBox(newComputerPtr);
            }

            setCellsOnBoard(cells);
        }
    }
    cout << "\n---------- Starting Budget/Points for each token ----------" << endl;
    for(int i = 0; i < tokenPtrsStart.size(); i++) {
        cout << "Starting Budget/Points for Token " << i << " : " << tokenPtrsStart[i]->getTokenBudget() << "/" << tokenPtrsStart[i]->getTokenPoints() << endl;
    }
    setTokenPtrs(tokenPtrsStart);
}

void Board::move(array<array<Cell, 5>, 5> &cells, vector<Token*> &tokenPtrVector) {
    for(int i = 0; i < tokenPtrVector.size(); i++) {
        cout << "\n-------------------- TOKEN " << (i + 1) << " --------------------" << endl;
        if(tokenPtrVector[i]->getTokenVectorOfItems().size() > 0) {
            // cout << "CALLING USEPOWERUP" << endl;
            tokenPtrVector[i]->usePowerUp();
        }

        // If true skip the movement phase for at least this turn for each Token who has the movementBanStatus variable set to true
        if(tokenPtrVector[i]->getMovementBanStatus()) {
            int turnsLeftOnBan = turnCounter - tokenPtrVector[i]->getMovementBanStartTurn();
            switch(turnsLeftOnBan) {
                case 1:
                    cout << "You will be able to move again in 2 turns!\n" << endl;
                    break;
                case 2:
                    cout << "You will be able to move again next turn!\n" << endl;
                    break;
                case 3:
                    tokenPtrVector[i]->setMovementBanStatus(false);
                    break;
            }
        }

        if(tokenPtrVector[i]->getTokenType() == "PLAYER" && !(tokenPtrVector[i]->getMovementBanStatus())) {
            cout << "Start of Turn Points/Budget" << endl;
            cout << "Player Points : " << tokenPtrVector[i]->getTokenPoints() << endl;
            cout << "Player Budget : " << tokenPtrVector[i]->getTokenBudget() << "\n\n";
            bool moved = false;
            int row = 0;
            int col = 0;

            // If the Player is unable to move then tell them they are being randomly moved and then move them
            if(playerBoxedOut(tokenPtrVector[i]->getTokenRow(), tokenPtrVector[i]->getTokenCol())) {
                // Let user know they are being moved to random Cell
                char continueTurn;
                cout << "You are boxed out and being moved to a random cell!" << endl;

                bool cellIsOpen = false;
                while(!cellIsOpen) {
                    try {
                        // Generate a random Cell
                        row = rand() % 5;
                        col = rand() % 5;
                        if(cells[row][col].cellIsFree()) {
                            cellIsOpen = true;
                            cout << "You are being moved to Cell (" << row + 1 << "," << col + 1 <<")" << endl;
                            cout << "Enter any key and click Enter to continue: ";
                            cin >> continueTurn;

                            // Removes the Player from the old cell by setting the tokenPtr to nullptr
                            cells[tokenPtrVector[i]->getTokenRow()][tokenPtrVector[i]->getTokenCol()].setTokenPtr(nullptr);
                            // Set coordinates of Player Token to desired coordinates
                            tokenPtrVector[i]->setCoordinates(row, col);
                            // Set the desired Cell to have a tokenPtr of the player instance
                            cells[row][col].setTokenPtr(tokenPtrVector[i]);
                            moved = true;
                        }
                    }
                    catch(const char* e) {
                        cout << e << endl;
                        cout << "Generating a new Cell" << endl;
                    }
                }
            }
            else {
                cout << "Which cell would you like to move to? (You are currently at Cell (" << tokenPtrVector[i]->getTokenRow() + 1 << "," << tokenPtrVector[i]->getTokenCol() + 1 << ")" << endl;
                cout << "Enter the Y coordinate (must be adjacent to current location) (1 - 5): ";
                cin >> row;
                cout << "Enter the X coordinate (must be adjacent to current location) (1 - 5): ";
                cin >> col;

                cout << endl;

                row--;
                col--;
            }

            while(!moved) {
                try {
                    // If the Cell is available then execute if statement
                    if(movementToAdjacentCell(tokenPtrVector[i], row, col) && cells[row][col].cellIsFree()) {
                        // Removes the Player from the old cell by setting the tokenPtr to nullptr
                        cells[tokenPtrVector[i]->getTokenRow()][tokenPtrVector[i]->getTokenCol()].setTokenPtr(nullptr);
                        // Set coordinates of Player Token to desired coordinates
                        tokenPtrVector[i]->setCoordinates(row, col);
                        // Set the desired Cell to have a tokenPtr of the player instance
                        cells[row][col].setTokenPtr(tokenPtrVector[i]);
                        moved = true;
                    }
                }
                // Otherwise prompt user to enter a valid cell
                catch(const char* e) {
                    cout << e << endl;
                    cout << "Enter the Y coordinate (must be adjacent to current location) (1 - 5): ";
                    cin >> row;
                    cout << "Enter the X coordinate (must be adjacent to current location) (1 - 5): ";
                    cin >> col;

                    row--;
                    col--;

                    moved = false;
                }
            }

            if(cells[row][col].getItemBox() != nullptr) {
                cells[row][col].openItemBox(tokenPtrVector[i]);
            }

            setCellsOnBoard(cells);
            cout << "End of Turn Points/Budget" << endl;
            cout << "Player Points : " << tokenPtrVector[i]->getTokenPoints() << endl;
            cout << "Player Budget : " << tokenPtrVector[i]->getTokenBudget() << endl;

            char endTurn;
            cout << "Enter an key and then press enter to end your turn: ";
            cin >> endTurn;
        }
        else if(tokenPtrVector[i]->getTokenType() == "COMPUTER" && !(tokenPtrVector[i]->getMovementBanStatus())) {
            cout << "Start of Turn Points/Budget" << endl;
            cout << "Computer Points : " << tokenPtrVector[i]->getTokenPoints() << endl;
            cout << "Computer Budget : " << tokenPtrVector[i]->getTokenBudget() << "\n\n";
            bool moved = false;
            // Generate random coordinates
            int row = rand() % BOARDSIZE;
            int col = rand() % BOARDSIZE;
            while(!moved) {
                try {
                    // If the Cell is available then execute if statement
                    if(cells[row][col].cellIsFree()) {
                        // Removes the Computer from the old cell and sets the tokenPtr to nullptr
                        cells[tokenPtrVector[i]->getTokenRow()][tokenPtrVector[i]->getTokenCol()].setTokenPtr(nullptr);
                        // Set coordinates of Computer Token to the randomly generated coordinates
                        tokenPtrVector[i]->setCoordinates(row, col);
                        // Sets the tokenPtr for the Cell to move to
                        cells[row][col].setTokenPtr(tokenPtrVector[i]);
                        cout << "Computer " << i + 1 << " is now at Cell (" << row << "," << col << ")\n" << endl;
                        moved = true;
                    }
                }
                catch(const char* e) {
                    row = rand() % BOARDSIZE;
                    col = rand() % BOARDSIZE;
                }
            }
            if(cells[row][col].getItemBox() != nullptr) {
                cells[row][col].openItemBox(tokenPtrVector[i]);
            }
            setCellsOnBoard(cells);
            cout << "End of Turn Points/Budget" << endl;
            cout << "Computer Points : " << tokenPtrVector[i]->getTokenPoints() << endl;
            cout << "Computer Budget : " << tokenPtrVector[i]->getTokenBudget() << endl;
        }
    }
    setTokenPtrs(tokenPtrVector);
}

bool Board::movementToAdjacentCell(const Token* playerToMove, const int rowToMoveTo, const int colToMoveTo) {
    bool adjacentCell;
    // Ensure the Cell the Player wants to move to is not out of bounds
    if(rowToMoveTo > 4 || rowToMoveTo < 0 || colToMoveTo > 4 || colToMoveTo < 0) {
        throw("Please enter a Cell within the game board boundaries!");
    }
    else {
        // Cell Player wants to move to is straight left
        if(rowToMoveTo == playerToMove->getTokenRow() && colToMoveTo == playerToMove->getTokenCol() - 1) {
            adjacentCell = true;
        }
        // Cell Player wants to move to is straight up
        else if(rowToMoveTo == playerToMove->getTokenRow() - 1 && colToMoveTo == playerToMove->getTokenCol()) {
            adjacentCell = true;
        }
        // Cell Player wants to move to is straight right
        else if(rowToMoveTo == playerToMove->getTokenRow() && colToMoveTo == playerToMove->getTokenCol() + 1) {
            adjacentCell = true;
        }
        // Cell Player wants to move to is straight down
        else if(rowToMoveTo == playerToMove->getTokenRow() + 1 && colToMoveTo == playerToMove->getTokenCol()) {
            adjacentCell = true;
        }
        else {
            throw("Please enter an adjacent Cell!");
        }
    }
    return adjacentCell;
}

bool Board::gameOverCheck(vector<Token*> vectorOfTokens) {
    bool gameOver = false;
    array<array<Cell, 5>, 5> cells = getCellsOnBoard();
    // First check if all ItemBoxes are empty
    int emptyCells = 0;
    for(int i = 0; i < cells.size(); i++) {
        for(int j = 0; j < cells[i].size(); j++) {
            if(cells[i][j].getItemBox() == nullptr) {
                emptyCells++;
            }
        }
    }
    // If not all Cells are empty then check if all Tokens have used up all their money
    int emptyBudgets = 0;
    for(int i = 0; i < vectorOfTokens.size(); i++) {
        if(vectorOfTokens[i]->getTokenBudget() == 0) {
            emptyBudgets++;
        }
    }
    if(emptyCells == 25 || emptyBudgets == vectorOfTokens.size()) {
        gameOver = true;
    }
    return gameOver;
}

/*
Format of Winner Summary Card
**************************
Winner:       Token (Player or Computer) #
Points:       Token Points
Money Left:   Token Budget
**************************
*/
void Board::printSummaryCard() {
    // Track the winning token, points and money left
    int winningTokenNum = 1;
    int winningTokenPoints = getTokenPtrs()[0]->getTokenPoints();
    int winningTokenMoney = getTokenPtrs()[0]->getTokenBudget();
    string winningTokenType = getTokenPtrs()[0]->getTokenType();
    // For loop to determine the winning player
    for(int i = 0; i < getTokenPtrs().size(); i++) {
        if(getTokenPtrs()[i]->getTokenPoints() > winningTokenPoints) {
            winningTokenNum = i + 1;
            winningTokenPoints = getTokenPtrs()[i]->getTokenPoints();
            winningTokenMoney = getTokenPtrs()[i]->getTokenBudget();
            winningTokenType = getTokenPtrs()[i]->getTokenType();
        }
    }
    // Print the statstics in the above format
    cout << setw(23) << setfill('*') << "" << endl;
    cout << left << setw(11) << setfill(' ') << "Winner:" << right << setw(10) << winningTokenType << " " << winningTokenNum << endl;
    cout << left << setw(11) << "Points:" << right << setw(12) << winningTokenPoints << endl;
    cout << left << setw(11) << "Money Left:" << right << setw(12) << winningTokenMoney << endl;
    cout << setw(23) << setfill('*') << "" << endl;
}

/*
Format of the statistics
*****************************
Type: Token (Computer/Player)
Points: # Points
Money Left: Budget
Current Cell: (row, col)
# Of Debuffs Gained: # of Debuffs
Special Items Gained and When:
    (Turn Number) - (Type)
    (Turn Number) - (Type)
    (Turn Number) - (Type)
    (Turn Number) - (Type)
    etc
*****************************
*/
void Board::printStatistics() {
    // Create variables for all necessary data to print
    string winningTokenType = getTokenPtrs()[0]->getTokenType();
    int winningTokenPoints = getTokenPtrs()[0]->getTokenPoints();
    int winningTokenBudget = getTokenPtrs()[0]->getTokenBudget();
    int winningTokenRow = getTokenPtrs()[0]->getTokenRow();
    int winningTokenCol = getTokenPtrs()[0]->getTokenCol();
    int winningNumDebuffsUsed = getTokenPtrs()[0]->getNumDebuffsUsed();
    vector<int> winningSpecialItemsGainedTurns = getTokenPtrs()[0]->getSpecialItemsGainedTurns();
    vector<string> winningSpecialItemsGained = getTokenPtrs()[0]->getSpecialItemsGained();
    vector<string> winningNormalItemsGained = getTokenPtrs()[0]->getNormalItemsGained();

    ofstream outfile;
    outfile.open("./GameSummary.txt");

    // Find the winning Token and set all the variables to that Token's values
    for(int i = 0; i < getTokenPtrs().size(); i++) {
        if(getTokenPtrs()[i]->getTokenPoints() > winningTokenPoints) {
            winningTokenType = getTokenPtrs()[i]->getTokenType();
            winningTokenPoints = getTokenPtrs()[i]->getTokenPoints();
            winningTokenBudget = getTokenPtrs()[i]->getTokenBudget();
            winningTokenRow = getTokenPtrs()[i]->getTokenRow();
            winningTokenCol = getTokenPtrs()[i]->getTokenCol();
            winningNumDebuffsUsed = getTokenPtrs()[i]->getNumDebuffsUsed();
            winningSpecialItemsGainedTurns = getTokenPtrs()[i]->getSpecialItemsGainedTurns();
            winningSpecialItemsGained = getTokenPtrs()[i]->getSpecialItemsGained();
            winningNormalItemsGained = getTokenPtrs()[i]->getNormalItemsGained();
        }
        // Print all the statistics
        // PRINT THE TOP STARS FIRST
        outfile << setw(26) << setfill('*') << "*" << endl;
        // PRINT ALL INFORMATION
        outfile << "TOTAL GAME TURNS: " << turnCounter << endl;
        outfile << left << setw(16) << setfill(' ') << "Type:" << right << setw(10) << getTokenPtrs()[i]->getTokenType() << endl;
        outfile << left << setw(16) << "Points:" << right << setw(10) << getTokenPtrs()[i]->getTokenPoints() << endl;
        outfile << left << setw(16) << "Money Left:" << right << setw(10) << getTokenPtrs()[i]->getTokenBudget() << endl;
        outfile << left << setw(16) << "Current Cell:" << right << setw(6) << "(" << getTokenPtrs()[i]->getTokenRow() << "," << getTokenPtrs()[i]->getTokenCol() << ")" << endl;
        outfile << left << setw(16) << "Debuffs Gained:" << right << setw(10) << getTokenPtrs()[i]->getNumDebuffsUsed() << endl;
        outfile << "Normal Items Gained:" << endl;
        for(int j = 0; j < getTokenPtrs()[i]->getNormalItemsGained().size(); j++) {
            outfile << "    " << getTokenPtrs()[i]->getNormalItemsGained()[j] << endl;
        }
        outfile << "Special Items Gained:" << endl;
        for(int j = 0; j < getTokenPtrs()[i]->getSpecialItemsGained().size(); j++) {
            outfile << "    Turn " << getTokenPtrs()[i]->getSpecialItemsGainedTurns()[j] << " - " << getTokenPtrs()[i]->getSpecialItemsGained()[j] << endl;
        }
        // PRINT THE BOTTOM STARS LAST
        outfile << setw(26) << setfill('*') << "*" << endl;
    }

    outfile.close();

    // Print all the statistics
    // PRINT THE TOP STARS FIRST
    cout << setw(26) << setfill('*') << "*" << endl;
    // PRINT ALL INFORMATION
    cout << left << setw(16) << setfill(' ') << "Turns Played:" << right << setw(10) << turnCounter << endl;
    cout << left << setw(16) << "Type:" << right << setw(10) << winningTokenType << endl;
    cout << left << setw(16) << "Points:" << right << setw(10) << winningTokenPoints << endl;
    cout << left << setw(16) << "Money Left:" << right << setw(10) << winningTokenBudget << endl;
    cout << left << setw(16) << "Current Cell:" << right << setw(6) << "(" << winningTokenRow << "," << winningTokenCol << ")" << endl;
    cout << left << setw(16) << "Debuffs Gained:" << right << setw(10) << winningNumDebuffsUsed << endl;
    cout << "Normal Items Gained:" << endl;
    for(int i = 0; i < winningNormalItemsGained.size(); i++) {
        cout << "    " << winningNormalItemsGained[i] << endl;
    }
    cout << "Special Items Gained:" << endl;
    for(int i = 0; i < winningSpecialItemsGained.size(); i++) {
        cout << "    Turn " << winningSpecialItemsGainedTurns[i] << " - " << winningSpecialItemsGained[i] << endl;
    }
    // PRINT THE BOTTOM STARS LAST
    cout << setw(26) << setfill('*') << "*" << endl;
}

bool Board::playerBoxedOut(const int currentRow, const int currentCol) {
    bool boxedOut = false;
    // Check if player is boxed out in the top left corner
    if(currentRow == 0 && currentCol == 0) {
        if(getCellsOnBoard()[currentRow][currentCol + 1].getTokenPtr() != nullptr && getCellsOnBoard()[currentRow + 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
        }
    }
    // Check if player is boxed out in the top right corner
    else if(currentRow == 0 && currentCol == 4) {
        if(getCellsOnBoard()[currentRow][currentCol - 1].getTokenPtr() != nullptr && getCellsOnBoard()[currentRow + 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
        }
    }
    // Check if player is boxed out in the bottom left corner
    else if(currentRow == 4 && currentCol == 0) {
        if(getCellsOnBoard()[currentRow][currentCol + 1].getTokenPtr() != nullptr && getCellsOnBoard()[currentRow - 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
        }
    }
    // Check if player is boxed out in the bottom right corner
    else if(currentRow == 4 && currentCol == 4) {
        if(getCellsOnBoard()[currentRow][currentCol - 1].getTokenPtr() != nullptr && getCellsOnBoard()[currentRow - 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
        }
    }
    // Check if player is boxed out on the left wall
    else if(currentCol == 0) {
        // Check Cell above, Cell to the right, Cell below
        if(getCellsOnBoard()[currentRow - 1][currentCol].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow][currentCol + 1].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow + 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
           }
    }
    // Check if player is boxed out on the top wall (ceiling)
    else if(currentRow == 0) {
        // Check Cell to the left, Cell below, Cell to the right
        if(getCellsOnBoard()[currentRow][currentCol - 1].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow + 1][currentCol].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow][currentCol + 1].getTokenPtr() != nullptr) {
            boxedOut = true;
           }
    }
    // Check if player is boxed out on the right wall
    else if(currentCol == 4) {
        // Check Cell above, Cell to the left, Cell below
        if(getCellsOnBoard()[currentRow - 1][currentCol].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow][currentCol - 1].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow + 1][currentCol].getTokenPtr() != nullptr) {
            boxedOut = true;
           }
    }
    // Check if player is boxed out on the bottom wall (floor)
    else if(currentRow == 4) {
        // Check Cell to the left, Cell above, Cell to the right
        if(getCellsOnBoard()[currentRow][currentCol - 1].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow - 1][currentCol].getTokenPtr() != nullptr &&
           getCellsOnBoard()[currentRow][currentCol + 1].getTokenPtr() != nullptr) {
            boxedOut = true;
           }
    }
    return boxedOut;
}