#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_to_binary(string text);

int main(void)
{
    // Get input text from the user
    string text = get_string("Enter a message: ");

    // Convert text to binary and print bulbs
    convert_to_binary(text);

    return 0;
}

void convert_to_binary(string text)
{
    // Loop through each character in the input text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Get the ASCII value of the character
        int ascii_value = (int) text[i];

        // Convert ASCII value to binary representation
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = (ascii_value >> j) & 1; // Extract each bit
            print_bulb(bit);                  // Print the bulb representation
        }

        // Print a newline character after each set of 8 bits
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
