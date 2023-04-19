#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// function prototype
bool only_digits(string s);
void print_error();
bool only_digits(string key);
string caesar_encryption(string plaintext, int key);

int main(int argc, string argv[])
{
    // check if the number of command-line arguments
    if (argc == 2)
    {
        // key is valid
        if (only_digits(argv[1]))
        {
            // convert command-line argument to key
            int key = atoi(argv[1]) % 26;

            // get plaintext and encrypt it
            string plaintext = get_string("plaintext: ");
            string ciphertext = caesar_encryption(plaintext, key);

            // print ciphertext
            printf("ciphertext: %s\n", ciphertext);
        }
        else
        {
            // print error message when argc is not 1
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        // print error message when argc is not 1
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

// check if key is an integer
bool only_digits(string key)
{
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

// caesar encryption
string caesar_encryption(string plaintext, int key)
{
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++)
    {
        // shift only when c is alphabetical character
        char c = plaintext[i];
        if (c >= 'a' && c <= 'z')
        {
            plaintext[i] = ((c - 'a' + key) % 26 + 'a');
        }
        else if (c >= 'A' && c <= 'Z')
        {
            plaintext[i] = ((c - 'A' + key) % 26 + 'A');
        }
    }
    return plaintext;
}
