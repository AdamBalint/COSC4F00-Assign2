//
//  Player.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include "Player.hpp"

Player::Player(char c, bool ai){
    charSymbol = c;
    isAI = ai;
}

Player::~Player(){

}

void Player::setBoard(Board* brd){ // Pases the board to the player
    board = brd;
}

int Player:: getScore(){
    
    return board->scoreBoard(charSymbol);
}

void Player::getMove(){
    std::regex reg("[a-hA-H]{1}");
    if (!isAI){
        bool played = false;
        std::cout << "Please enter the peg you wish to place a bead on: ";
        std::string move;
        while (!played){
            std::cin >> move;
            if (std::regex_match(move, reg)){
                played = true;
            }else{
                std::cout << "Please enter a letter from A to H" << std::endl;
            }
        }
        board->placeBead(toupper(move[0])-'A', charSymbol);
    }
    else {
        // Store Board as key and hold the best move to make
        std::unordered_map<std::string, int> cur;
        
        
    }
}




bool Player::getAI(){
    return isAI;
}


