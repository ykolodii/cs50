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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate sepia values
            /*
            Algorythm which is taken from task spec:
                sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
                sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
                sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            */
            int sepiaRed = clamp((int) round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            int sepiaGreen = clamp((int) round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            int sepiaBlue = clamp((int) round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            float count = 0;

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
