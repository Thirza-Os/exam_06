#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        write(1, "\n", 1);

    int number = atoi(argv[1]);

    int divider = 2;

    while(number > 1)
    {
        if (number % divider == 0)
        {
            number = number / divider;
            printf("%i", divider);
            divider --;
            if (number > 1)
                printf("*");
        }
        divider++;
    }
}