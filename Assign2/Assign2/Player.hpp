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
    void setBoard(Board*); // Pases the board to the player
    int getScore();
    void getMove();
    bool getAI();
    void changeTurn();
   // static void threadGetMove(Player p);
    
    
    private:
    bool isAI;
    char charSymbol;
    Board* board;
    int score = 0;
    int getBestMove(std::string);
    int getBestMove(int, std::string, int, char);
    bool isTurn = false;
    int minimax(std::string, int, bool);
    int heuristic(Board);
    //int minimax(std::string, int, bool, int, int);
};


#endif /* Player_hpp */
