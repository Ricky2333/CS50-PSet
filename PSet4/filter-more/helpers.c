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
            // calculate the average value
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
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
            // Swap pixels in the horizontal direction with their mirrored positions.
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // define 2 kernels: Gx and Gy
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // make a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // loop through all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate image[i][j]'s weightd sum
            int red_sum_x = 0, red_sum_y = 0;
            int green_sum_x = 0, green_sum_y = 0;
            int blue_sum_x = 0, blue_sum_y = 0;
            for (int row = 0; row <= 2; row++)
            {
                for (int col = 0; col <= 2; col++)
                {
                    // current weight is gx[row][col] and gy[row][col]
                    // current pixel is copy[i - 1 + row][j - 1 + col]
                    // boundary
                    if (!(i - 1 + row < 0 || i - 1 + row > height - 1 || j - 1 + col < 0 || j - 1 + col > width - 1))
                    {
                        red_sum_x += Gx[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtRed;
                        red_sum_y += Gy[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtRed;
                        green_sum_x += Gx[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtGreen;
                        green_sum_y += Gy[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtGreen;
                        blue_sum_x += Gx[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtBlue;
                        blue_sum_y += Gy[row][col] * (int)copy[i - 1 + row][j - 1 + col].rgbtBlue;
                    }
                }
            }
            // assign new value
            image[i][j].rgbtRed = min(255, (int)round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y)));
            image[i][j].rgbtGreen = min(255, (int)round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y)));
            image[i][j].rgbtBlue = min(255, (int)round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y)));
        }
    }
    return;
}

// return the smaller of two values
int min(int a, int b)
{
    return a < b ? a : b;
}

// return the larger of two values
int max(int a, int b)
{
    return a > b ? a : b;
}