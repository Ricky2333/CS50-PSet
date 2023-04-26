#include "helpers.h"
#include <math.h>

// function prototype
int min(int a, int b);
int max(int a, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = (BYTE)avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;
            // sepia formula
            image[i][j].rgbtRed = min(255, (int)round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            image[i][j].rgbtGreen = min(255, (int)round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            image[i][j].rgbtBlue = min(255, (int)round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap pixels in each row
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // modify each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // ensure the 3*3 blur box is inside the image
            // the index of center element is (i,j)
            // the index of top left corner element is (i-1,j-1)
            // the index of bottom right corner element is (i+1,j+1)
            int start_row = max(0, i - 1);
            int end_row = min(height - 1, i + 1);
            int start_col = max(0, j - 1);
            int end_col = min(width - 1, j + 1);

            // calculate the sum of blur box
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int cnt = 0;
            for (int r = start_row; r <= end_row; r++)
            {
                for (int c = start_col; c <= end_col; c++)
                {
                    sumRed += copy[r][c].rgbtRed;
                    sumBlue += copy[r][c].rgbtBlue;
                    sumGreen += copy[r][c].rgbtGreen;
                    cnt++;
                }
            }
            // calculate the avg of blur box and assign it
            image[i][j].rgbtRed = round(1.0 * sumRed / cnt);
            image[i][j].rgbtBlue = round(1.0 * sumBlue / cnt);
            image[i][j].rgbtGreen = round(1.0 * sumGreen / cnt);
        }
    }
    return;
}

// return the min value of a and b
int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


// return the max value of a and b
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}