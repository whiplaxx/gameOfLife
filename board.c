#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "tools.h"
#include "board.h"

float RANGE_CHANCE = 1.0;

void random_state( Board board, float percentageAliveChance ){
    for( int hIndex = 0; hIndex < board->height; hIndex++ ){
        for( int wIndex = 0; wIndex < board->width; wIndex++ ){
            int state = 0;
            float chance = (float)rand() * (RANGE_CHANCE / (float)(RAND_MAX));
            if( chance < percentageAliveChance ){
                state = 1;
                board->numOfAliveCells += 1;
            }
            *( board->matrix + (hIndex* board->width) + wIndex ) = state;
        }
    }
}

int countNeighbors( Board board, int row, int col ){

    int aliveNeighbors = 0;

    int topRowRange =       (row-1) >= 0               ? (row-1) : row;
    int bottomRowRange =    (row+1) < board->height    ? (row+1) : row;
    int leftColRange =      (col-1) >= 0               ? (col-1) : col;
    int rightColRange =     (col+1) < board->width     ? (col+1) : col;    

    for( int r = topRowRange; r <= bottomRowRange; r++ ){
        for( int c = leftColRange; c <= rightColRange; c++ ){
            if( r != row || c != col ) // is not the cell being verified
                aliveNeighbors += *(board->matrix + (r*board->width) + c);
        }
    }
    return aliveNeighbors;
}

void printBoard( Board board, int width, int height ){
    for( int hIndex = 0; hIndex < height; hIndex++ ){
        for( int wIndex = 0; wIndex < width; wIndex++ ){
            char cell;
            switch( *(board->matrix + (hIndex* board->width) + wIndex) ){
                case 1: cell = '#'; break;
                case 0: cell = ' '; break;
            }
            printf("%c", cell);
        } printf("\n");
    }
}

Board createBoard(int width, int height){
    Board board = (Board) malloc( sizeof(struct boardStruct) );
    board->width = width;
    board->height = height;
    board->numOfAliveCells = 0;

    board->matrix = (int*) malloc( width*height*sizeof(int) );
    return board;
}
