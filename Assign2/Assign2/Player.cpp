//
//  Player.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include "Player.hpp"

// Creates a player using the pieces specified.
// If the player is an AI or not is also specified
Player::Player(char c, bool ai){
    charSymbol = c;
    if (charSymbol == 'X')
        isTurn = true;
    isAI = ai;
}

Player::~Player(){
    
}

// Sets the board the player will use
void Player::setBoard(Board* brd){
    board = brd;
}

// Gets the player's score
int Player:: getScore(){
    return board->scoreBoard(charSymbol);
}


// Gets the move from the player.
// If the player is human, then it waits for human input
// If the player is AI, then it runs minimax to find the next move
void Player::getMove(){
    std::regex reg("[a-hA-H]{1}");
    
    // If the player is human
    if (!isAI){
        bool played = false;
        
        // Ask the player for input
        std::cout << "Please enter the peg you wish to place a bead on: ";
        std::string move;
        while (!played){
            // Get the user input
            std::cin >> move;
            // Check for valid input
            if (std::regex_match(move, reg)){
                // If valid, try placing it. If the placement is not valid ask for another move
                played = true;
                bool valid = board->placeBead(toupper(move[0])-'A', charSymbol);
                if (!valid){
                    std::cout << "This peg is full. Please enter a valid move" << std::endl;
                    played = false;
                }
            }
            // If the input was invalid, check if they want to quit
            else if (move.compare("q") == 0 || move.compare("Q") == 0){
                std::cout << "We are sorry to see you leave ㅠㅠ\nHave a great day!" << std::endl;
                exit(0);
            }
            // If it was invalid, and they didn't want to quit, then promt for another letter
            else{
                std::cout << "Please enter a letter from A to H" << std::endl;
            }
        }
        
    }
    // If the player is AI
    else {
        // Show that it is doing comething
        std::cout <<"\nThe AI is thinking..." << std::endl;
        
        // Store Board as key and hold the best move to make
        std::unordered_map<std::string, int> cur;
        std::string boardRep = board->stringify();
        
        // If it is not this player's turn
        if (!isTurn){
            // Go through each move the opponent could make
            for (int j = 0; j < 8; j++){
                // Set up the default best move and best score
                int best = -1;
                int bestScore = -10000000;
                
                // Create a copy of the current board
                Board b2(boardRep);
                // try placing a bead for the opponent to anticipate their move
                bool placed2 = b2.placeBead(j, (charSymbol == 'O') ? 'X' : 'O');
                
                // if it was successful, then run minimax on that board
                if (placed2){
                    
                    // Generate all the boards I can respond with
                    for (int i = 0; i < 8; i++){
                        Board b(b2.stringify());
                        bool placed = b.placeBead(i, charSymbol);
                        if (placed){
                            // Calculate the score of that move
                            int score = minimax(b.stringify(), 4, true);
                            if (bestScore < score){
                                bestScore = score;
                                best = i;
                            }
                        }
                    }
                    // store the best remponse to the possible oppenent board
                    cur[b2.stringify()] = best;
                }
            }
            // Wait for the turns to swap
            while(!isTurn);
            
            // Print where the AI placed for the user, and place bead
            std::cout << "AI " << charSymbol << " Played on: " << (char)('A'+cur[board->stringify()]) << std::endl;
            board->placeBead(cur[board->stringify()], charSymbol);
            
        }
        // If it is the AI's turn
        else {
            // Do the same as above without accounting for the opponent's move as the opponent has alread played
            int best = -1;
            int bestScore = -10000000;
            
            // Generate all the boards I can respond with
            for (int i = 0; i < 8; i++){
                Board b(boardRep);
                bool placed = b.placeBead(i, charSymbol);
                if (placed){
                    
                    // Calculate the score of that move
                    int score = minimax(b.stringify(), 4, true);
                    if (bestScore < score){
                        bestScore = score;
                        best = i;
                        
                    }
                }
            }
            // Print out where the AI moved for the player and place the bead
            board->placeBead(best, charSymbol);
            std::cout << "AI " << charSymbol << " Played on: " << (char)('A'+best) << std::endl;
        }
        
    }
}

// Changes whose turn it is
void Player::changeTurn (){
    isTurn = !isTurn;
}


// Calculates the score of the current board
// A combination of the points already earned, and the points that only have 1 bead missing
// It tries maximizin it's points compared to the oppenent's points, while trying to create
// more situations that could result in points compared to the ememy once again
int Player::heuristic(Board b){
    int myScore = b.scoreBoard(charSymbol);
    int oppScore = b.scoreBoard((charSymbol == 'O') ? 'X' : 'O');
    int myAlmostScore = b.scoreAlmostPoint(charSymbol);
    int oppAlmostscore = b.scoreAlmostPoint((charSymbol == 'O') ? 'X' : 'O');
    
    return ((myScore-oppScore)*90 + (myAlmostScore - oppAlmostscore)*10);
}

// The minimax code
int Player::minimax(std::string node, int depth, bool maximizing) {
    // If we reached the ply level, calculate the board score
    if ( depth == 0 ){
        Board b(node);
        return heuristic(b);
    }
    // Calculate the best score of the board
    int max = -1000000;
    for (int i = 0; i < 8; i++){
        Board b(node);
        bool placed = b.placeBead(i, maximizing ? 'X' : 'O');
        int score = -1000000000;
        if (placed){
            score = minimax(b.stringify(), depth - 1, !maximizing);
            if(score > max)
                max = score;
        }
    }
    // Return the score
    return (maximizing ? -1 : 1) * max;
}

// Gets if the player is an AI or not
bool Player::getAI(){
    return isAI;
}

bool Player::getTurn(){
    return isTurn;
}

