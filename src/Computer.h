/***********************************
 * Class Name: Computer
 * 
 * Description: This header file contains the class declaration for Computer
 * and it's constructors, getters and setters
 * A Computer is a Token
***********************************/

#ifndef COMPUTER_H
#define COMPUTER_H

#include "Board.h"

class Computer : public Token {
    public:
        // Constructors
        // @brief Default constructor for Computer - will never be used
        Computer();
        // @brief Parameterized constructor, calls generateXCoord and generateYCoord to determine starting location
        // @param int tokenNum
        // @param int randomRow
        // @param int randomCol
        explicit Computer(const int tokenNum, int randomRow, int randomCol);

        // Other Functions
        // @brief Generates random coordinates returning them in a vector where x = index 0 and y = index 1
        // @param array2DCells arrayOfCells
        void generateRandomCoordinates(array<array<Cell, 5>, 5> arrayOfCells);
        // @brief Use any number of Power Ups randomly - overriden from Token.h
        void usePowerUp() override;
    private:
};

#endif