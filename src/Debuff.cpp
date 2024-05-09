/*********************************************************
* Summary: This file includes the implementation for the Debuff class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       23 Apr 2024 - Created Debuff.cpp
********************************************************/

#include "Debuff.h"

// Constructors
Debuff::Debuff() { /* LEFT EMPTY*/ }

Debuff::Debuff(const int itemNum, const string itemName) : Item(itemNum, itemName, 0, 0) { /* LEFT EMPTY*/ }

// Getters
int Debuff::getDebuffType() const {
    return debuffType;
}

string Debuff::getType() const {
    return "Debuff";
}

// Setters
void Debuff::setDebuffType(const int debuffType) {
    this->debuffType = debuffType;
}