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

class Player{

    public:
    
    Player(char, bool); // Character to use and if AI or not
    ~Player();
    void setBoard(Board*); // Pases the board to the player
    int getScore();
    void getMove();
    bool getAI();
    
    
    private:
    bool isAI;
    char charSymbol;
    Board* board;
    int score = 0;
    
    
};


#endif /* Player_hpp */
