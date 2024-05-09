/*********************************************************
* Summary: This file includes the implementation for the Item class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       23 Apr 2024 - Created Item.cpp
********************************************************/

#include "Item.h"

Item::Item() {
    setItemNum(0);
    setItemName("");
    setItemPoints(0);
    setItemCost(0);
}

Item::Item(const int itemNum, const string itemName, const int points, const int cost) {
    setItemNum(itemNum);
    setItemName(itemName);
    setItemPoints(points);
    setItemCost(cost);
}

// Destructor
Item::~Item() { /* LEFT EMPTY */}

// Getters
int Item::getItemNum() const {
    return itemNum;
}

string Item::getItemName() const {
    return itemName;
}

int Item::getItemPoints() const {
    return points;
}

int Item::getItemCost() const {
    return cost;
}

// Setters
void Item::setItemNum(const int itemNum) {
    this->itemNum = itemNum;
}

void Item::setItemName(const string itemName) {
    this->itemName = itemName;
}

void Item::setItemPoints(const int points) {
    this->points = points;
}

void Item::setItemCost(const int cost) {
    this->cost = cost;
}