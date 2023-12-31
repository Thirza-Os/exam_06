#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void printMap(char **map, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", map[i][j]);
        }
    }
}


int floodFill(char **map, int row, int column, char mark, int rows, int columns) {
    if (row < 0 || row >= rows || column < 0 || column >= columns || map[row][column] != 'X')
        return 0;

    map[row][column] = mark;

    int size = 1;

    // Recursively call floodFill in all four directions
    size += floodFill(map, row - 1, column, mark, rows, columns);
    size += floodFill(map, row + 1, column, mark, rows, columns);
    size += floodFill(map, row, column - 1, mark, rows, columns);
    size += floodFill(map, row, column + 1, mark, rows, columns);

    return size;
}

int main(int argc, char *argv[]) {
    char visited = 'v';
    int largestIsland = 0;
    int currentSize;
    int fd;

    int rows = 1;
    int columns = 0;
    char curr;

    int row = 0;
    int column = 0;

    if (argc != 2) {
        write(1, "nope", 4);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(1, "nope", 4);
        exit(1);
    }

    while(read(fd, &curr, 1) == 1){
        if(curr == '\n'){
            rows++;
            columns = 0;
            }
        columns++;
    }
    close(fd);

    char **map = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
        map[i] = (char*)malloc(columns * sizeof(char));

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(1, "nope", 4);
        exit(1);
    }

    // Second pass: Read data into the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (read(fd, &curr, 1) == 1) {
                map[i][j] = curr;
            }
        }
    }
    printMap(map, rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (map[i][j] == 'X') {
                currentSize = floodFill(map, i, j, visited, rows, columns);
                if (currentSize > largestIsland)
                    largestIsland = currentSize;
            }
        }
    }



    printf("Size of the largest island: %i\n", largestIsland);
    close(fd);

    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
