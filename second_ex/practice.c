#include <stdio.h>

int    floodFill(char map[4][5], int row, int column, char mark)
{
    if (row < 0 || row >= 4 || column < 0 || column >= 5 || map[row][column] != 'X')
        return(0);

    map[row][column] = mark;

    int size = 1;

    size += floodFill(map, row - 1, column, mark);
    size += floodFill(map, row + 1, column, mark);
    size += floodFill(map, row, column - 1, mark);
    size += floodFill(map, row, column + 1, mark);

    return(size);
}

int main(void) {
    char grid[4][5] = {
        {'.', 'X', '.', '.', 'X'},
        {'.', 'X', 'X', 'X', 'X'},
        {'.', '.', '.', 'X', '.'},
        {'X', 'X', '.', '.', '.'},
    };

    char visited = 'v';
    int largestIsland = 0;
    int currentSize;

    int i = 0;
    int j = 0;
    while(i < 4)
    {
        j = 0;
        while (j < 5)
        {
            if(grid[i][j] == 'X'){                
                currentSize = floodFill(grid, i, j, visited);
                if (currentSize > largestIsland)
                    largestIsland = currentSize;}
            j++;
        }
        i++;
    }
    printf("Size of the largest island: %i\n", largestIsland);
    return(0);
}
