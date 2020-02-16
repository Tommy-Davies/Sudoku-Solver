//
//  main.cpp
//  Sudoku
//
//  Created by Tommy Davies on 2020-02-15.
//  Copyright © 2020 Tommy Davies. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
bool findEmpty(int board[9][9], int &row, int &col);
bool isValid(int board[9][9], int row, int col, int num);
void printBoard(int board [9][9]){
    for(int i = 0; i < 9; i++){
        
        if(i % 3 == 0 && i != 0){
            for(int j = 0; j < 29; j++){
                printf("_");
            }
        }
        printf("\n");
        for(int j = 0; j < 9; j++){
            
            if(j % 3 == 0 && j != 0){
                printf("|");
            }
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}


struct solveState{
    bool solved;
    int row;
    int col;
};
struct isEmpty{
    bool state;
    int row;
    int col;
};
struct solveState findEmpty(int board[9][9]){
    struct solveState x;
    for( x.row = 0; x.row < 9; x.row++){
        
        for(x.col = 0; x.col < 9; x.col++){
            //            printf("\n%d %d", row, col);
            
            if(board[x.row][x.col] == 0){
                x.solved = false;
                return x;
            }
        }
    }
    
    x.solved = true;
    return x;
}
bool solved(int board[9][9]){
    struct solveState x;
    
    x = findEmpty(board);
    
    if (x.solved){
        //        printf("solved");
        return true;
    }
    
    for(int num = 1; num <= 9; num++){
        if(isValid(board, x.row, x.col, num)){
            board[x.row][x.col] = num;
            if(solved(board)){
                return true;
            }
            board[x.row][x.col] = 0;
            
        }
    }
    
    return false;
}

bool existsInRow(int x, int row, int board[9][9]){
    
    for(int i = 0; i < 9; i++){
        if(board[row][i] == x){
            
            return true;
        }
    }
    return false;
}
bool existsInCol(int x, int col, int board[9][9]){
    for(int i = 0; i < 9; i++){
        if(board[i][col] == x){
            return true;
        }
    }
    return false;
}
bool existsInBox(int x, int boxRow, int boxCol, int board[9][9]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i+boxRow][j+boxCol] == x){
                return true;
            }
        }
    }
    return false;
}
bool isValid(int board[9][9], int row, int col, int num){
    if(!existsInRow(num, row, board) && !existsInCol(num, col, board) && !existsInBox(num, row - row % 3, col - col % 3, board)){
        return true;
    }
    return false;
}
struct isEmpty findEmptyBox(int board[9][9]){
    struct isEmpty x;
    bool empty = true;
    for(x.row = 0; x.row < 3; x.row++){
        for(x.col = 0; x.col < 3; x.col++){
            empty = true;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(board[x.row * 3 + i][x.col * 3 + j] != 0){
                        empty = false;
                    }
                }
            }
            if(empty == true){
                x.state = true;
                
                //                   printf("%d %d", x.row, x.col);
                return x;
            }
        }
        
    }
    x.state = false;
    return x;
}
void clearBox(int board[9][9], struct isEmpty x){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[x.row * 3 + i][x.col * 3 + j] = 0;
        }
    }
}
bool insertBox(int board[9][9]){
    //    int filledBoxCount = 0;
    bool safe = false;
    int rowIndex[4];
    int colIndex[4];
    int boxVal;
    struct isEmpty x;
    x = findEmptyBox(board);
    if(!x.state){
        return true;
    }
    for(int i = 0; i < 4; i++){
        rowIndex[i] = rand() % 3;
    }
    for(int i = 0; i < 4; i++){
        colIndex[i] = rand() % 3;
        //        printf("%d %d\n", rowIndex[i], colIndex[i]);
    }
    while(safe == false){
        boxVal = rand() % 9 + 1;
        
        if(isValid(board, x.row * 3 +rowIndex[2], x.col * 3 + colIndex[1], boxVal)){
            board[x.row * 3 + rowIndex[2]][x.col * 3 + colIndex[1]] = boxVal;
            if(insertBox(board)){
                return true;
            }
            clearBox(board, x);
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    //    struct isEmpty x;
    int board[9][9] = {0};
    //    int currentBox [2] = {0, 1};
    //    int boardStart;
    srand (static_cast<unsigned int>(time(NULL)));
    //    boardStart = rand() % 9 + 1;
    //    board [1][1] = boardStart;
    
    
    //    printBoard(board);
    //    x = findEmptyBox(board);
    //    printf("%d, %d | %d\n", x.row, x.col, x.state);
    
    insertBox(board);
    printf("Puzzle:\n");
    printBoard(board);
    
    if(solved(board)){
        printf("\nPuzzle Solution:\n");
        printBoard(board);
        printf("\n");
    } else {
        printf("no solution for this puzzle exists\n");
        return 1;
    }
    
    // insert code here...
    return 0;
}
