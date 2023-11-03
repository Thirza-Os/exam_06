#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


void    print_map(char **map, int rows, int columns)
{
    char c;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            c = map[i][j];
            write(1, &c, 1);
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

int main(int argc, char**argv)
{
    if (argc != 2)
    {
        write(1, "Map Error\n", 11);
        return(1);
    }

    
    
    // Check for wrong legths 

    // count length first row:
    int fd;

    fd = open(argv[1], O_RDONLY);

    char c;
    int first_row = 0;
    while(read(fd, &c, 1) == 1)
    {
        first_row++;
        if (c == '\n')
            break;
    }
    close(fd);

    // compare to other rows:
    int fd_1;

    fd_1 = open(argv[1], O_RDONLY);

    int compare_row = 0;
    while(read(fd_1, &c, 1) == 1)
    {
        compare_row++;
        if (c != '.' && c != 'X' && c != '\n')
        {
            write(1, "Map Char Error\n", 16);
            return(1);
        }
        if (c == '\n')
        {
            if (compare_row != first_row)
            {
                write(1, "Map Error\n", 11);
                return(1);
            }
            compare_row = 0;
        }
    }
    close(fd_1);

    // Count rows/colums
    int rows = 0;
    int columns = first_row;
    int fd_2;

    fd_2 = open(argv[1], O_RDONLY);

    while(read(fd_2, &c, 1) == 1)
    {
        if (c == '\n'){
            rows++;
            }
    }
    close(fd_2);

    // check for emptyness
    if (rows == 0 || columns == 0)
    {
        write(1, "\n", 1);
        return(1);
    }
    // allocate memory
    char **map;

    map = (char**)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
        map[i] = (char*)malloc(columns * sizeof(char*));


    // Fill with map
    int fd_3;

    fd_3 = open(argv[1], O_RDONLY);
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            if (read(fd_3, &c, 1) == 1)
                map[i][j] = c;
    }



    // do floodfill and keep counter
    int count = -1;
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            if (map[i][j] == 'X'){
                count++; // Increment the count for each new island
                floodFill(map, i, j, '0' + count, rows, columns);
                }
    }

    print_map(map, rows, columns);

}