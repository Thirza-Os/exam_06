#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
{       printf(" ");
        exit(1);}

    int input = atoi(argv[1]);
    if (input == 1){
        printf("1");
        exit(1);
        }

    int divider = 2;
    while (input > 1)
    {
        if (input % divider == 0)
        {
            printf("%i", divider);
            input = input / divider;
            if (input > 1){
                printf("*");
                divider--;
            }
        }
        divider++;
    }
    printf("\n");
}