/********************************************************
Name      :  Erik Kronquist
Class     :  CSC 2312 Section 001
PA#       :  PR2 - Shopping Spree Showdown
Due Date  :  4/29/2024
********************************************************/

#include "Board.h"
#include "Cell.h"
#include <iostream>
    using std::cout;
    using std::endl;
    using std::cin;
#include <time.h>
#include <string>
    using std::stoi;

string fileToUse;
int turnCounter;

bool playTheGame() {
    srand(time(NULL));
    
    bool playAgain;
    turnCounter = 1;


    bool numTokensIsValid = false;
    string numPlayersString;
    string numComputersString;
    // Number of Tokens for the game
    int numTokens = 0;
    int numPlayers = 0;
    int numComputers = 0;

    cout << "How many Players would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
    std::getline(cin, numPlayersString);

    cout << "How many Computers would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
    std::getline(cin, numComputersString);

    // Check to make sure user only enters single digit numbers and the number of Players and Computers combined is at least 2 but no more than 4
    while(!numTokensIsValid) {
        try {
            // cout << "How many Players would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            // std::getline(cin, numPlayersString);
            numPlayers = stoi(numPlayersString);

            // cout << "How many Computers would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            // std::getline(cin, numComputersString);
            numComputers = stoi(numComputersString);

            if(numPlayers + numComputers >= 2 && numPlayers + numComputers <= 4) {
                numTokens = numPlayers + numComputers;
                numTokensIsValid = true;
            }
            else {
                throw("Please stay between 2 and 4 Tokens!");
            }
        }
        catch(const char* e) {
            cout << e << endl;
            cout << "How many Players would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            std::getline(cin, numPlayersString);

            cout << "How many Computers would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            std::getline(cin, numComputersString);
        }
        catch(...) {
            cout << "Please enter only single digits!" << endl;
            cout << "How many Players would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            std::getline(cin, numPlayersString);

            cout << "How many Computers would you like to be present 2 - 4 Tokens Total (Players and Computers)? ";
            std::getline(cin, numComputersString);
        }
    }


    int itemInitializationOption;
    cout << "How would you like the Items to be initialized?\n1) By File where item boxes are filled randomly\n2) Item boxes are filled at complete random and have no theme\n";
    cin >> itemInitializationOption;

    cin.ignore();

    if(itemInitializationOption == 1) {
        string filename = "./ListOfItems";
        string filenum;
        cout << "Which file would you like to play with?" << endl;
        cout << "1) Grocery Store Haul" << endl;
        cout << "2) Department Store Clearout" << endl;
        cout << "3) Nacho Night Nuked" << endl;
        std::getline(cin, filenum);
        int fileNumInt;

        // Does not prevent an input of a string, only an incorrect number
            // If a string is entered, an infinite while loop will occur
        bool userHasEnteredFileNum = false;
        while(!userHasEnteredFileNum) {
            try {
                fileNumInt = stoi(filenum);
                if(fileNumInt == 1 || fileNumInt == 2 || fileNumInt == 3) {
                    userHasEnteredFileNum = true;
                }
                else {
                    throw("Invalid File");
                }
            }
            catch(...) {
                cout << "Enter a valid file! Which file would you like to play with (1, 2, 3)? ";
                std::getline(cin, filenum);
            }
        }

        // Append the file num and the .txt to the filename and set that to the global variable
        filename = filename + std::to_string(fileNumInt) + ".txt";
        fileToUse = filename;
    }

    cout << "---------- TURN " << turnCounter << " -----------" << endl;

    Board gameBoard = Board(itemInitializationOption, numPlayers, numComputers);

    array<array<Cell, 5>, 5> cells = gameBoard.getCellsOnBoard();
    vector<Token*> tokens = gameBoard.getTokenPtrs();

    cout << gameBoard;

    bool continueGame = true;
    while(continueGame) {
        turnCounter++;
        cout << "\n---------- TURN " << turnCounter << " -----------" << endl;
        string keepPlaying;

        gameBoard.move(cells, tokens);
        cells = gameBoard.getCellsOnBoard();
        tokens = gameBoard.getTokenPtrs();
        cout << gameBoard;
        if(gameBoard.gameOverCheck(tokens)) {
            continueGame = false;
        }
    }

    cout << "\n---------- GAME OVER ----------\n" << endl;

    gameBoard.printSummaryCard();

    bool endCurrentGame = false;
    while(!endCurrentGame) {
        int endOfGameOption;
        cout << "Enter an option as a single digit" << endl;
        cout << "1) See more in-depth statistics for the winner" << endl;
        cout << "2) Play the game again" << endl;
        cout << "3) Quit" << endl;
        cin >> endOfGameOption;
        // Print statistics
        if(endOfGameOption == 1) {
            gameBoard.printStatistics();
        }
        // Replay the game
        else if(endOfGameOption == 2) {
            playAgain = true;
            endCurrentGame = true;
            cin.ignore();
        }
        // Quit the program
        else if(endOfGameOption == 3) {
            playAgain = false;
            endCurrentGame = true;
        }
    }


    cout << "---------- DELETING ALL DYNAMICALLY ALLOCATED POINTERS ----------" << endl;

    // Deletes all Tokens belonging to the Board as they were created dynamically
        // Also deletes all Items from each Token when the Token destructor is called
    vector<Token*> boardTokens = gameBoard.getTokenPtrs();
    for(auto eachToken : boardTokens) {
        delete eachToken;
        eachToken = nullptr;
    }
    boardTokens.clear();
    gameBoard.setTokenPtrs(boardTokens);

    // Deletes all ItemBoxes from the Cells as they were dynamically created
        // Also deletes all the Items from the ItemBox when the ItemBox destructor is called
    array<array<Cell, 5>, 5> multiDimArrayOfCells = gameBoard.getCellsOnBoard();
    for(auto singleDimArrayOfCells : multiDimArrayOfCells) {
        for(auto eachCell : singleDimArrayOfCells) {
            ItemBox* itemBoxPtr = eachCell.getItemBox();
            delete itemBoxPtr;
            itemBoxPtr = nullptr;
        }
    }
    gameBoard.setCellsOnBoard(multiDimArrayOfCells);

    return playAgain;
}

int main() {
    srand(time(NULL));

    // Calling a function called playTheGame so I don't have to recursively call main()
    while(playTheGame());

    return 0;
}