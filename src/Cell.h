/***********************************
 * Class Name: Cell
 * 
 * Description: This header file contains the class declaration for Cell
 * and it's constructors, getters and setters
 * A Cell has an Item Box
 * A Cell has a Token which is set to NULL unless a Token is present
***********************************/

#ifndef CELL_H
#define CELL_H

#include "Token.h"
#include "ItemBox.h"
#include "Item.h"

extern string fileToUse;

class Cell {
    public:
        // Constructors
        // @brief Default constructor for Cell
        Cell();
        // @brief Parameterized constructor for Cell, will be called when Board is created and Cells are created
        // @param int itemInitializationOption
        explicit Cell(int itemInitializationOption);
        
        // Getters
        // @brief Gets the ItemBox in the cell
        // @return ItemBox itemBox
        ItemBox* getItemBox() const;
        // @brief Get the Token present in the cell
        // @return Token* tokenPtr
        Token* getTokenPtr() const;

        // Setters
        // @brief Sets itemBox for the Cell
        // @param ItemBox& itemBox
        void setItemBox(ItemBox *itemBox);
        // @brief Sets the tokenPtr for the Cell
        // @param Token* tokenPtr
        void setTokenPtr(Token *tokenPtr);

        // Other Functions
        // @brief Opens the itemBox when a Token is present in the Cell for the first time
        // @return vector<Item*> listOfItemPtrs
        void openItemBox(Token* tokenPtr);
        // @brief Checks if the Cell contains a nullptr and returns true if it does
        // @return bool available
        bool cellIsFree();
    private:
        // Member Variables
        ItemBox *itemBoxPtr = nullptr;
        Token *tokenPtr = nullptr;
};

#endif