#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Calculate number of years until the threshold is reached
    int years = 0;
    while (start < end)
    {
        int new_population = start + (start / 3) - (start / 4);
        start = new_population;
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}
