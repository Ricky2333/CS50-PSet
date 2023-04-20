#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// function prototype
bool check(string key);
string substitution_encryption(string plaintext, string key);

int main(int argc, string argv[])
{
    // check the number of command-line arguments
    if (argc == 2)
    {
        // check if key is valid
        if (check(argv[1]))
        {
            // get key
            string key = argv[1];

            // get plaintext and do substitution
            string plaintext = get_string("plaintext:  ");
            string ciphertext = substitution_encryption(plaintext, key);

            // print the ciphertext
            printf("ciphertext: %s\n", ciphertext);
        }
        else
        {
            // print error message
            printf("Key must contain 26 characters and no repetition.\n");
            return 1;
        }
    }
    else
    {
        // print error message
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

// check if key is valid
bool check(string key)
{
    int len = strlen(key);
    // check the length of key
    if (len != 26)
    {
        return false;
    }
    else
    {
        // check if key is composed of 26 alphabetic charaters
        int letters[26] = {0};
        for (int i = 0; i < len; i++)
        {
            char c = key[i];
            if (c >= 'a' && c <= 'z')
            {
                letters[c - 'a'] ++;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                letters[c - 'A'] ++;
            }
            else
            {
                return false;
            }
        }
        // after iteration, each element in letters should be 1
        for (int i = 0; i < 26; i++)
        {
            if (letters[i] != 1)
            {
                return false;
            }
        }
        return true;
    }
}

// get plaintext and do substitution
string substitution_encryption(string plaintext, string key)
{
    // get the length of plaintext
    int len = strlen(plaintext);

    // substitute plaintext
    for (int i = 0; i < len; i++)
    {
        char c = plaintext[i];
        if (c >= 'a' && c <= 'z')
        {
            plaintext[i] = tolower(key[c - 'a']);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            plaintext[i] = toupper(key[c - 'A']);
        }
    }
    return plaintext;
}