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
    int width, height;
    float percentageAliveChance;
    getArgs(argc, argv, &width, &height, &percentageAliveChance);

    Board board = createBoard(width, height);
    random_state( board, percentageAliveChance );
    printBoard( board, width, height );

    free( board );
}
