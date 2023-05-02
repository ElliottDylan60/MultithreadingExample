#include "Board.h"
#include <iostream>
#include <pthread.h>

Board::Board(){
    //std::cout << "Created" << std::endl;
    //std::cout << "\033[31m" << "This text is red." << "\033[0m" << std::endl;
    //std::cout << "\033[32m" << "This text is green." << "\033[0m" << std::endl;
    //std::cout << "\033[33m" << "This text is yellow." << "\033[0m" << std::endl;
    //std::cout << "\033[34m" << "This text is blue." << "\033[0m" << std::endl;
    //std::cout << "\033[35m" << "This text is magenta." << "\033[0m" << std::endl;
    //std::cout << "\033[36m" << "This text is cyan." << "\033[0m" << std::endl;
}
Board::Board(const int rows, const int cols) : rows(rows), columns(cols){
    
    board = new Plot*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new Plot[cols];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            Plot temp;
            temp.currentOwner = -1;
            temp.PROTECTED = false;
            board[i][j] = temp;
        }
    }
}
void Board::printBoard(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j].currentOwner == EMPTY_PLOT){
                std::cout << "\033[32m" << "[ ]" << "\033[0m";
            }else if(board[i][j].currentOwner == TEAM_A){
                if(board[i][j].PROTECTED){
                    std::cout << "\033[33m" << "[A]" << "\033[0m";
                }else{
                    std::cout << "\033[31m" << "[A]" << "\033[0m";
                }
                
            }else if(board[i][j].currentOwner == TEAM_B){
                if(board[i][j].PROTECTED){
                    std::cout << "\033[33m" << "[B]" << "\033[0m";
                }else{
                    std::cout << "\033[34m" << "[B]" << "\033[0m";
                }
                
            }
        }
        std::cout << std::endl;
    }
}
int Board::fireMissle(int row, int col, int TEAM){
    
    if(board[row][col].PROTECTED){
        return 0;
    }
    switch(board[row][col].currentOwner){
        case EMPTY_PLOT:
            updatePlot(row, col, TEAM);
            break;
        case TEAM_A:
            if(TEAM == TEAM_A){
                board[row][col].currentOwner = EMPTY_PLOT;
            }else{
                updatePlot(row, col, TEAM);
            }
            break;
        case TEAM_B:
            if(TEAM == TEAM_B){
                board[row][col].currentOwner = EMPTY_PLOT;
            }else{
                updatePlot(row, col, TEAM);
            }
            break;
    }
    
    int delay = (rand() % 3) + 1;
    return delay;
}
void Board::updatePlot(int row, int col, int TEAM){
    if(!board[row][col].PROTECTED){
        board[row][col].currentOwner = TEAM;

        if(hasMaj(row, col) == TEAM){
            // Team B has majority
            updateSurrounding(row, col, TEAM);
        }
    }
}
void Board::updateSurrounding(int row, int col, int TEAM){
    for(int i = row-1; i <= row+1; i++){
        for(int j = col-1; j <= col+1; j++){
            if(i >= 0 && i < rows && j >= 0 && j < columns){
                if(!board[i][j].PROTECTED){
                    board[i][j].currentOwner = TEAM;
                }       
            }
        }
    }
}
int Board::hasMaj(int row, int col){
    int TEAM_A_COUNT = 0;
    int TEAM_B_COUNT = 0;
    for(int i = row-1; i <= row+1; i++){
        for(int j = col-1; j <= col+1; j++){
            if(i >= 0 && i < rows && j >= 0 && j < columns){        
                if(board[i][j].currentOwner==TEAM_A){
                    TEAM_A_COUNT++;
                }else if(board[i][j].currentOwner==TEAM_B){
                    TEAM_B_COUNT++;
                }
            }
        }
    }
    if(TEAM_A_COUNT > TEAM_B_COUNT){
        return TEAM_A;
    }
    return TEAM_B;
}
bool Board::placePlayer(int row, int col, int TEAM){
    if(board[row][col].PROTECTED){
        return false;
    }
    board[row][col].currentOwner = TEAM;
    board[row][col].PROTECTED = true;
    return true;
}
int Board::getRow(){
    return rows;
}
int Board::getCol(){
    return columns;
}
bool Board::isFull(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j].currentOwner == EMPTY_PLOT){
                return false;
            }
        }
    }
    return true;
}
int Board::Winner(){
    int TEAM_A_COUNT = 0;
    int TEAM_B_COUNT = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j].currentOwner == TEAM_A){
                TEAM_A_COUNT++;
            }else if(board[i][j].currentOwner == TEAM_B){
                TEAM_B_COUNT++;
            }
        }
    }
    if(TEAM_A_COUNT > TEAM_B_COUNT){
        return TEAM_A;
    }else if(TEAM_A_COUNT < TEAM_B_COUNT){
        return TEAM_B;
    }else{
        return -1;
    }
}