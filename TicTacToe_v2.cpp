//
//  main.cpp
//  Tic Tac Toe v2
//
//  Created by Lennart Buhl on 10/17/21.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Obj {
    
    char symbol;
    
    Obj(char sym) {
        symbol = sym;
    }
    
    Obj() {
        symbol = '_';
    }
    
};


Obj board[9];

static int calculations = 0;

void initilizeB() {
    for (int x = 0; x < 9; x++) {
        board[x] = Obj();
    }
    calculations = 0;
}




bool howManySqrs(Obj board[9]) {
    
    for (int x = 0; x < 9; x++) {
        if (board[x].symbol == '_') {
            return true;
        }
    }
    return false;
}


int evaluateBoard(Obj board[9]) {
    
    for (int x = 0; x < 3; x++) {
        
        if (board[3*x].symbol == board[3*x+1].symbol && board[3*x+1].symbol == board[3*x+2].symbol) {
            if (board[3*x].symbol == 'X' || board[3*x].symbol == 'O') {
                return board[3*x].symbol == 'X' ? 100:-100;
            }
        }
        if (board[x].symbol == board[x+3].symbol && board[x+3].symbol == board[x+6].symbol) {
            if (board[x].symbol == 'X' || board[x].symbol == 'O') {
                return board[3*x].symbol == 'X' ? 100:-100;
            }
        }
    }
    
    if (board[0].symbol == board[4].symbol && board[4].symbol == board[8].symbol) {
        if (board[0].symbol == 'X' || board[0].symbol == 'O') {
            return board[0].symbol == 'X' ? 100:-100;
        }
    }
    if (board[2].symbol == board[4].symbol && board[4].symbol == board[6].symbol) {
        if (board[2].symbol == 'X' || board[2].symbol == 'O') {
            return board[2].symbol == 'X' ? 100:-100;
        }
    }
    
    return 0;
}

void printBoard(Obj board[9]) {
    
    for (int x = 0; x < 3; x++) {
        cout << "| " << board[3*x].symbol << " | " << board[3*x+1].symbol << " | " << board[3*x+2].symbol << " |\n";
    }
    cout << endl;
    
}

int AB_Prune(Obj board[9], int alpha, int beta, bool isMax, int depth) {
    
    calculations++;
    ++depth;
    
    int score = evaluateBoard(board);
    
    if (score != 0) {
        return score-depth;
    } else {
        if (!howManySqrs(board)) {
            return 0;
        }
    }
    
    if (isMax) {
        
        for (int x = 0; x < 9; x++) {
            if (board[x].symbol == '_') {
                
                board[x] = Obj('X');
                
                alpha = max(alpha, AB_Prune(board, alpha, beta, !isMax, depth));
                
                board[x] = Obj();
                
                if (alpha >= beta) {
                    return alpha;
                }
            }
            
        }
        return alpha;
    } else {
        
        for (int x = 0; x < 9; x++) {
            if (board[x].symbol == '_') {
                
                board[x] = Obj('O');
                
                beta = min(beta, AB_Prune(board, alpha, beta, !isMax, depth));
                
                board[x] = Obj();
                
                if (alpha >= beta) {
                    return beta;
                }
            }
        }
        
        return beta;
        
    }
    
}


void AB_Prune_Root() {
    
    int bestVal = -100000;
    int bestMove = -1;
    calculations = 0;
    
    for (int x = 0; x < 9; x++) {
        
        if (board[x].symbol == '_') {
            
            board[x] = Obj('X');
            
            int moveVal = AB_Prune(board, -100000, 100000, false, 0);
            
            board[x] = Obj();
            
            if (moveVal > bestVal) {
                bestMove = x;
                bestVal = moveVal;
            }
        }
    }
    board[bestMove] = 'X';
    return;
}

void playerMove() {
    
    int a;
    cout << "Give a square from 1-9: ";
    cin >> a;
    cout << endl;
    
    if (board[a-1].symbol == '_') {
        board[a-1] = 'O';
    } else {
        cout << "Wrong Input!";
        if (howManySqrs(board)) {
            playerMove();
        }
    }
}


void getWinner(Obj board[9]) {
    if (evaluateBoard(board) == 100) {
        cout << "\nX Won This One!\n";
    } else if (evaluateBoard(board) == -100) {
        cout << "\nO Won This One!\n";
    } else {
        cout << "\nIt Was A Draw!\n";
    }
}

void gameTic() {
    while (true) {
        if (evaluateBoard(board) == 0 && howManySqrs(board)) {
            AB_Prune_Root();
            printBoard(board);
            cout << "Evaluated this many Boards: " << calculations << endl;
        } else {
            getWinner(board);
            break;
        }
        if (evaluateBoard(board) == 0 && howManySqrs(board)) {
            playerMove();
            printBoard(board);
        } else {
            getWinner(board);
            break;
        }
    }
    char a;
    cout << "\033[35m";
    cout << "Do you want to play again? (y/n) ";
    cin >> a;
    
    if (a == 'y') {
        cout << "\033[0m";
        cout << endl;
        initilizeB();
        gameTic();
    } else {
        return;
    }
}

int main() {
    
    
    gameTic();
    
    return 0;
}
