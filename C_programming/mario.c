#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt pyramid height
    int n;

    // Accept height between 1 and 8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // For height
    for (int i = 1; i <= n; i++)
    {
        // For columns
        int s = n - i;
        //  left space
        for (int j = 0; j < s; j++)
        {
            printf(" ");
        }
        // Left block
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Middle space
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }

        // Right block
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // Move to newline at the end of each column
        printf("\n");
    }

}