//
//  Board.hpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include "Peg.hpp"
#include <array>
#include <vector>
#include <iostream>


class Board{

    public:
    Board(); // Board constructor
    Board(std::string); // Board constructor using a string of boead placements
    ~Board();
    std::array<Peg, 8> getBoard(); // Returns the pegs of the board
    bool placeBead(int, char); // Places a bead on the board
    void printBoard(); // Prints the board
    std::string stringify(); // converts the board to a string representation of the board
    int scoreBoard(char); // Calculates the number of points the specified player has
    int scoreAlmostPoint(char); // Calculates the number of 2 bead 1 empty combinations on a 3x3 board
    bool hasMoves(); // Checks if the board has moves
    
    private:
    // Array of pegs that hold the beads
    std::array<Peg, 8> pegs;
    // count of total number of beads
    int totBeads = 0;
    int score3x3(Peg, Peg, Peg, char); //Calculates the number of points the specified player has on a 3x3 board
    int scoreAlmostPoint3x3(Peg, Peg, Peg, char); // Calculates the number of 2 bead 1 empty combinations on a 3x3 board
    
};


#endif /* Board_hpp */
