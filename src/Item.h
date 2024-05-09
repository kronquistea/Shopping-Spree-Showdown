/***********************************
 * Class Name: Item
 *
 * Description: This header file contains the class declaration for Item
 * and it's constructors, getters and setters, this class is Abstract.
 * Format of ListOfItems.txt - Item #, Item Type, Item Name, Item Point Value, Item Cost
***********************************/

#ifndef ITEM_H
#define ITEM_H

#include <string>
   using std::string;

class Item {
   public:
      // Constructors
      // @brief Default constructor for Item, will never be used
      Item();
      // @brief Paramterized constructor for Item, will be used when the specific object types are created
      // @param int itemNum
      // @param string itemName
      // @param int points
      // @param int cost
      explicit Item(const int itemNum, const string itemName, const int points, const int cost);
      
      // Destructor
      // @brief Destructor for Item, left empty
      ~Item();

      // Getters
      // @brief Gets the Item number
      // @return int itemNum
      int getItemNum() const;
      // @brief Gets the Item name
      // @return string itemName
      string getItemName() const;
      // @brief Gets the points that the Item is worth
      // @return points
      int getItemPoints() const;
      // @brief Gets the cost of the Item
      // @return int cost
      int getItemCost() const;

      // Setters
      // @brief Sets the item number
      // @param int itemNum
      void setItemNum(const int itemNum);
      // @brief Sets the item name
      // @param string itemName
      void setItemName(const string itemName);
      // @brief Sets how many points the item is worth
      // @param int points
      void setItemPoints(const int points);
      // @brief Sets the cost of the item
      // @param int cost
      void setItemCost(const int cost);

      // Other Functions
      // @brief Gets the item type - Normal Item, Debuff, Power Up - will be overriden in the derived classes (PowerUp, NormalItem, Debuff)
      // @return string itemType
      virtual string getType() const = 0; // Pure virtual
   private:
      // Member Variables
      int itemNum;
      string itemName;
      int points;
      int cost;
};

#endif