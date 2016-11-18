//
//  Peg.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include "Peg.hpp"

// Creates an empty peg
Peg::Peg(){
    this->beads = std::vector<char>();
}

Peg::~Peg(){

}

// Returns the vector containing the beads
std::vector<char> Peg::getBeads(){  // returns the beads of the
    return beads;
}

// Tries placing a bead. If there are 3 beads on it, it return false
// Otherwise it adds the bead and return true
bool Peg::placeBead(char c){
    if (beads.size() >= 3)
        return false;
    beads.push_back(c);
    return true;
}

// Prints the bead on the peg at the specified level
void Peg::printPegAt(int level){
    if (beads.size() >= level+1){
        std::cout << "[" << beads[level] << "]";
    } else{
        std::cout << "[ ]";
    }
}


// Returns the number of beads on the peg
long Peg::size(){
    return beads.size();
}
