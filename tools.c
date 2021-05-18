#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int charToInt( char numChar );

int randomFloat( float max ){
    float number = max * ( (float)rand() / (float)(RAND_MAX) );
    return number;
}

int strToInt( char numStr[], int numStrSize ){
    int number = 0;
    for( int index = 0; index < numStrSize; index++ ){
        number *= 10;
        int currentNum = charToInt( numStr[index] );
        if( currentNum == -1){ number /= 10; break; }
        number += currentNum;
    }
    return number;
}

float strToFloat( char numStr[], int numStrSize ){
    float number = 0, decimal = 0;
    int decMult = 0;
    for( int index = 0; index < numStrSize; index++ ){
        int currentNum = charToInt( numStr[index] );
        if( currentNum == -1 ){
            if( numStr[index] == '.' && decMult == 0 ){ decMult = 10; }
            else { break; }
        }else{
            if( decMult == 0 ){
                number *= 10;
                number += (float) currentNum;
            }else{
                decimal += ((float)currentNum / decMult);
                decMult *= 10;
            }
        }
    }
    return number+decimal;
}
int charToInt( char numChar ){
    switch( numChar ){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return -1;
    }
}
