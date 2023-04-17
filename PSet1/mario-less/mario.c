#include <cs50.h>
#include <stdio.h>

// function prototype
int get_size();
void print_pyramid(int size);

int main(void)
{
    // get the size of pyramid
    int size;
    size = get_size();

    // print the pyramid
    print_pyramid(size);
}

// get user input
int get_size()
{
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    return size;
}

// print the pyramid
void print_pyramid(int size)
{
    for (int i = 0; i < size; i ++)
    {
        for (int j = 0; j < size; j ++)
        {
            if (j < size - i - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}