/*********************************************************
* Summary: This file includes the implementation for the ItemBox class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       23 Apr 2024 - Created ItemBox.cpp
*       25 Apr 2024 - Removed old comments
********************************************************/

#include "ItemBox.h"
#include "NormalItem.h"
#include "PowerUp.h"
#include "Debuff.h"
#include <iostream>
    using std::cout;
    using std::endl;
#include <sstream>
    using std::stringstream;
#include <fstream>
    using std::ifstream;

// Constructors
ItemBox::ItemBox() {
    generateNewItems();
}

ItemBox::ItemBox(const string filename) {
    generateNewItems(filename);
}

// Destructor
ItemBox::~ItemBox() {
    // Deletes all the Items "in" the ItemBox
    for(auto item : listOfItemPtrs) {
        delete item;
        item = nullptr;
    }
    listOfItemPtrs.clear();
}

// Getters
vector<Item*> ItemBox::getListOfItemPtrs() const {
    return this->listOfItemPtrs;
}

// Setters
void ItemBox::setListOfItemPtrs(const vector<Item*> listOfItemPtrs) {
    this->listOfItemPtrs = listOfItemPtrs;
}

// Other Functions
void ItemBox::generateNewItems() {
    vector<Item*> newItems;
    for(int i = 0; i < 5; i++) {
        int randomItemType = rand() % 7;
        if(randomItemType >= 0 && randomItemType <= 3) {
            newItems.push_back(new NormalItem(1, "Normal", 10, 5));
        }
        else if(randomItemType >= 4 && randomItemType <= 5) {
            string randomPowerUpType;
            int randomPowerUp = rand() % 3;
            if(randomPowerUp == 0) {
                randomPowerUpType = "Budget Boost";
            }
            else if(randomPowerUp == 1) {
                randomPowerUpType = "Point Surge";
            }
            else {
                randomPowerUpType = "Refund Request";
            }
            newItems.push_back(new PowerUp(2, randomPowerUpType, 0, 0));
        }
        else {
            string randomDebuffType;
            int randomDebuff = rand() % 3;
            if(randomDebuff == 0) {
                randomDebuffType = "Monetary Drain";
            }
            else if(randomDebuff == 1) {
                randomDebuffType = "Item Vanish";
            }
            else {
                randomDebuffType = "Movement Ban";
            }
            newItems.push_back(new Debuff(3, randomDebuffType));
        }
    }
    setListOfItemPtrs(newItems);
}

void ItemBox::generateNewItems(const string filename) {
    // cout << "Generating new Items" << endl;
    vector<Item*> newItems;

    /*
    0, 1, 2, 3 - Normal Item
    4, 5 - Power Up
    6 - Debuff
    */
    // Generate 5 random Items
    for(int i = 0; i < 5; i++) {
        ifstream inputfile;
        inputfile.open(filename, std::ios::in);
        // Vector for holding each Items information
        vector<string> itemInformation;
        // Generate a random type of Item
        int itemType = rand() % 7;
        // Get random Normal Item
        if(itemType >= 0 && itemType <= 3) {
            int counter = 1;
            // Generate a random Normal Item Id (1 - 10)
            int randomNormalItemId = (rand() % 10) + 1;
            // Loop through the file
            while(inputfile) {
                // Parse each line into a stringstream object
                string itemInfo;
                std::getline(inputfile, itemInfo, '\n');
                stringstream itemStream(itemInfo);
                // While the itemStream (line) still has more elements
                while(itemStream.good()) {
                    // Create a substr string and parse the Items information into it then push it into the itemInformation vector
                    string substr;
                    std::getline(itemStream, substr, ',');
                    itemInformation.push_back(substr);
                }
                // Parse the first piece of information (Item Number) from a string into an int
                stringstream itemIDStream;
                stringstream itemCostStream;
                stringstream itemPointsStream;
                // Item ID as int
                itemIDStream << itemInformation[0];
                int itemNum = 0;
                itemIDStream >> itemNum;
                // Item cost as int
                itemCostStream << itemInformation[4];
                int itemCost = 0;
                itemCostStream >> itemCost;
                // Item points as int
                itemPointsStream << itemInformation[3];
                int itemPoints = 0;
                itemPointsStream >> itemPoints;

                if(itemNum == randomNormalItemId) {
                    newItems.push_back(new NormalItem(itemNum, itemInformation[2], itemPoints, itemCost));
                    break;
                }
                itemInformation.clear();
            }
        }
        // Get random Power Up
        else if(itemType >= 4 && itemType <= 5) {
            int randomPowerUpID = (rand() % 3) + 11;
            // Loop through the file
            while(inputfile) {
                // Parse each line into a stringstream object
                string itemInfo;
                // inputfile >> itemInfo;
                std::getline(inputfile, itemInfo, '\n');
                stringstream itemStream(itemInfo);
                // While the itemStream (line) still has more elements
                while(itemStream.good()) {
                    // Create a substr string and parse the Items information into it then push it into the itemInformation vector
                    string substr;
                    std::getline(itemStream, substr, ',');
                    itemInformation.push_back(substr);
                }
                // Parse the first piece of information (Item Number) from a string into an int
                stringstream itemIDStream;
                stringstream itemCostStream;
                stringstream itemPointsStream;
                // Item ID as int
                itemIDStream << itemInformation[0];
                int itemNum = 0;
                itemIDStream >> itemNum;
                // Item cost as int
                itemCostStream << itemInformation[4];
                int itemCost = 0;
                itemCostStream >> itemCost;
                // Item points as int
                itemPointsStream << itemInformation[3];
                int itemPoints = 0;
                itemPointsStream >> itemPoints;

                if(itemNum == randomPowerUpID) {
                    newItems.push_back(new PowerUp(itemNum, itemInformation[2], itemPoints, itemCost));
                    break;
                }
                itemInformation.clear();
            }
        }
        // Get random Debuff
        else {
            int randomDebuffID = (rand() % 3) + 14;
            while(inputfile) {
                // Parse each line into a stringstream object
                string itemInfo;
                std::getline(inputfile, itemInfo, '\n');
                stringstream itemStream(itemInfo);
                // While the itemStream (line) still has more elements
                while(itemStream.good()) {
                    // Create a substr string and parse the Items information into it then push it into the itemInformation vector
                    string substr;
                    std::getline(itemStream, substr, ',');
                    itemInformation.push_back(substr);
                }
                // Parse the first piece of information (Item Number) from a string into an int
                stringstream itemIDStream;
                stringstream itemCostStream;
                stringstream itemPointsStream;
                // Item ID as int
                itemIDStream << itemInformation[0];
                int itemNum = 0;
                itemIDStream >> itemNum;
                // Item cost as int
                itemCostStream << itemInformation[4];
                int itemCost = 0;
                itemCostStream >> itemCost;
                // Item points as int
                itemPointsStream << itemInformation[3];
                int itemPoints = 0;
                itemPointsStream >> itemPoints;

                if(itemNum == randomDebuffID) {
                    newItems.push_back(new Debuff(itemNum, itemInformation[2]));
                }
                itemInformation.clear();
            }
        }
    }

    setListOfItemPtrs(newItems);
}