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

/*
 
 0 1 2
  3 4
 5 6 7
 
 Diagonals:   : 1,2 inc: 2       S: 0,1 inc: 3
 Diagonals: {1,3,5}, {2,4,6}, {0,3,6}, {1,4,7}
 Diagonals: {1,3,5}, {0,3,6}, {1,4,7}, {2,4,6}
 
 All 3x3 Boards:
 {0,1,2}, {5,6,7}, {1,3,5}, {2,4,6}, {0,3,6}, {1,4,7}
 
 Horizontal: {0,1,2}, {5,6,7}
 
 
 |===========|
 |  Scores   |
 |===========|
 |Player 1: 0|
 |Player 2: 1|
 |===========|
 
 
  6       7       8
 [ ]     [ ]     [ ]
 [ ]     [ ]     [ ]
 [ ] [ ] [ ] [ ] [ ]
     [ ]     [ ]
 [ ] [ ] [ ] [ ] [ ]
 [ ]  4  [ ]  5  [ ]
 [ ]     [ ]     [ ]
 
 
 
 
 
 
 */


class Board{

    public:
    Board();
    Board(std::string);
    ~Board();
    std::array<Peg, 8> getBoard();
    bool placeBead(int, char);
    void printBoard();
    std::string stringify();
    bool isFull();
    int scoreBoard(char);
    
    
    private:
    std::array<Peg, 8> pegs;
    int score3x3(Peg, Peg, Peg, char);
    
};


#endif /* Board_hpp */
