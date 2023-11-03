#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void printMap(char **map, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            char c = map[i][j];
            write(1, &c, 1); // Use write to output a single character
        }
        write(1, "\n", 1); // Add a newline at the end of each row
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
    int islandsCount = -1; // Initialize the count of islands
    int fd;

    int rows = 1;
    int columns = 0;
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
        if (curr == '\n') {
            rows++;
            columns = 0;
        }
        columns++;
    }

    close(fd);

    char **map = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
        map[i] = (char *)malloc(columns * sizeof(char));

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(1, "Error opening file 2\n", 21);
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

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (map[i][j] == 'X') {
                islandsCount++; // Increment the count for each new island
                floodFill(map, i, j, '0' + islandsCount, rows, columns);
            }
        }
    }

    // Output the modified map with counts
    printMap(map, rows, columns);

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
