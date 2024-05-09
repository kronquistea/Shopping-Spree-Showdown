/***********************************
 * Class Name: Debuff
 * 
 * Description: This header file contains the class declaration for Debuff
 * and it's constructors, getters and setters
 * A Debuff is an Item
***********************************/

#ifndef DEBUFF_H
#define DEBUFF_H

#include "Item.h"

class Debuff : public Item {
    public:
        // Constructors - sets points and cost to 0
        // @brief Default constructor for Debuff, will never be used
        Debuff();
        // @brief Parameterized constructor for Debuff, will be used when creating Debuff object
        // @param int itemNum
        // @param string itemName
        explicit Debuff(int itemNum, string itemName);

        // Getters
        // @brief Gets the Debuff type (Monetary Drain, Item Vanish, Movement Ban, etc) as an integer
        // @return int debuffType
        int getDebuffType() const;

        // Setters
        // @brief Sets the Debuff type (Monetary Drain, Item Vanish, Movement Ban, etc) based on an integer
        // @param int debuffType
        void setDebuffType(const int debuffType);

        // Other Functions
        // @brief Gets type of Debuff - Overriden from Item class - Monetary Drain, Item Vanish, Movement Ban, etc - overriden from Item.h
        // @return string itemType
        string getType() const override;
    private:
        int debuffType;
};

#endif