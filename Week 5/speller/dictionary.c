// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    // Cursor points to the head of the hash table
    node *cursor = table[index];

    // Go through the list until the final node is reached
    for (node *temp = cursor; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Get the lengh of the string and sum the value of the characters
    unsigned int hashvalue = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }
    return hashvalue;
}

// Nodes counter
int counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file with read permission
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open dictionary");
        return false;
    }

    char words_arr[LENGTH + 1];

    while (fscanf(file, "%s", words_arr) != EOF)
    {
        // Keep track of how many nodes are being made
        counter++;

        // Allocate memory for each new node
        node *newNode = malloc(sizeof(node));

        if (newNode == NULL)
        {
            return 1;
        }

        // Initialize the new node by copying the word to the next node
        strcpy(newNode->word, words_arr);
        newNode->next = NULL;

        int index = hash(words_arr);

        // If the index is not yet assigned, put the newest node at the head of this index
        if (table[index] == NULL)
        {
            table[index] = newNode;
        }

        // If the index is assigned point the existing head node at the table[index] and then make the new node the head
        else
        {
            // Makes the next the new head
            newNode->next = table[index];

            // Head points to the new node
            table[index] = newNode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /*
      Create a temporary node to keep track of the current node
      Create a cursor that points to the head node. This cursor will iterate through the linked lists, setting each node's next
      pointer to NULL and freeing the memory
    */
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
