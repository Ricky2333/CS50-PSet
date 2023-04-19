#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Each ASCII character is composed of 8 bits.
const int BITS_IN_BYTE = 8;

// function prototype
void print_bulb(int bit);
int convert_to_ascii(char c);
int *convert_to_binary(int asc);
void convert_to_bulb(int *binary);

int main(void)
{
    // get message
    string message = get_string("Message: ");

    // conversion
    int len = strlen(message);
    for (int i = 0; i < len; i++)  // convert each character
    {
        // convert current character to Ascii number
        int asc = convert_to_ascii(message[i]);

        // convert Ascii number to binary, and store the result in an arrray named "binary"
        int *binary = convert_to_binary(asc);

        // convert binary to bulb
        convert_to_bulb(binary);

        // free the current pointer
        free(binary);
    }
}

// convert a character to Ascii number
int convert_to_ascii(char c)
{
    // '\0' or NUL is the first character in Ascii Table
    return c - '\0';
}

// convert Ascii number to binary
int *convert_to_binary(int asc)
{
    // allocate memory for array
    int *binary = (int *) malloc(BITS_IN_BYTE * sizeof(int));
    // store the result in reverse order
    for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
    {
        binary[i] = asc % 2;
        asc /= 2;
    }
    return binary;
}

// print bulb
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

// convert binary to bulb
void convert_to_bulb(int *binary)
{
    // show bulb status
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        print_bulb(binary[i]);
    }
    printf("\n");
}