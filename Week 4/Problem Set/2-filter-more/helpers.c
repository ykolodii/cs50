#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Helper function to clamp values between 0 and 255
int clamp(int value)
{
    return value < 0 ? 0 : value > 255 ? 255 : value;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average as a floating-point number
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Round the average and convert it to an integer
            int roundedAverage = (int) round(average);

            // Update pixel with grayscale values
            image[i][j].rgbtRed = roundedAverage;
            image[i][j].rgbtGreen = roundedAverage;
            image[i][j].rgbtBlue = roundedAverage;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels horizontally
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Compute blurred values for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Iterate over neighboring pixels
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newI = i + k;
                    int newJ = j + l;

                    // Check if the neighboring pixel is within bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        totalRed += image[newI][newJ].rgbtRed;
                        totalGreen += image[newI][newJ].rgbtGreen;
                        totalBlue += image[newI][newJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate average values
            temp[i][j].rgbtRed = (int) round(totalRed / count);
            temp[i][j].rgbtGreen = (int) round(totalGreen / count);
            temp[i][j].rgbtBlue = (int) round(totalBlue / count);
        }
    }

    // Copy blurred values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define Sobel operator kernels
    int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0, GyRed = 0, GxGreen = 0, GyGreen = 0, GxBlue = 0, GyBlue = 0;

            // Iterate over the 3x3 neighborhood
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newI = i + k;
                    int newJ = j + l;

                    // Check if the neighboring pixel is within bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        GxRed += kernelX[k + 1][l + 1] * image[newI][newJ].rgbtRed;
                        GyRed += kernelY[k + 1][l + 1] * image[newI][newJ].rgbtRed;
                        GxGreen += kernelX[k + 1][l + 1] * image[newI][newJ].rgbtGreen;
                        GyGreen += kernelY[k + 1][l + 1] * image[newI][newJ].rgbtGreen;
                        GxBlue += kernelX[k + 1][l + 1] * image[newI][newJ].rgbtBlue;
                        GyBlue += kernelY[k + 1][l + 1] * image[newI][newJ].rgbtBlue;
                    }
                }
            }

            // Calculate the magnitude of the gradient
            int magnitudeRed = (int) round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int magnitudeGreen = (int) round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int magnitudeBlue = (int) round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            // Ensure that the magnitude values are within the valid range [0, 255]
            temp[i][j].rgbtRed = clamp(magnitudeRed);
            temp[i][j].rgbtGreen = clamp(magnitudeGreen);
            temp[i][j].rgbtBlue = clamp(magnitudeBlue);
        }
    }

    // Copy edge-detected values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
