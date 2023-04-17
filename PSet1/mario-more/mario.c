#include <cs50.h>
#include <stdio.h>

// function prototype
int get_height();
void print_map(int height);

int main(void)
{
    // get height
    int height;
    height = get_height();

    // print map
    print_map(height);
}

// get height
int get_height()
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

// print the map
void print_map(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // print the left part
        for (int j = 1; j <= height; j++)
        {
            if (j <= height - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // print two whitespaces
        printf("  ");

        // print the right part
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}