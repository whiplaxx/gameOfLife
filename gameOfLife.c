#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "tools.h"
#include "board.h"

int DEFAULT_WIDTH = 50;
int DEFAULT_HEIGHT = 20;
float DEFAULT_PERCENTAGE_ALIVE_CHANCE = 0.5;

void getArgs(int argc, char** argv, int* width, int* height, float* percentageAliveChance){
    *width = DEFAULT_WIDTH;
    *height = DEFAULT_HEIGHT;
    *percentageAliveChance = DEFAULT_PERCENTAGE_ALIVE_CHANCE;

    int c;
    while( (c = getopt(argc, argv, "w:h:c:")) != -1 ){
        switch( c ){
            case 'w':
                *width = strToInt( optarg, strlen(optarg) ); break;
            case 'h':
                *height = strToInt( optarg, strlen(optarg) ); break;
            case 'c':
                *percentageAliveChance = strToFloat( optarg, strlen(optarg) ); break;
            default: break;
        }
    }
}

int main( int argc, char* argv[] ){
    
    srand( time(NULL) );

    Board board = NULL;
    int width;
    int height;
    float percentageAliveChance;
    
    getArgs(argc, argv, &width, &height, &percentageAliveChance);
    
    char* tempCharArray = getArrayFromFile("toad.txt", &width, &height);
    board = createBoard(width, height);

    int* tempIntArray = charArrayToInt( tempCharArray, width*height );
    loadBoardFromArray( board, tempIntArray );

    free( tempCharArray );
    free( tempIntArray );
    //random_state( board, percentageAliveChance );

    char c;
    while( 1 ){
        printBoard( board );
        calculateNextBoardState( board );

        printf("\n\nPress ENTER to get next state, 'r' to reset or 'e' to exit.\n");
        printf("(select the exit option instead of closing the execution to release the allocated memory)\n");

        //sleep(1);
        c = getchar();
        if( c == 'r' || c == 'R' ){ random_state( board, percentageAliveChance ); }
        else if( c == 'e' || c == 'E' ){ break; }
    }

    freeBoard( board );
}
