/***********************************
 * Class Name: PowerUp
 * 
 * Description: This header file contains the class declaration for PowerUp
 * and it's constructors, getters and setters
 * A PowerUp is an Item
***********************************/

#ifndef POWERUP_H
#define POWERUP_H

#include "Item.h"

class PowerUp : public Item {
    public:
        // Constructors
        // @brief Default constructor for PowerUp, will never be used
        PowerUp();
        // @brief Paramterized constructor for PowerUp, will be used when creating a PowerUp instance
        // @param int itemNum
        // @param string itemName
        // @param int itemPoints
        // @param int itemCost
        explicit PowerUp(const int itemNum, const string itemName, const int itemPoints, const int itemCost);

        // Getters
        // @brief Gets the PowerUp type (Budget Boost, Point Surge, Refund Request, etc) as an integer
        // @return int powerUpType
        int getPowerUpType() const;

        // Setters
        // @brief Sets the PowerUp type (Budget Boost, Point Surge, Refund Request, etc) based on an integer
        // @param int powerUpType
        void setPowerUpType(const int powerUpType);

        // Other Functions
        // @brief Gets type of PowerUp - Overriden from Item class - could be Budget Boost, Point Surge, Refund Request, etc - overriden from Item.h
        // @return string itemType
        string getType() const override;
    private:
        // Member Variables
        int powerUpType;
};

#endif