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
    if (charSymbol == 'X')
        isTurn = true;
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
                bool valid = board->placeBead(toupper(move[0])-'A', charSymbol);
                if (!valid){
                    std::cout << "This peg is full. Please enter a valid move" << std::endl;
                    played = false;
                }
            }else{
                std::cout << "Please enter a letter from A to H" << std::endl;
            }
        }
        
    }
    else {
        std::cout <<"\nThe AI is thinking..." << std::endl;
        
        // Store Board as key and hold the best move to make
        std::unordered_map<std::string, int> cur;
        std::string boardRep = board->stringify();
        
        int best = -1;
        int bestScore = -10000000;
        
        // Generate all the boards I can respond with
        for (int i = 0; i < 8; i++){
            Board b(boardRep);
            bool placed = b.placeBead(i, charSymbol);
                //int best = getBestMove(b.stringify());
                //cur[b.stringify()] = best;
            if (placed){
                /*
                 O - bool: true, no inverse
                 X - bool: true, no inverse
                 */
                int score = minimax(b.stringify(), 4, true);
               // if (charSymbol == 'O')
                 //   score *= -1;
                
                //std::cout << "Best: " << best << std::endl;
                //std::cout << "Best Score: " << bestScore << std::endl;
                //std::cout << "Score: " << score << std::endl;
                //std::cout << std::endl;
                
                if (bestScore < score){
                    bestScore = score;
                    best = i;
                    
                }
            }
            
        }
       // std::cout << "Move: " << best << " Best Score: " << bestScore << std::endl;
        
        while(!isTurn);
        
        //board->placeBead(cur[board->stringify()], charSymbol);
        board->placeBead(best, charSymbol);
        std::cout << "AI Played on: " << (char)('A'+best) << std::endl;
    }
}

void Player::changeTurn (){
    isTurn = !isTurn;
}


int Player::heuristic(Board b){
    int myScore = b.scoreBoard(charSymbol);
    int oppScore = b.scoreBoard((charSymbol == 'O') ? 'X' : 'O');
    int myAlmostScore = b.scoreAlmostPoint(charSymbol);
    int oppAlmostscore = b.scoreAlmostPoint((charSymbol == 'O') ? 'X' : 'O');
    
    return ((myScore-oppScore)*90 + (myAlmostScore - oppAlmostscore)*10);
}

int Player::minimax(std::string node, int depth, bool maximizing) {
    if ( depth == 0 ){
        Board b(node);
        return heuristic(b);
    }
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
    return (maximizing ? -1 : 1) * max;
}


/*
 
 
 */


/*
int Player::minimax(std::string node, int depth, bool maximizingPlayer){
    Board b(node);
    if (depth == 0 || !(b.hasMoves())){
        int myScore = b.scoreBoard(charSymbol);
        int oppScore = b.scoreBoard((charSymbol == 'O') ? 'X' : 'O');
        return myScore - oppScore;
    }
    
    if (maximizingPlayer){
        int bestValue = -10000000;
        for (int i = 0; i < 8; i++){
            //Generate child
            Board child(b.stringify());
            bool placed = child.placeBead(i, (maximizingPlayer) ? charSymbol : (charSymbol == 'O') ? 'X' : 'O');
            if (placed){
                int v = minimax(child.stringify(), (depth-1), false);
                bestValue = std::max(bestValue, -v);
            }else {
                int v = -1000000000;
                bestValue = std::max(bestValue, -v);
            }
        }
        return bestValue;
    }
    //minimizing player
    else {
        int bestValue = 10000000;
        for (int i = 0; i < 8; i++){
            //Generate child
            Board child(b.stringify());
            bool placed = child.placeBead(i, (!maximizingPlayer) ? ((charSymbol == 'O') ? 'X' : 'O') : charSymbol);
            if (placed){
                int v = minimax(child.stringify(), (depth-1), true);
                bestValue = std::min(bestValue, v);
            }else {
                int v = 1000000000;
                bestValue = std::min(bestValue, v);
            }
        }
        return bestValue;
    }
}
*/


// Generate all the moved the opponent can respond with
int Player::getBestMove(std::string s){
    int score = -1000000;
    int bestMove = -1;
    
    for (int i = 0; i < 8; i++){
        Board b(s);
        bool placed = b.placeBead(i, (charSymbol == 'O') ? 'X' : 'O');
    
        if (placed){
            int myScore = b.scoreBoard(charSymbol);
            int oppScore = b.scoreBoard((charSymbol == 'O') ? 'X' : 'O');
            
            if (score < (oppScore - myScore)){
                score = (oppScore - myScore);
                bestMove = i;
            }
        }
        
    }
    /*
    std::cout << "Best move for board " << std::endl;
    Board b(s);
    b.printBoard();
    std::cout << " " << bestMove << "\tWith a Score of " << score << std::endl;*/
    return bestMove;
}

/*
int Player::getBestMove(int level, std::string boardRep, int next, char opponent){
    int bestMove = -1;
    int bestScore = -1000000;
    if (level == 3)
        return getScore();
    Board b(boardRep);
    bool placed = b.placeBead(next, opponent);
    std::cout << "Bead placed at " << next << " by: " << opponent << std::endl;
    
    if (placed){
        for (int i = 0; i < 8; i++){
            int score = getBestMove(level+1, b.stringify(), i, (opponent == 'X') ? 'O': 'X');
           // std::cout << "Level " << level << " Move to: " << i << " score: " << score << " player: " << opponent << std::endl;
            if (score >= bestScore){
                bestScore = score;
                bestMove = i;
            }
        }
    }
    
    return bestMove;
}
*/



bool Player::getAI(){
    return isAI;
}


