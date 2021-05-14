#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "tools.h"

int DEFAULT_WIDTH = 50;
int DEFAULT_HEIGHT = 20;
float RANGE_CHANCE = 1.0;
float DEFAULT_PERCENTAGE_ALIVE_CHANCE = 0.5;

void random_state( int* board, int width, int height, float percentageAliveChance ){
    for( int hIndex = 0; hIndex < height; hIndex++ ){
        for( int wIndex = 0; wIndex < width; wIndex++ ){
            int state = 0;
            float chance = (float)rand() * (RANGE_CHANCE / (float)(RAND_MAX));
            if( chance < percentageAliveChance ){
                state = 1;
            }
            *( board + (hIndex*height) + wIndex ) = state;
        }
    }
}

void printBoard( int* board, int width, int height ){
    for( int hIndex = 0; hIndex < height; hIndex++ ){
        for( int wIndex = 0; wIndex < width; wIndex++ ){
            char cell;
            switch( *(board + wIndex + (hIndex*height)) ){
                case 1: cell = '#'; break;
                case 0: cell = ' '; break;
            }
            printf("%c", cell);
        }
        printf("\n");
    }
}

void getArgs(int argc, char** argv, int* width, int* height, float* percentageAliveChance)
{
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
    
    int* board = (int*) malloc( width*height * sizeof(int));
    random_state( board, width, height, percentageAliveChance );
    printBoard( board, width, height );
    free( board );
}
