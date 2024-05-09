/*********************************************************
* Summary: This file includes the implementation for the NormalItem class' functions.

* Author: Erik Kronquist
* Created: Apr 22, 2024
* Summary of Modifications:
*       23 Apr 2024 - Created NormalItem.cpp
********************************************************/

#include "NormalItem.h"

// Constructors
NormalItem::NormalItem() { /* LEFT EMPTY*/ }

NormalItem::NormalItem(const int itemNum, const string itemName, const int itemPoints, const int itemCost) : Item(itemNum, itemName, itemPoints, itemCost) { /* LEFT EMPTY*/ }

string NormalItem::getType() const {
    return "Normal Item";
}