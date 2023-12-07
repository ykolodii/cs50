#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if the argument contains only digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert command-line argument to int
    int key = atoi(argv[1]);

    // Get plaintext
    string plaintext = get_string("plaintext: ");

    // Print ciphertext
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char encrypted_char = rotate(plaintext[i], key);
        printf("%c", encrypted_char);
    }

    // Print a newline
    printf("\n");

    return 0;
}

// Check if all chars in the string are digits
bool only_digits(string s)
{
    // Iterate through each char in the string
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Rotate the char by specified key
char rotate(char c, int key)
{
    // Check if the char is an alphabetical character
    if (isalpha(c))
    {
        // Determine the offset based on whether the char is lowercase or uppercase
        char offset = islower(c) ? 'a' : 'A';

        // And then rotate this char by the key, ensuring it wraps around within the alphabet
        return (c - offset + key) % 26 + offset;
    }

    // If the char is not alphabetical, return it unchanged
    return c;
}
