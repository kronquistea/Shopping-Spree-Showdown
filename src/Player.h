/***********************************
 * Class Name: Player
 * 
 * Description: This header file contains the class declaration for Player
 * and it's constructors, getters and setters, and other functions
 * A Player is a Token
***********************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player : public Token {
    public:
        // Constructors
        // @brief Default constructor for Player, never used
        Player();
        // @brief Parameterized constructor for Player, will be called when a new Player is created
        // @param int tokenNum
        // @param int playerRow
        // @param int playerCol
        explicit Player(const int tokenNum, const int playerRow, const int playerCol);
        
        // Other Functions
        // @brief Uses any number of Power Ups (According to the Player) and enacts their abilities - overriden from Token.h
        void usePowerUp() override;
    private:
};

#endif