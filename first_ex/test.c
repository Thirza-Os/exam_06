#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int nr = atoi(argv[1]);
    int count = 2;

    while(nr > 1)
    {
        if (nr % count == 0)
        {
            nr = nr / count;
            printf("%i", count);
            count--;
            if(nr > 1)
            {
                printf("*");
            }
        }
        count++;
    }

}