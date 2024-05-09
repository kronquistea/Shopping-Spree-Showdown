/*********************************************************
* Summary: This file includes the implementation for the PowerUp class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       23 Apr 2024 - Created PowerUp.cpp
********************************************************/

#include "PowerUp.h"

// Constructors
PowerUp::PowerUp() { /* LEFT EMPTY*/ }

PowerUp::PowerUp(const int itemNum, const string itemName, const int points, const int cost) : Item(itemNum, itemName, points, cost) { /* LEFT EMPTY*/ }

// Getters
int PowerUp::getPowerUpType() const {
    return powerUpType;
}

string PowerUp::getType() const {
    return "Power Up";
}

// Setters
void PowerUp::setPowerUpType(const int powerUpType) {
    this->powerUpType = powerUpType;
}