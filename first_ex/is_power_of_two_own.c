#include <unistd.h>
#include <stdio.h>

int is_power_of_two(int n)
{
    if (n == 0)
        return(0);
    while (n % 2 == 0)
        n = n / 2;
    if (n == 1)
        return (1);
    return(0);
}

int main(void)
{
    printf(": %i", is_power_of_two(40));
}