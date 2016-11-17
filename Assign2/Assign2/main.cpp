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

void meth(int num){
    
    int a = rand();
    std::this_thread::sleep_for(std::chrono::milliseconds(a%30000+1));
    std::cout << "Thread: " << num << " finished with " << a << "ms" << std::endl;
}


void printScore(Player p1, Player p2){

    int p1Score = p1.getScore();
    int p2Score = p2.getScore();
    
    std::cout << "___________________" << std::endl;
    std::cout << "|                 |" << std::endl;
    std::cout << "|      Score      |" << std::endl;
    std::cout << "|_________________|" << std::endl;
    std::cout << "|          |      |" << std::endl;
    if (p1.getAI()){
        std::cout << (p1Score < 10 ? "|   AI  X  |   " : "|   AI  X  |  ") << p1Score << "  |" << std::endl;
    }else {
        std::cout << (p1Score < 10 ? "| Player X |   " : "| Player X |  ") << p1Score << "  |" << std::endl;
    }
    if (p2.getAI()){
        std::cout << (p2Score < 10 ? "|  AI   O  |   " : "|  AI   O  |  ") << p2Score << "  |" << std::endl;
    }else {
        std::cout << (p2Score < 10 ? "| Player O |   " : "| Player O |  ") << p2Score << "  |" << std::endl;
    }
    std::cout << "|__________|______|" << std::endl;
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    
    Board* b = new Board();
    Player p1('X', false);
    Player p2('O', true);
    p1.setBoard(b);
    p2.setBoard(b);
    
    bool playing = true;
    
    while (playing){
        Board* b = new Board();
        Player p1('X', false);
        Player p2('O', true);
        p1.setBoard(b);
        p2.setBoard(b);

        
        printScore(p1, p2);
        b->printBoard();
        
        for (int i = 0; i < 12; i++){
    
            p1.getMove();
            
            printScore(p1, p2);
            b->printBoard();
            //std::cout << b->scoreAlmostPoint('X') << std::endl;

            p1.changeTurn();
            p2.changeTurn();
            
            p2.getMove();
            //std::cout << b->scoreAlmostPoint('O') << std::endl;
            printScore(p1, p2);
            b->printBoard();
            p1.changeTurn();
            p2.changeTurn();
            
            
        }
        
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
        std::cout << "Would you like to play another game? ";
        char choice;
        std::cin >> choice;
        
        if (choice == 'n')
            playing = false;
        
    }
    
    
    /*char board[8][3];
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 3; j++){
            board[i][j] = '*';
        }
    }
    
    board[7][0] = 'X';
    board[7][1] = 'O';
    
    board[2][0] = 'X';
    board[5][0] = 'O';
    
    
    for (int i = 2; i >= 0; i--){
        std::cout << "Level: " << i << std::endl;
        std::cout << board[0][i] << " " << board[1][i] << " " << board[2][i] << std::endl;
        std::cout << " " << board[3][i] << " " << board[4][i] << std::endl;
        std::cout << board[5][i] << " " << board[6][i] << " " << board[7][i] << std::endl;
        std::cout << std::endl;
    }
    
    std::thread thr[30];
    
    for (int i = 0; i < 30; i++){
        thr[i] = std::thread(meth, i);
    }
    
    for (int i = 0; i < 30; i++){
        thr[i].join();
    }
    */
    
    return 0;
}
