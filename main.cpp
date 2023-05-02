#include "Board.h"
#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

// Shared Memory
Board myBoard;
pthread_mutex_t my_mutex;
bool winner = false;
int totalReady = 0;
int totalPlayers = 0;
void *CheckForWinner(void* param){
    while(!winner){
         pthread_mutex_lock(&my_mutex);
        if(myBoard.isFull()){
            winner = true;
        }
        pthread_mutex_unlock(&my_mutex);
    }
    pthread_exit(NULL);
}
void *player(void* TEAM){
    int TEAM_ID;
    if((int*)TEAM){
        TEAM_ID = 1;
    }else{
        TEAM_ID = 0;
    }
    
    pthread_mutex_lock(&my_mutex);
    while(true){
        // More efficient way of doing this:
        // 1) create array of available spots, 
        // 2) choose random spot, 
        // 3) remove spot from array, 
        // 4) repeat
        
        int row = rand() % myBoard.getRow();
        int col = rand() % myBoard.getCol();
        if(myBoard.placePlayer(row, col, TEAM_ID)){
            cout << "Successful Place: " << endl;
            myBoard.printBoard();
            totalReady++;
            break;
        }
    }
    pthread_mutex_unlock(&my_mutex);
    while(totalReady != totalPlayers){
        // wait for all processes to be ready
    }
    while(!winner){
        pthread_mutex_lock(&my_mutex);
        int row = rand() % myBoard.getRow();
        int col = rand() % myBoard.getCol();
        cout << "Firing missle at (" << row <<"," << col << ")" << endl;
        int delay = myBoard.fireMissle(row, col, TEAM_ID);
        myBoard.printBoard();
        pthread_mutex_unlock(&my_mutex);
        sleep(delay);
    }
    
    pthread_exit(NULL);
}
// compile - g++ main.cpp Board.cpp -pthread
int main(int argc, char * argv[]){
    // Argument Input
    // 1 -> Rows
    // 2 -> Columns
    // 3 -> TEAM_A count
    // 4 -> TEAM_B count
    srand(time(0)); // initialize random seed
    if(argc == 5){
        
        if((atoi(argv[4]) + atoi(argv[3])) > (atoi(argv[1]) * atoi(argv[2]))){
            cout << "Too Many Players, please decrease team size" << endl;
            return 0;
        }
        totalPlayers = (atoi(argv[4]) + atoi(argv[3]));
        myBoard = Board(atoi(argv[1]), atoi(argv[2]));

        cout << "Default Board: "<< totalPlayers << endl;
        myBoard.printBoard();
        //myBoard.fireMissle(0, 2, 1);
        
        pthread_t pid;
        pthread_create(&pid, NULL, &CheckForWinner, NULL);

        
        
        // create threads for TEAM A and TEAM B
        for(int i = 0; i < atoi(argv[4]); i++){
            pthread_t pid;
            pthread_create(&pid, NULL, &player, (void*)TEAM_A);
        }
        for(int i = 0; i < atoi(argv[3]); i++){
            pthread_t pid;
            pthread_create(&pid, NULL, &player, (void*)TEAM_B);
        }
        
        
    }
    pthread_exit(NULL); // wait for threads to finish

    int Winner = myBoard.Winner();
    if(Winner == 0){
        // team A
        cout << "Team A Won" << endl;
    }else if (Winner == 1){
        // team B
        cout << "Team B Won" << endl;
    }else{
        // draw
        cout << "Draw" << endl;
    }
    return 0;
}