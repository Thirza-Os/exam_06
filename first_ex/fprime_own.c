#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
{       printf(" \n");
        exit(1);}

    int number = atoi(argv[1]);
    if (number == 1){
        printf("%i\n", number);
        exit(1);
    }

    int divider = 2;
    while (number > 1)
    {
        if (number % divider == 0)
        {
            printf("%i", divider);
            number = number / divider;
            if (number > 1){
                printf("*");
                divider--;
            }
        }
        divider++;
    }
    printf("\n");
}