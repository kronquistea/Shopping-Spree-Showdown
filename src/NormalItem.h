/***********************************
 * Class Name: NormalItem
 * 
 * Description: This header file contains the class declaration for NormalItem
 * and it's constructors, getters and setters
 * A NormalItem is an Item
***********************************/

#ifndef NORMALITEM_H
#define NORMALITEM_H

#include "Item.h"

class NormalItem : public Item {
    public:
        // Constructors
        // @brief Default constructor for NormalItem, will never be used
        NormalItem();
        // @brief Paramterized constructor for NormalItem, will be used when creating a NormalItem object
        // @param int itemNum
        // @param string itemName
        // @param int itemPoints
        // @param int itemCost
        explicit NormalItem(const int itemNum, const string itemName, const int itemPoints, const int itemCost);

        // Other Functions
        // @brief Gets type of NormalItem - Overriden from Item class - could be raspberry, milk carton, eggs, etc - overriden from Item.h
        // @return string itemType
        string getType() const override;
    private:
};

#endif