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

int* charArrayToInt( char* charArray, int arraySize ){
    int* intArray = (int*) malloc( sizeof(int) * arraySize);
    for(int index = 0; index < arraySize; index++){
        *(intArray + index) = charToInt( *(charArray + index) );
    }
    return intArray;
}

char* getArrayFromFile( char* filename, int* width, int* height ){
    *width = 0;
    *height = 0;

    int sizeAlloc = 20;
    char* fileContent = (char*) malloc( sizeof(char) * sizeAlloc );
    FILE* fp = fopen(filename, "r");
    
    char readChar = fgetc( fp );
    int index = 0;
    while( !feof( fp ) ){
        if( readChar != '\n' ){
            if(index % sizeAlloc == 0 && index > 0)
                fileContent = realloc(fileContent, sizeAlloc + (sizeAlloc * (index/sizeAlloc)) );
            
            *(fileContent + index) = readChar;
            index++;
        }else{ // if is a break of line
            if(*height == 0){ // if is the first line
                *width = index; // use the index to get the width
                *height += 1;
            }
        }
        readChar = fgetc( fp );
    }
    *height = index / (*width);

    // reallocate the decrease the extra memory allocated
    fileContent = realloc( fileContent, index);
    return fileContent;
}
