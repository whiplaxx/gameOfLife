#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "tools.h"
#include "board.h"

float RANGE_CHANCE = 1.0;

void insertValueInBoard( Board board, int row, int col, int value );
int getValueFromCell( Board board, int row, int col );
int getIndexFromCoord( int width, int row, int col );
int countNeighbors( Board board, int row, int col );
int calculateNextCellState( int currentState, int aliveNeighbors );

void loadBoardFromArray( Board board, int* array ){
    if( board->matrix != NULL ){
        int boardSize = board->width*board->height;
        for( int index = 0; index < boardSize; index++ ){
            *(board->matrix + index) = *(array + index);
            if( *(array + index) == 1 )
                board->numOfAliveCells += 1;
        }
    }
}

/* Create an array with random states. 
    aliveChance: percentage float (0.0 - 1.0)
*/
void random_state( Board board, float aliveChance ){
    srand( time(NULL) );

    int boardSize = board->width*board->height;
    int* boardArray = (int*) malloc( sizeof(int) * boardSize );
    for( int index = 0; index < boardSize; index++ ){
        int state = (randomFloat(RANGE_CHANCE) < aliveChance) ? 1 : 0;
        *(boardArray + index) = state;
        if(state == 1)
            board->numOfAliveCells += 1;
    }
    loadBoardFromArray( board, boardArray );
    free(boardArray);
}

void insertValueInBoard( Board board, int row, int col, int value ){
    int currentState = getValueFromCell( board, row, col );
    board->numOfAliveCells -= currentState - value;
    int index = getIndexFromCoord( board->width, row, col );
    *(board->matrix + index) = value;
}

/* Get value from the board matrix given the row and column */
int getValueFromCell( Board board, int row, int col ){
    int index = getIndexFromCoord( board->width, row, col );
    return *(board->matrix + index);
}
/* Return array index for the row and column passed */
int getIndexFromCoord( int width, int row, int col ){
    return (row*width)+col;
}

/* Iterate over the board calculating the next state of each cell */
void calculateNextBoardState( Board board ){

    int* nextBoard = (int*) malloc( sizeof(int) * board->width * board->height );
    for( int row = 0; row < board->height; row++ ){
        for( int col = 0; col < board->width; col++ ){
            int state = getValueFromCell( board, row, col );
            int numOfAliveNeighbors = countNeighbors( board, row, col );
            int newState = calculateNextCellState( state, numOfAliveNeighbors );
            *(nextBoard + getIndexFromCoord(board->width, row, col)) = newState;
        }
    }
    board->numOfAliveCells = 0;
    loadBoardFromArray( board, nextBoard );
    free( nextBoard );
}

/* Verify the next state of the cell based on the current one and the neighbors */
int calculateNextCellState( int currentState, int aliveNeighbors ){
    int state = 0;
    
    // Alive
    if( currentState == 1 ){
        if( aliveNeighbors <= 1 ){ state = 0; }
        else if( aliveNeighbors <= 3){ state = 1; }
        else{ state = 0; }
    }
    // Dead
    else{ 
        if( aliveNeighbors == 3 ){ state = 1; }
    }

    return state;
}

/* Sum the numbers from the neighbours cells */
int countNeighbors( Board board, int row, int col ){
    
    int aliveNeighbors = 0;
    
    // Range for vertical and horizontal navigation
    int topRowRange =       (row-1) >= 0               ? (row-1) : row;
    int bottomRowRange =    (row+1) < board->height    ? (row+1) : row;
    int leftColRange =      (col-1) >= 0               ? (col-1) : col;
    int rightColRange =     (col+1) < board->width     ? (col+1) : col;    
    
    // Vertical navigation
    for( int r = topRowRange; r <= bottomRowRange; r++ ){
        // Horizontal navigation
        for( int c = leftColRange; c <= rightColRange; c++ ){
            if( r != row || c != col ) // is not the cell being verified
                aliveNeighbors += *(board->matrix + (r*board->width) + c);
        }
    }

    return aliveNeighbors;
}

void printBoard( Board board ){
    printf("## BOARD ##\n");
    printf("Width: %d | Height: %d | Alive Cells: %d\n\n", board->width, board->height, board->numOfAliveCells );
    for(int index = 0; index <= board->width; index++)
        printf("_");
    printf("\n");
    for( int row = 0; row < board->height; row++ ){
        for( int col= 0; col < board->width; col++ ){
            if( col == 0 )
                printf("|");
            char cell;
            switch( getValueFromCell(board, row, col) ){
                case 1: cell = '#'; break;
                case 0: cell = ' '; break;
            }
            printf("%c", cell);
            if( col == board->width - 1)
                printf("|");
        } printf("\n");
    }
    for(int index = 0; index <= board->width; index++)
        printf("-");
    printf("\n");
}


void freeBoard( Board board ){
    free( board->matrix );
    free( board );
}

/*  */
Board createBoard(int width, int height){
    Board board = (Board) malloc( sizeof(struct boardStruct) );
    board->width = width;
    board->height = height;
    board->numOfAliveCells = 0;

    board->matrix = (int*) malloc( width*height*sizeof(int) );
    for( int index = 0; index < width*height; index++ )
        *( board->matrix + index ) = 0;
    return board;
}

