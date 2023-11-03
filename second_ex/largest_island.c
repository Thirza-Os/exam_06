#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void printMap(char **map, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int floodFill(char **map, int row, int column, char mark, int rows, int columns) {
    if (row < 0 || row >= rows || column < 0 || column >= columns || map[row][column] != '\n')
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
    int columns = 1024;
    char curr;

    if (argc != 2) {
        write(1, "Usage: program input.txt\n", 26);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(1, "Error opening file\n", 19);
        exit(1);
    }

    // First pass: Count rows and columns
    while (read(fd, &curr, 1) == 1) {
    if (read(fd, &curr, 1) == 1) {
        if (curr == '\n')
            rows++;
        }
    }
    close(fd);

    char **map = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
        map[i] = (char *)malloc(columns * sizeof(char));

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(1, "Error opening file\n", 19);
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
    close(fd);

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

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
