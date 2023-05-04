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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 45 * 26;

// Hash table
node *table[N];
// int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // get the hash code of this word
    unsigned int index = hash(word);

    // check if this word is in table[index]
    node *head = table[index];
    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // hash based on word length and the first character
    return (strlen(word) - 1) * 26 + toupper(word[0]) - 'A';

    // based on the first two characters
    // if (strlen(word) == 3)
    // {
    //     return (toupper(word[0]) - 'A') * 26 + toupper(word[1]) - 'A';
    // }
    // else
    // {
    //     return (toupper(word[0]) - 'A') * 26;
    // }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    // iterate this dictionary
    char word[LENGTH + 1];
    while (fscanf(fp, "%s", word) != EOF)
    {
        // create a node to store this word
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            unload();
            fclose(fp);
            return false;
        }
        strcpy(new->word, word);

        // hash this word
        unsigned int index = hash(new->word);

        // insert it into hash table
        new->next = table[index];
        table[index] = new;

        // code below is incorrect to insert a node into a hash table, why?
        // node *head = table[index];
        // new->next = head;
        // head = new;
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // set a counter
    unsigned int cnt = 0;

    // iterate hash table
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        while (head != NULL)
        {
            cnt++;
            head = head->next;
        }
    }
    return cnt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate hash table
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        while (head != NULL)
        {
            node *tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    return true;
}
