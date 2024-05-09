/*********************************************************
* Summary: This file includes the implementation for the Computer class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       22 Apr 2024 - Created Computer.cpp
*       25 Apr 2024 - Added usePowerUp function to avoid compilation errors - not yet implemented
*       25 Apr 2024 - Implemented usePowerUp function
*       25 Apr 2024 - Changed if statement to while loop to allow Computer to use any number of Power Ups
*       26 Apr 2024 - Fixed Refund Request Logic as it was erasing the wrong items from the vector
*       27 Apr 2024 - Fixed deletion of dynamically allocated Power Ups when used
********************************************************/

#include "Board.h"
#include "Computer.h"
#include <iostream>
    using std::cout;
    using std::endl;

// Constructors
Computer::Computer() : Token(0, 0, 0, "COMPUTER") { /* LEFT EMPTY */}
Computer::Computer(const int tokenNum, int randomRow, int randomCol) : Token(tokenNum, randomRow, randomCol, "COMPUTER") { /* LEFT EMPTY */ }

// Other Functions
void Computer::generateRandomCoordinates(array<array<Cell, 5>, 5> arrayOfCells) {
    bool cellIsTaken = false;
    while(!cellIsTaken) {
        int randomRow = rand() % 5;
        int randomCol = rand() % 5;
        if(arrayOfCells[randomRow][randomCol].cellIsFree()) {
            setTokenRow(randomRow);
            setTokenCol(randomCol);
            cellIsTaken = true;
        }
    }
}

void Computer::usePowerUp() {
    vector<Item*> computerItems = getTokenVectorOfItems();
    int sizeOfComputerItems = computerItems.size();
    int numOfNormalItems = 0;
    int numOfPowerUps = 0;

    for(int i = 0; i < sizeOfComputerItems; i++) {
        if(computerItems[i]->getType() == "Normal Item") {
            numOfNormalItems++;
        }
        else if(computerItems[i]->getType() == "Power Up") {
            numOfPowerUps++;
        }
    }

    int powerUpLocation = 0;
    bool itemSelected = false;
    while(powerUpLocation < sizeOfComputerItems && numOfPowerUps > 0 && !itemSelected) {
        int randomChanceToUsePowerUp = rand() % 3;
        if(randomChanceToUsePowerUp == 0 && sizeOfComputerItems > 0 && numOfPowerUps > 0) {
            if(computerItems[powerUpLocation]->getItemName() == "Budget Boost") {
                cout << "ACTIVATING BUDGET BOOST" << endl;
                setTokenBudget(getTokenBudget() + 20);
                delete computerItems[powerUpLocation];
                computerItems[powerUpLocation] = nullptr;
                computerItems.erase(computerItems.begin() + powerUpLocation);
                itemSelected = true;
            }
            else if(computerItems[powerUpLocation]->getItemName() == "Point Surge") {
                cout << "ACTIVATING POINT SURGE" << endl;
                setTokenPoints(getTokenPoints() + 10);
                delete computerItems[powerUpLocation];
                computerItems[powerUpLocation] = nullptr;
                computerItems.erase(computerItems.begin() + powerUpLocation);
                itemSelected = true;
            }
            else if(computerItems[powerUpLocation]->getItemName() == "Refund Request" && numOfNormalItems > 0) {
                cout << "ACTIVATING REFUND REQUEST" << endl;
                bool itemRefunded = false;
                // Generate an index for a random item to be refunded
                int randomItemToRefundIndex = rand() % sizeOfComputerItems;
                while(!itemRefunded) {
                    // If that random Item is a Normal Item, then refund it, other wise generate a new random item
                    if(computerItems[randomItemToRefundIndex]->getType() == "Normal Item") {
                        setTokenBudget(getTokenBudget() + computerItems[randomItemToRefundIndex]->getItemCost());
                        setTokenPoints(getTokenPoints() - computerItems[randomItemToRefundIndex]->getItemPoints());
                        if(powerUpLocation < randomItemToRefundIndex) {
                            delete computerItems[powerUpLocation];
                            computerItems[powerUpLocation] = nullptr;
                            delete computerItems[randomItemToRefundIndex];
                            computerItems[randomItemToRefundIndex] = nullptr;
                            computerItems.erase((computerItems.begin() + powerUpLocation));
                            computerItems.erase((computerItems.begin() + randomItemToRefundIndex) - 1);
                            itemRefunded = true;
                        }
                        else {
                            delete computerItems[powerUpLocation];
                            computerItems[powerUpLocation] = nullptr;
                            delete computerItems[randomItemToRefundIndex];
                            computerItems[randomItemToRefundIndex] = nullptr;
                            computerItems.erase((computerItems.begin() + powerUpLocation));
                            computerItems.erase((computerItems.begin() + randomItemToRefundIndex));
                            itemRefunded = true;
                        }
                        itemRefunded = true;
                    }
                    else {
                        randomItemToRefundIndex = rand() % sizeOfComputerItems;
                    }
                }
                itemSelected = true;
            }
        }
        powerUpLocation++;
    }

    setTokenVectorOfItems(computerItems);
}