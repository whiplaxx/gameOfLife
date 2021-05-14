struct boardStruct {
    int width, height;
    int numOfAliveCells;

    int* matrix;
};

typedef struct boardStruct* Board;

Board createBoard(int width, int height);
void printBoard( Board board, int width, int height );
void random_state( Board board, float percentageAliveChance );
int countNeighbors( Board board, int row, int col );
