/***********************************
 * Class Name: Token
 *
 * Description: This header file contains the class declaration for Token
 * and it's constructors, getters and setters, and other functions. This class is Abstract.
 * A Token can be a Player or a Computer
***********************************/

#ifndef TOKEN_H
#define TOKEN_H

#include "Item.h"
#include <string>
    using std::string;
#include <vector>
    using std::vector;
// #include "Board.h"

class Token {
    public:
        // Constructors
        // @brief Default constructor for Token, will never be used
        Token();
        // @brief Parameterized constructor for Token, sets xCoord and yCoord of the token to the designated starting Cell's location
        // @param int tokenNum
        // @param int tokenRow
        // @param int tokenCol
        // @param string tokenType
        Token(const int tokenNum, const int tokenRow, const int tokenCol, const string tokenType);
        
        // Destructor
        // @brief Destructor for Token delets all items from the item vector and sets them to nullptrs
        ~Token();

        // Getters
        // @brief Gets the Token number
        // @return int tokeNum
        int getTokenNum() const;
        // @brief Gets points of Token
        // @return int points
        int getTokenPoints() const;
        // @brief Gets budget of Token
        // @return int budget
        int getTokenBudget() const;
        // @brief Gets row of Token
        // @return int tokenRow
        int getTokenRow() const;
        // @brief Gets column of Token
        // @return int tokenCol
        int getTokenCol() const;
        // @brief Gets token type
        // @return string tokenType
        string getTokenType() const;
        // @brief Gets the Items that the Token owns
        // @return vector<Item*> tokenVectorOfItems
        vector<Item*> getTokenVectorOfItems() const;
        // @brief Gets the turns that the special items that the Token gained them (Power Ups and Debuffs only)
        // @return vector<int> specialItemsGainedTurns
        vector<int> getSpecialItemsGainedTurns() const;
        // @brief Gets the names of the special items that the Token gained throughout the game (Power Ups and Debuffs only)
        // @return vector<string> specialItemsGained
        vector<string> getSpecialItemsGained() const;
        // @brief Gets the names of the normal items that the Token gained throughout the game
        // @return vector<string> normalItemsGained
        vector<string> getNormalItemsGained() const;
        // @brief Gets the status of the movementBanStatus variable, true means Token is banned from moving, false otherwise
        // @return bool movementBanStatus
        bool getMovementBanStatus() const;
        // @brief Gets the turn that the movement ban was applied on
        // @return int movementBanStartTurn
        int getMovementBanStartTurn() const;
        // @brief Gets the number of Debuffs that the Token had applied during the game
        // @return int numDebuffsUsed
        int getNumDebuffsUsed() const;

        // Setters
        // @brief Sets the Token Num
        // @param const int tokenNum
        void setTokenNum(const int tokenNum);
        // @brief Sets points of Token
        // @param int points
        void setTokenPoints(const int points);
        // @brief Sets budget of Token
        // @param int budget
        void setTokenBudget(const int budget);
        // @brief Sets row of Token
        // @param int tokenRow
        void setTokenRow(const int tokenRow);
        // @brief Sets column of Token
        // @param int playerCol
        void setTokenCol(const int tokenCol);
        // @brief Sets token type
        // @param string tokenType
        void setTokenType(const string tokenType);
        // @brief Sets the Items that the Token owns
        // @param vector<Item*> tokenVectorOfItems
        void setTokenVectorOfItems(const vector<Item*> tokenVectorOfItems);
        // @brief Sets the turns that the special items that the Token gained them (Power Ups and Debuffs only)
        // @return vector<int> specialItemsGainedTurns
        void setSpecialItemsGainedTurns(const vector<int> specialItemsGainedTurns);
        // @brief sets the names of the special items that the Token gained throughout the game (Power Ups and Debuffs only)
        // @return vector<int> specialItemsGained
        void setSpecialItemsGained(const vector<string> specialItemsGained);
        // @brief Sets the vector for the normal items the Token gained during the game
        // @param const vector<string> normalItemsGained
        void setNormalItemsGained(const vector<string> normalItemsGained);
        // @brief Sets the status of the movement ban, true if they are banned from moving, false otherwise
        // @param bool movementBanStatus
        void setMovementBanStatus(const bool movementBanStatus);
        // @brief Sets the turn that the movement ban started
        // @param int movementBanStartTurn
        void setMovementBanStartTurn(const int movementBanStartTurn);
        // @brief Sets the number of Debuffs that the Token had applied during the game
        // @param int numDebuffsUsed
        void setNumDebuffsUsed(const int numDebuffsUsed);
        /* @brief Sets new coordinates for the Token (Player or Computer)
           @param int newTokenRow
           @param int newTokenCol*/
        void setCoordinates(const int newTokenRow, const int newTokenCol);

        // Other Functions
        // @brief Adds an item to the tokenOfVectorItems member variable
        // @param Item* itemPtr
        void addAnItem(Item *itemPtr);
        // @brief Uses a Debuff when it is gained
        // @param string debuffName
        void useDebuff(string debuffName);
        // @brief Uses a Power Up, random chance for Computer, asks Player if they want to use theirs
        virtual void usePowerUp() = 0; // Pure Virtual Function
    private:
        // Member Variables
        int tokenNum;
        int points;
        int budget;
        int tokenRow;
        int tokenCol;
        string tokenType;
        vector<Item*> tokenVectorOfItems;
        vector<int> specialItemsGainedTurns;
        vector<string> specialItemsGained;
        vector<string> normalItemsGained;
        bool movementBanStatus;
        int movementBanStartTurn;
        int numDebuffsUsed;
};

#endif