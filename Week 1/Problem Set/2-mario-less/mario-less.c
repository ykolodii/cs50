#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_grid(int size);

int main(void)
{
    // Get size of grid
    int num = get_size();

    // Print grid of bricks
    print_grid(num);
}

int get_size(void)
{
    int num;
    do
    {
        printf("Height: ");
        scanf("%d", &num);
    }
    while (num < 1 || num > 8);
    return num;
}

void print_grid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // Print spaces
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }

        // Print '#' symbols
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Move to the next line after each row
        printf("\n");
    }
}
