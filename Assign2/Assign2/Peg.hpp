//
//  Peg.hpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#ifndef Peg_hpp

#define Peg_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class Peg{

public:
    Peg(); // Creates a peg
    ~Peg();
    bool placeBead(char); // Places a bead on the peg
    std::vector<char> getBeads(); // returns the beads of the
    void printPegAt(int); // Prints the bead at the specific level of the peg
    long size(); // returns the number of beads on the peg
    
private:
    std::vector<char> beads;// Peg can hold 3 beads
};
#endif /* Peg_hpp */

