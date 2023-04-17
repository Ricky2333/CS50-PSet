#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get user name
    string name = get_string("What's your name? ");
    // print the result
    printf("hello, %s\n", name);
}