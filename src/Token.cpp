/*********************************************************
* Summary: This file includes the implementation for the Token class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       22 Apr 2024 - Created Token.cpp
*       24 Apr 2024 - Created a vector to store the Items that a Token possesses and its Getter and Setter functions
*       24 Apr 2024 - Created addAnItem functions so the Tokens can actually get the Items rather than them just disappearing from the board
*       25 Apr 2024 - Added variables and functions for Budget and Points and created usePowerUp as a pure virtual functions
*       25 Apr 2024 - Added useDebuff and movementBanStatus and movementBanStartTurn and getters/setters
*       27 Apr 2024 - Added vector to store names of all normal items gained
*       27 Apr 2024 - Delete dynamically created Debuffs when gained/after being used
********************************************************/

#include "Board.h"
#include "Token.h"
#include <iostream>
    using std::cout;
    using std::endl;

// Constructors
Token::Token() { /* LEFT EMPTY */ }

Token::Token(const int tokenNum, const int tokenRow, const int tokenCol, const string tokenType) {
    setTokenNum(tokenNum);
    setTokenRow(tokenRow);
    setTokenCol(tokenCol);
    setTokenType(tokenType);
    setTokenPoints(0);
    setTokenBudget(40);
    setNumDebuffsUsed(0);
}

// Destructor
Token::~Token() {
    // Deletes all items belonging to the Token
    for(auto item : tokenVectorOfItems) {
        delete item;
        item = nullptr;
    }
    tokenVectorOfItems.clear();
}

// Getters
int Token::getTokenNum() const {
    return tokenNum;
}

int Token::getTokenPoints() const {
    return points;
}

int Token::getTokenBudget() const {
    return budget;
}

int Token::getTokenRow() const {
    return tokenRow;
}

int Token::getTokenCol() const {
    return tokenCol;
}

string Token::getTokenType() const {
    return tokenType;
}

vector<Item*> Token::getTokenVectorOfItems() const {
    return tokenVectorOfItems;
}

bool Token::getMovementBanStatus() const {
    return movementBanStatus;
}

int Token::getMovementBanStartTurn() const {
    return movementBanStartTurn;
}

int Token::getNumDebuffsUsed() const {
    return numDebuffsUsed;
}

vector<int> Token::getSpecialItemsGainedTurns() const {
    return specialItemsGainedTurns;
}

vector<string> Token::getSpecialItemsGained() const {
    return specialItemsGained;
}

vector<string> Token::getNormalItemsGained() const {
    return normalItemsGained;
}

// Setters
void Token::setTokenNum(const int tokenNum) {
    this->tokenNum = tokenNum;
}

void Token::setTokenPoints(const int points) {
    this->points = points;
}

void Token::setTokenBudget(const int budget) {
    this->budget = budget;
}

void Token::setTokenRow(const int tokenRow) {
    this->tokenRow = tokenRow;
}

void Token::setTokenCol(const int tokenCol) {
    this->tokenCol = tokenCol;
}

void Token::setTokenType(const string tokenType) {
    this->tokenType = tokenType;
}

void Token::setTokenVectorOfItems(const vector<Item*> tokenVectorOfItems) {
    this->tokenVectorOfItems = tokenVectorOfItems;
}

void Token::setMovementBanStatus(const bool movementBanStatus) {
    this->movementBanStatus = movementBanStatus;
}

void Token::setMovementBanStartTurn(const int movementBanStartTurn) {
    this->movementBanStartTurn = movementBanStartTurn;
}

void Token::setNumDebuffsUsed(const int numDebuffsUsed) {
    this->numDebuffsUsed = numDebuffsUsed;
}

void Token::setSpecialItemsGainedTurns(const vector<int> specialItemsGainedTurns) {
    this->specialItemsGainedTurns = specialItemsGainedTurns;
}

void Token::setSpecialItemsGained(const vector<string> specialItemsGained) {
    this->specialItemsGained = specialItemsGained;
}

void Token::setNormalItemsGained(const vector<string> normalItemsGained) {
    this->normalItemsGained = normalItemsGained;
}

void Token::setCoordinates(const int newTokenRow, const int newTokenCol) {
    setTokenRow(newTokenRow);
    setTokenCol(newTokenCol);
}

// Other Functions
void Token::addAnItem(Item *itemPtr) {
    vector<Item*> items = getTokenVectorOfItems();
    items.push_back(itemPtr);
    setTokenVectorOfItems(items);
}

void Token::useDebuff(string debuffType) {
    vector<Item*> items = getTokenVectorOfItems();
    int debuffIndex;
    for(int i = 0; i < items.size(); i++) {
        // cout << "items[i]->getItemName() : " << items[i]->getItemName() << endl;
        if(items[i]->getItemName() == debuffType) {
            debuffIndex = i;
        }
    }
    // Drains the Token of 10 dollars, if they would go negative, they now go to 0
    if(debuffType == "Monetary Drain") {
        cout << "ACTIVATING MONETARY DRAIN" << endl;
        if(getTokenBudget() - 10 < 0) {
            setTokenBudget(0);
        }
        else {
            setTokenBudget(getTokenBudget() - 10);
        }

        delete items[debuffIndex];
        items[debuffIndex] = nullptr;
        items.erase(items.begin() + debuffIndex);
    }
    // Removes an item from the Tokens inventory of items with NO refund
    else if(debuffType == "Item Vanish" && items.size() > 1) {
        cout << "ACTIVATING ITEM VANISH" << endl;
        int randomItemIndex = rand() % items.size();
        setTokenPoints(getTokenPoints() - items[randomItemIndex]->getItemPoints());
        delete items[randomItemIndex];
        items[randomItemIndex] = nullptr;
        items.erase(items.begin() + randomItemIndex);

        delete items[debuffIndex];
        items[debuffIndex] = nullptr;
        items.erase(items.begin() + debuffIndex - 1);
    }
    else if(debuffType == "Item Vanish" && items.size() <= 1) {
        cout << "ACTIVATING ITEM VANISH" << endl;
        delete items[debuffIndex];
        items[debuffIndex] = nullptr;
        items.erase(items.begin() + debuffIndex);
    }
    // Player cannot move, essentially skipping their turn, CAN STILL USE POWERUP, applied for 2 turns
    else if(debuffType == "Movement Ban") {
        cout << "ACTIVATING MOVEMENT BAN" << endl;
        setMovementBanStatus(true);
        setMovementBanStartTurn(turnCounter);

        delete items[debuffIndex];
        items[debuffIndex] = nullptr;
        items.erase(items.begin() + debuffIndex);
    }
    setTokenVectorOfItems(items);
}