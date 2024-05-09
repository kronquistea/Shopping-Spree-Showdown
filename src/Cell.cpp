/*********************************************************
* Summary: This file includes the implementation for the Cell class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       22 Apr 2024 - Created Cell.cpp
*       24 Apr 2024 - Added functionality in openItemBox function so the Items get added to the Tokens profile
*       24 Apr 2024 - Removed emptyItemBox and instead directly change itemBoxPtr to a nullptr
*       24 Apr 2024 - Added throw statement inside cellIsFree function
*       25 Apr 2024 - Added logic to openItemBox to ensure the Token can afford the items
*       25 Apr 2024 - Added functionality so Debuff will be used if obtained
********************************************************/

#include "Board.h"
#include "Cell.h"
#include <iostream>
    using std::cout;
    using std::endl;

// Constructor(s)
Cell::Cell() {
    ItemBox* newItemBoxPtr = new ItemBox();
    setItemBox(newItemBoxPtr);
}

Cell::Cell(int itemInitializationOption) {
    if(itemInitializationOption == 1) {
        ItemBox* newItemBoxPtr = new ItemBox(fileToUse);
        setItemBox(newItemBoxPtr);
    }
    else {
        ItemBox* newItemBoxPtr = new ItemBox();
        setItemBox(newItemBoxPtr);
    }
}

// Getters
ItemBox* Cell::getItemBox() const {
    return itemBoxPtr;
}

Token* Cell::getTokenPtr() const {
    return tokenPtr;
}

// Setters
void Cell::setItemBox(ItemBox* itemBox) {
    this->itemBoxPtr = itemBox;
}

void Cell::setTokenPtr(Token* tokenPtr) {
    this->tokenPtr = tokenPtr;
}

// Other Functions
void Cell::openItemBox(Token* tokenPtr) {
    vector<int> turns = tokenPtr->getSpecialItemsGainedTurns();
    vector<string> specialItems = tokenPtr->getSpecialItemsGained();
    vector<string> normalItems = tokenPtr->getNormalItemsGained();

    // Pick 2 random Items from the ItemBox
    ItemBox *itemBoxToOpenPtr = getItemBox();
    int firstRandomItemIndex = rand() % 5;
    int secondRandomItemIndex = rand() % 4;

    vector<Item*> items = itemBoxToOpenPtr->getListOfItemPtrs();

    Item *firstItemPtr = items[firstRandomItemIndex];
    items.erase(items.begin() + firstRandomItemIndex);

    Item *secondItemPtr = items[secondRandomItemIndex];
    items.erase(items.begin() + secondRandomItemIndex);

    cout << "Items Gained:" << endl;
    // As long as the Player can afford the items, put the item into the randomItems vector, add the Item to the Player, add points and lower the remaining money (budget)
    if(firstItemPtr->getType() == "Debuff") {
        tokenPtr->addAnItem(firstItemPtr);
        tokenPtr->useDebuff(firstItemPtr->getItemName());
        turns.push_back(turnCounter);
        specialItems.push_back("Debuff");
        tokenPtr->setSpecialItemsGainedTurns(turns);
        tokenPtr->setSpecialItemsGained(specialItems);
        tokenPtr->setNumDebuffsUsed(tokenPtr->getNumDebuffsUsed() + 1);
    }
    else if((tokenPtr->getTokenBudget() - firstItemPtr->getItemCost()) >= 0) {
        if(firstItemPtr->getType() == "Power Up") {
            turns.push_back(turnCounter);
            specialItems.push_back("Power Up");
            tokenPtr->setSpecialItemsGainedTurns(turns);
            tokenPtr->setSpecialItemsGained(specialItems);
        }
        else if(firstItemPtr->getType() == "Normal Item") {
            normalItems.push_back(firstItemPtr->getItemName());
            tokenPtr->setNormalItemsGained(normalItems);
        }
        cout << "Gained a " << firstItemPtr->getItemName() << endl;
        tokenPtr->addAnItem(firstItemPtr);
        tokenPtr->setTokenPoints(tokenPtr->getTokenPoints() + firstItemPtr->getItemPoints());
        tokenPtr->setTokenBudget(tokenPtr->getTokenBudget() - firstItemPtr->getItemCost());
    }

    if(secondItemPtr->getType() == "Debuff") {
        tokenPtr->addAnItem(secondItemPtr);
        tokenPtr->useDebuff(secondItemPtr->getItemName());
        turns.push_back(turnCounter);
        specialItems.push_back("Debuff");
        tokenPtr->setSpecialItemsGainedTurns(turns);
        tokenPtr->setSpecialItemsGained(specialItems);
        tokenPtr->setNumDebuffsUsed(tokenPtr->getNumDebuffsUsed() + 1);
    }
    else if((tokenPtr->getTokenBudget() - secondItemPtr->getItemCost()) >= 0) {
        if(secondItemPtr->getType() == "Power Up") {
            turns.push_back(turnCounter);
            specialItems.push_back("Power Up");
            tokenPtr->setSpecialItemsGainedTurns(turns);
            tokenPtr->setSpecialItemsGained(specialItems);
        }
        else if(secondItemPtr->getType() == "Normal Item") {
            normalItems.push_back(secondItemPtr->getItemName());
            tokenPtr->setNormalItemsGained(normalItems);
        }
        cout << "Gained a " << secondItemPtr->getItemName() << endl;
        tokenPtr->addAnItem(secondItemPtr);
        tokenPtr->setTokenPoints(tokenPtr->getTokenPoints() + secondItemPtr->getItemPoints());
        tokenPtr->setTokenBudget(tokenPtr->getTokenBudget() - secondItemPtr->getItemCost());
    }

    cout << endl;

    // ItemBoxes are deleted at the end of the game
    itemBoxPtr = nullptr;
}

bool Cell::cellIsFree() {
    bool available = false;
    if(getTokenPtr() != nullptr) {
        throw("There is a Token already present at that cell!");
    }
    else {
        available = true;
    }
    return available;
}