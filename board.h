struct boardStruct {
    int width, height;
    int numOfAliveCells;

    int* matrix;
};

typedef struct boardStruct* Board;

Board createBoard(int width, int height);
void freeBoard( Board board );
void printBoard( Board board );
void random_state( Board board, float percentageAliveChance );
void calculateNextBoardState( Board board );
void loadBoardFromArray( Board board, int* array );
