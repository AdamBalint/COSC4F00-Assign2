//
//  Board.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include "Board.hpp"

// Default constructor - Uses 8 Empty pegs
Board::Board(){
    for (int i = 0; i < 8; i++){
        pegs[i] = Peg();
    }
}

// String Constructor - Places beads based on location in the string
Board::Board(std::string s){
    for (int i = 0; i < s.length(); i++){
        if (s[i] != ' '){
            pegs[i%8].placeBead(s[i]);
            totBeads++;
        }
    }
}

Board::~Board(){
    
}

// Places a bead on a specific peg
// Returns true if it could place it, otherwise it returns false
bool Board::placeBead(int peg, char c){
    if (pegs[peg].size() == 3){
        return false;
    }
    pegs[peg].placeBead(c);
    totBeads++;
    return true;
}


// Prints out the board
void Board::printBoard(){
   
    std::cout << " A       B       C" << std::endl;
    for (int i = 2; i >= 0; i--){
        pegs[0].printPegAt(i);
        if (i == 0){
            std::cout << "  D  ";
        } else {
            std::cout << "     ";
        }
        pegs[1].printPegAt(i);
        if (i == 0){
            std::cout << "  E  ";
        } else {
            std::cout << "     ";
        }
        pegs[2].printPegAt(i);
        std::cout << std::endl;
    }
    
    for (int i = 2; i >= 0; i--){
        if (i == 0){
            std::cout << " F  ";
        } else{
            std::cout << "    ";
        }
        pegs[3].printPegAt(i);
        if (i == 0){
            std::cout << "  G  ";
        } else{
            std::cout << "     ";
        }
        pegs[4].printPegAt(i);
        if (i == 0){
            std::cout << "  H  ";
        } else{
            std::cout << "    ";
        }
        std::cout << std::endl;
    }

    for (int i = 2; i >= 0; i--){
        pegs[5].printPegAt(i);
        std::cout << "     ";
        pegs[6].printPegAt(i);
        std::cout << "     ";
        pegs[7].printPegAt(i);
        std::cout << std::endl;
    }
    std::cout << "\n\n" << std::endl;
    
}

// Returns the array of pegs
std::array<Peg, 8> Board::getBoard(){
    return pegs;
}

// Converts the board to a string representation
// Used in the constructor taking the string
std::string Board::stringify(){
    std::string res;
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 8; j++){
            if (pegs[j].size() >= i+1){
                res += pegs[j].getBeads()[i];
            } else{
                res += " ";
            }
        }
    }
    
    return res;
}

// Calculates the score for the board from the view of the player
int Board::scoreBoard(char player){
    int score = 0;
    
    // The board can be thought of a set of 6, 3x3 boards slotted together.
    // This calculation takes advantage of that.
    
    // Defines the set of 3x3 boards
    int boardCombos[6][3] = {{0,1,2}, {5,6,7}, {1,3,5}, {2,4,6}, {0,3,6}, {1,4,7}};
    
    // Lopps through the boards and calculates the horizontal and diagonal for each board
    for (int i = 0; i < 6; i++){
        score += score3x3(pegs[boardCombos[i][0]], pegs[boardCombos[i][1]], pegs[boardCombos[i][2]], player);
    }
    
    // Loops through and calculates the vertical for each peg
    for (int i = 0; i < pegs.size(); i++){
        std::vector<char> b = pegs.at(i).getBeads();
        // Checks for Vertical line
        if (b.size() == 3)
            if (b[0] == player && b[1] == player && b[2] == player){
                score += 1;
            }
    }
    
    // Returns the score for the player
    return score;
}

// Scores the 3x3 board
int Board::score3x3(Peg left, Peg middle, Peg right, char player){
    int score = 0;
    
    // Creates the 3x3 board using the pegs provided
    std::array<std::vector<char>, 3> b;
    b[0] = left.getBeads();
    b[1] = middle.getBeads();
    b[2] = right.getBeads();
    
    for (int i = 0; i < 3; i++){
        // Checks for Horizontal line
        if (b[0].size() >= i+1 && b[1].size() >= i+1 && b[2].size() >= i+1)
            if (b[0][i] == player && b[1][i] == player && b[2][i] == player){
                score += 1;
            }
    }
    // Checks for Diagonals
    if (b[1].size() >= 2)
        if (b[1][1] == player){
            if (b[0].size() >= 1 && b[2].size() == 3 && b[0][0] == player && b[2][2] == player){
                score += 1;
            }
            if (b[2].size() >= 1 && b[0].size() == 3 && b[0][2] == player && b[2][0] == player){
                score += 1;
            }
        }
    
    // Returns the score for the 3x3 board
    return score;
}

// Almost point calculated the number of places where the player has 2 in a line, with the 3rd one missing
// Uses the same 3x3 board logic as above
int Board::scoreAlmostPoint(char player){
    int num = 0;
    
    int boardCombos[6][3] = {{0,1,2}, {5,6,7}, {1,3,5}, {2,4,6}, {0,3,6}, {1,4,7}};

    // Checks the 3x3 boards
    for (int i = 0; i < 6; i++){
        num += scoreAlmostPoint3x3(pegs[boardCombos[i][0]], pegs[boardCombos[i][1]], pegs[boardCombos[i][2]], player);
    }
    
    // Check for 2 vertically
    for (int i = 0; i < 8; i++){
        if (pegs.at(i).size() == 2){
            std::vector<char> bds = pegs.at(i).getBeads();
            if (bds.at(0) == player && bds.at(1) == player)
                num++;
        }
    }
    return num;
}


// Scores the almost point for the 3x3 board horizontally and diagonally
int Board::scoreAlmostPoint3x3(Peg left, Peg middle, Peg right, char player){
    int num = 0;
    
    // Sets up the 3x3 board
    std::array<std::vector<char>, 3> b;
    b[0] = left.getBeads();
    b[1] = middle.getBeads();
    b[2] = right.getBeads();
    
    // loops upwards vertically on the 3x3 board
    for (int i = 0; i < 3; i++){
        // Checks for Horizontal line
        int score = 0;
        // loops horizontally across the row
        for (int j = 0; j < 3; j++){
            //if there is a bead there
            if (b[j].size() >= i+1){
                // if it is the players bead increase the score otherwise decrease
                if (b[j][i] == player){
                    score++;
                }else{
                    score--;
                }
            }
        }
        // If there is a score of 2, then that means that there are 2 of the player's
        // beads horizontally with a spot for a third, if it is 1, then the line of 3 has been blocked
        if (score == 2)
            num++;
    }
    
    int scoreUR = 0;
    int scoreDR = 0;
    
    // Checks both diagonals using the same logic
    for (int i = 0; i < 3; i++){
        if (b[i].size() >= i+1){
            if (b[i][i] == player){
                scoreUR++;
            }else {
                scoreUR--;
            }
        }
        if (b[2-i].size() >= i+1){
            if (b[2-i][i] == player){
                scoreDR++;
            }else {
                scoreDR--;
            }
        }
    }
    
    // If the score is 2 then it increments the number of almost points
    if (scoreUR == 2){
        num++;
    }
    if (scoreDR == 2){
        num++;
    }
    
    // Returns the number of almost points on the 3x3 board
    return num;
}

// Returns if there are any moves left
bool Board::hasMoves(){
    return !(totBeads == 24);
}
