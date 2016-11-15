//
//  Peg.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-29.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include "Peg.hpp"

Peg::Peg(){
    this->beads = std::vector<char>();
}

Peg::~Peg(){

}

std::vector<char> Peg::getBeads(){  // returns the beads of the
    return beads;
}

bool Peg::placeBead(char c){
    if (beads.size() >= 3)
        return false;
    beads.push_back(c);
    return true;
}

void Peg::printPegAt(int level){
    if (beads.size() >= level+1){
        std::cout << "[" << beads[level] << "]";
    } else{
        std::cout << "[ ]";
    }
}

long Peg::size(){
    return beads.size();
}
