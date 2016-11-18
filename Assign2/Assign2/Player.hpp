//
//  Player.hpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Board.hpp"
#include <regex>
#include <unordered_map>
#include <algorithm> 


class Player{

    public:
    
    Player(char, bool); // Character to use and if AI or not
    ~Player();
    void setBoard(Board*); // Passes the board to the player
    int getScore(); // Gets the player's score
    void getMove(); // Gets the player's move
    bool getAI(); // Gets if the player is an AI or not
    void changeTurn(); // Swaps the turn of the player
    bool getTurn(); // Returns if it is that player's turn or not
    
    private:
    bool isAI; // stores if the player is AI or not
    char charSymbol; // Stores the symbol the player will use (X or O)
    Board* board; // Stores the board
    bool isTurn = false; // Stores if it is the player's turn or not
    int minimax(std::string, int, bool); // The minimax algorithm
    int heuristic(Board); // The heuristic calculation
};


#endif /* Player_hpp */
