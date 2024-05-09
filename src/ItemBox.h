/***********************************
 * Class Name: ItemBox
 *
 * Description: This header file contains the class declaration for ItemBox
 * and it's constructors, getters and setters
 * An ItemBox has a vector of 5 Items
***********************************/

#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <vector>
    using std::vector;
#include "Item.h"

class ItemBox {
    public:
        // Constructors
        // @brief Default constructor for ItemBox, created ItemBoxes randomly
        ItemBox();
        // @brief Paramterized constructor for ItemBox, will be used when creating each Cell and its ItemBox
        // @param string filename
        explicit ItemBox(const string filename);

        // Destructor
        // @brief Destructor for ItemBox, deletes all Items belonging to the ItemBox
        ~ItemBox();

        // Getters
        // @brief Gets the list of items as a list of pointers
        // @return vector<Item*> listOfItemPtrs
        vector<Item*> getListOfItemPtrs() const;

        // Setters
        // @brief Sets the list of items based on parameter
        // @param vector<Item*> listOfItemPtrs
        void setListOfItemPtrs(const vector<Item*> listOfItemPtrs);

        // Other Functions
        // @brief Is called when the user of the program wants to create ItemBoxes randomly rather than by file
        void generateNewItems();
        // @brief Generates new items based on the desired file
        // @param string filename
        void generateNewItems(const string filename);
    private:
        // Member Variables
        vector<Item*> listOfItemPtrs;
};

#endif