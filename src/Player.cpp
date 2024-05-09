/*********************************************************
* Summary: This file includes the implementation for the Player class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       22 Apr 2024 - Created Player.cpp
*       25 Apr 2024 - Added userPowerUp function for Player
*       25 Apr 2024 - Properly removing items from Player when Refund Request is activated
*       25 Apr 2024 - Asked user if they would like to use another Power Up
*       27 Apr 2024 - Delete dynamically created Power Ups when used
*       29 Apr 2024 - Added error checking againt out-of-bounds when using a Power Up
********************************************************/

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;
    using std::stoi;
#include "Player.h"

// Constructors
Player::Player() { /* LEFT EMPTY */ }

Player::Player(const int tokenNum, const int playerRow, const int playerCol) : Token(tokenNum, playerRow, playerCol, "PLAYER") { /* LEFT EMPTY */ }

// Other Functions
void Player::usePowerUp() {
    vector<Item*> tokenVectorOfItems = getTokenVectorOfItems();
    // Ask user if they would like to user a Power Up
    string yesOrNo = "N";
    cout << "Would you like to use a Power Up? (Y/N) ";
    cin >> yesOrNo;
    cin.ignore();
    // If they do, ask them which Power Up and apply the effect
    while(yesOrNo == "y" || yesOrNo == "Y") {
        // Ensure that the Player has at least one Normal Item
        int numberOfNormalItems = 0;
        // Ensure that the Player has at least on
        int numberOfPowerUps = 0;
        for(int i = 0; i < tokenVectorOfItems.size(); i++) {
            if(tokenVectorOfItems[i]->getType() == "Power Up") {
                numberOfPowerUps++;
            }
            else if(tokenVectorOfItems[i]->getType() == "Normal Item") {
                numberOfNormalItems++;
            }
        }
        // Ask long as they own at least one Power Up ask the Player which Power Up they would like to use
        try {
        if(numberOfPowerUps > 0) {
            bool validPowerUpNumber = false;
            string powerUpNumberString;
            int powerUpNumber;
            while(!validPowerUpNumber) {
                try {
                    cout << "Enter the number corresponding to the Power Up you would like to use." << endl;
                    for(int i = 0; i < tokenVectorOfItems.size(); i++) {
                        if(tokenVectorOfItems[i]->getType() == "Power Up") {
                            cout << i << " - " << tokenVectorOfItems[i]->getItemName() << endl;
                        }
                    }
                    std::getline(cin, powerUpNumberString);
                    powerUpNumber = stoi(powerUpNumberString);
                    // cin >> powerUpNumber;
                    if(powerUpNumber < 0 || powerUpNumber >= tokenVectorOfItems.size() || tokenVectorOfItems[powerUpNumber]->getType() != "Power Up") {
                        throw("Please enter a valid number for the Power Up you would like to use!");
                    }
                    else {
                        validPowerUpNumber = true;
                    }
                }
                catch(const char* e) {
                    cout << e << endl;
                }
                catch(...) {
                    cout << "Please enter a number!" << endl;
                }
            }

            // If the Power Up is a Budget Boost add $20 to their account
            if(tokenVectorOfItems[powerUpNumber]->getItemName() == "Budget Boost") {
                setTokenBudget((getTokenBudget() + 20));
                delete tokenVectorOfItems[powerUpNumber];
                tokenVectorOfItems[powerUpNumber] = nullptr;
                tokenVectorOfItems.erase(tokenVectorOfItems.begin() + powerUpNumber);
            }
            // If the Power Up is a Point Surge add 10 points to their acount
            else if(tokenVectorOfItems[powerUpNumber]->getItemName() == "Point Surge") {
                setTokenPoints((getTokenPoints() + 10));
                delete tokenVectorOfItems[powerUpNumber];
                tokenVectorOfItems[powerUpNumber] = nullptr;
                tokenVectorOfItems.erase(tokenVectorOfItems.begin() + powerUpNumber);
            }
            // If the Power Up is a Refund Request, prompt them for which item to refund and remove it from their account
            // (reduce the amount of money the player has spent)
            else if(tokenVectorOfItems[powerUpNumber]->getItemName() == "Refund Request" && numberOfNormalItems > 0) {
                int normalItemIndex;
                cout << "Which Normal Item would you like to request for a full refund?" << endl;
                for(int i = 0; i < tokenVectorOfItems.size(); i++) {
                    if(tokenVectorOfItems[i]->getType() == "Normal Item") {
                        cout << i << " - " << tokenVectorOfItems[i]->getItemName()
                             << ", Points/Cost: " << tokenVectorOfItems[i]->getItemPoints() << "/" << tokenVectorOfItems[i]->getItemCost()
                        << endl;
                    }
                }
                cin >> normalItemIndex;
                setTokenPoints(getTokenPoints() - tokenVectorOfItems[normalItemIndex]->getItemPoints());
                setTokenBudget(getTokenBudget() + tokenVectorOfItems[normalItemIndex]->getItemCost());
                if(powerUpNumber < normalItemIndex) {
                    delete tokenVectorOfItems[powerUpNumber];
                    tokenVectorOfItems[powerUpNumber] = nullptr;
                    delete tokenVectorOfItems[normalItemIndex];
                    tokenVectorOfItems[normalItemIndex] = nullptr;
                    tokenVectorOfItems.erase((tokenVectorOfItems.begin() + powerUpNumber));
                    tokenVectorOfItems.erase((tokenVectorOfItems.begin() + normalItemIndex) - 1);
                }
                else {
                    delete tokenVectorOfItems[powerUpNumber];
                    tokenVectorOfItems[powerUpNumber] = nullptr;
                    delete tokenVectorOfItems[normalItemIndex];
                    tokenVectorOfItems[normalItemIndex] = nullptr;
                    tokenVectorOfItems.erase((tokenVectorOfItems.begin() + powerUpNumber));
                    tokenVectorOfItems.erase((tokenVectorOfItems.begin() + normalItemIndex));
                }
            }
            else {
                throw("Can not use this Power Up (Continuing turn)!");
            }
            setTokenVectorOfItems(tokenVectorOfItems);
            cout << "Would you like to use a Power Up again? (Y/N) ";
            cin >> yesOrNo;
        }
        else {
            throw("You have no Power Ups!");
        }
        }
        catch(const char* e) {
            // If a string with spaces is entered here it will cause an infinite while loop when asking for the next position to move to after leaving this function
            string continueGame;
            // cout << "You have no Power Ups! (Enter a key to continue): ";
            cout << e << " (Enter a key then press enter to continue): ";
            cin >> continueGame;
            yesOrNo = "n";
        }
    }
}