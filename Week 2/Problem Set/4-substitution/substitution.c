#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_valid_key(string key);
string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get the key from the command-line argument
    string key = argv[1];

    // Check if the key is valid
    if (!is_valid_key(key))
    {
        printf("Key is invalid.\n");
        return 1;
    }

    // Get plaintext
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext and print the ciphertext
    string ciphertext = encrypt(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Check if the key is valid
bool is_valid_key(string key)
{
    int key_length = strlen(key);

    // Check if the key has exactly 26 characters
    if (key_length != 26)
    {
        return false;
    }

    // Create an array to keep track of the occurrence of each letter
    int occurrences[26] = {0};

    // Iterate through each character in the key
    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        char c = toupper(key[i]);

        // Check if the letter has already occurred
        if (occurrences[c - 'A'] > 0)
        {
            return false;
        }

        // Mark the letter as occurred
        occurrences[c - 'A']++;
    }

    return true;
}

// Encrypt plaintext using the substitution cipher
string encrypt(string plaintext, string key)
{
    int plaintext_length = strlen(plaintext);
    for (int i = 0; i < plaintext_length; i++)
    {
        // Check if the character is an alphabetic character
        if (isalpha(plaintext[i]))
        {
            // Determine the case of the character
            char offset = islower(plaintext[i]) ? 'a' : 'A';

            // Find the index of the character in the key
            int index = toupper(plaintext[i]) - 'A';

            // Substitute the character using the key and preserve case
            plaintext[i] = islower(plaintext[i]) ? tolower(key[index]) : toupper(key[index]);
        }
    }

    return plaintext;
}
