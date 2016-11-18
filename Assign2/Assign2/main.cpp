//
//  main.cpp
//  Assign2
//
//  Created by Adam Balint on 2016-10-26.
//  Copyright © 2016 Adam Balint. All rights reserved.
//

#include <iostream>

#include <thread>
#include <chrono>
#include "Player.hpp"
#include "Board.hpp"

// Prints the score in a nice scoreboard
void printScore(Player p1, Player p2){

    int p1Score = p1.getScore();
    int p2Score = p2.getScore();
    
    std::cout << "___________________" << std::endl;
    std::cout << "|                 |" << std::endl;
    std::cout << "|      Score      |" << std::endl;
    std::cout << "|_________________|" << std::endl;
    std::cout << "|          |      |" << std::endl;
    if (p1.getAI()){
        std::cout << (p1Score < 10 ? "|   AI   X |   " : "|   AI  X  |  ") << p1Score << "  |" << std::endl;
    }else {
        std::cout << (p1Score < 10 ? "| Player X |   " : "| Player X |  ") << p1Score << "  |" << std::endl;
    }
    if (p2.getAI()){
        std::cout << (p2Score < 10 ? "|   AI   O |   " : "|   AI  O  |  ") << p2Score << "  |" << std::endl;
    }else {
        std::cout << (p2Score < 10 ? "| Player O |   " : "| Player O |  ") << p2Score << "  |" << std::endl;
    }
    std::cout << "|__________|______|" << std::endl;
    std::cout << std::endl;
}

// Used to thread getting the player move
void getMove(Player* p){
    p->getMove();
}

int main(int argc, const char * argv[]) {
    bool playing = true; // Playing flag, if false, game will exit
    
    std::cout << "Welcome to the revolution! Welcome to 3D Tic-Tac-Toe" << std::endl;
    
    while (playing){
        // Set up default players and board
        Board* b = new Board();
        Player p1('X', false);
        Player p2('O', true);
        
        // Get user input for the players for AI or Human
        bool valid = false;
        while (!valid){
            std::cout << "Is player X a Human(H) or AI(A)? ";
            std::string response;
            std::cin >> response;
            if (response.compare("H") == 0 || response.compare("h") == 0){
                p1 = Player('X', false);
                valid = true;
            } else if (response.compare("A") == 0 || response.compare("a") == 0){
                p1 = Player('X', true);
                valid = true;
            } else if (response.compare("Q") || response.compare("q")){
                std::cout << "We are sorry to see you leave ㅠㅠ\nHave a great day!" << std::endl;
                exit(0);
            } else {
                std::cout << "Please enter A for AI or H for Human" << std::endl;
            }
        }
        valid = false;
        while (!valid){
            std::cout << "Is player O a Human(H) or AI(A)? ";
            std::string response;
            std::cin >> response;
            if (response.compare("H") == 0 || response.compare("h") == 0){
                p2 = Player('O', false);
                valid = true;
            } else if (response.compare("A") == 0 || response.compare("a") == 0){
                p2 = Player('O', true);
                valid = true;
            } else if (response.compare("Q") || response.compare("q")){
                std::cout << "We are sorry to see you leave ㅠㅠ\nHave a great day!" << std::endl;
                exit(0);
            } else {
                std::cout << "Please enter A for AI or H for Human" << std::endl;
            }
        }
        std::cout << "Type q at any time to quit" << std::endl;
        
        // Give each player the board
        p1.setBoard(b);
        p2.setBoard(b);

        // Print the initial score and board
        printScore(p1, p2);
        b->printBoard();
        
        for (int i = 0; i < 12; i++){
            
            // Set threads and get moves. Delay needed for proper printing
            // If there are 2 human players, don't thread
            std::thread p1t, p2t;
            if (p1.getAI() || p2.getAI()){
                p2t = std::thread(getMove, &p2);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                p1t = std::thread(getMove, &p1);
                // Wait until Player X makes a move and then print board
                p1t.join();
            } else {
                p1.getMove();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            printScore(p1, p2);
            b->printBoard();
            
            // Swap the player turns
            p1.changeTurn();
            p2.changeTurn();
            
            if (p1.getAI() || p2.getAI()){
            // Wait until Player O make it's move. Delay needed for proper printing
                p2t.join();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            } else {
                p2.getMove();
            }
            // Print score and board and then change turns
            printScore(p1, p2);
            b->printBoard();
            p1.changeTurn();
            p2.changeTurn();
        }
        
        // Game done, Display winner and ask if the user wants to play another game
        std::cout << "Congratulations ";
        int p1Score, p2Score;
        p1Score = p1.getScore();
        p2Score = p2.getScore();
        if (p1Score > p2Score){
            std::cout << (p1.getAI() ? "AI X has won!" : "Player X has won!");
        }else if (p2Score > p1Score){
            std::cout << (p2.getAI() ? "AI O has won!" : "Player O has won!");
        }else {
            std::cout << "both players have won!" << std::endl;
        }
        std::cout << "Would you like to play another game? (y/n) ";
        char choice;
        std::cin >> choice;
        
        // If choice is no then quit
        if (choice == 'n' || choice == 'N')
            playing = false;
    }
    return 0;
}
