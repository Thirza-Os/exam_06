#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

void print_map(char **map, int rows, int columns)
{
    char c;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            c = map[i][j];
            write(1, &c, 1);
        }
}

int fload_fill(char **map, int row, int column, int rows, int columns, char c)
{
    if (row < 0 || row >= rows || column < 0 || column >= columns || map[row][column] != 'X')
        return 0;

    map[row][column] = c;

    int count = 1;

    count += fload_fill(map, row - 1, column, rows, columns, c);
    count += fload_fill(map, row + 1, column, rows, columns, c);
    count += fload_fill(map, row, column - 1, rows, columns, c);
    count += fload_fill(map, row, column + 1, rows, columns, c);

    return(count);
}

int main(int argc, char**argv)
{
    int rows = 1;
    int columns = 0;

    if (argc != 2)
        write(1, "\n", 1);

    int fd;
    char c;
    fd = open(argv[1], O_RDONLY);
    while (read(fd, &c, 1) == 1)
    {
        if (c == '\n'){
            rows++;
            columns = 0;
            }
            columns++;
    }
    close(fd);



    char **map;
    map = (char**)malloc(rows * sizeof(char*));
    for(int i = 0; i < rows; i++)
        map[i] = (char*)malloc(columns * sizeof(char));

    fd = open(argv[1], O_RDONLY);
    for (int i =0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(read(fd, &c, 1) == 1)
                map[i][j] = c;
    close(fd);

    int islands = -1;

   for (int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++)
            if (map[i][j] == 'X'){
                islands++;
                fload_fill(map, i, j, rows, columns, '0' + islands);
        }
    }
print_map(map, rows, columns);
}