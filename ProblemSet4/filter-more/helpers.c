#include "helpers.h"
#include <math.h>

int get_color_avg(BYTE values[], int neighbors);
float get_gx(BYTE values[], int neighbors);
float get_gy(BYTE values[], int neighbors);
int check_bounds(int sobel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through rows of pixels.
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols of pixels.
        for (int j = 0; j < width; j++)
        {
            // RGB is backward here due to proper BMP data.
            float blue = image[i][j].rgbtBlue;   // grab blue value.
            float green = image[i][j].rgbtGreen; // grab green value.
            float red = image[i][j].rgbtRed;     // grab red value.

            // Round up the average to make it an int.
            int avg = round(((blue + green + red) / 3));

            // setting pixel RGB's to the average for grayscale.
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through rows of pixels
    for (int i = 0; i < height; i++)
    {
        int half = (width / 2);

        // Go to half the width of image so you don't flip the pixels back to their original place.
        for (int j = 0; j < half; j++)
        {
            // Swapping pixels RGB values from n-1 to 0.
            RGBTRIPLE temp = image[i][j];          // Store RGBTRIPLE value.
            image[i][j] = image[i][width - 1 - j]; // Swap First with last.
            image[i][width - 1 - j] = temp;        // Swap last with temp.
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Make copy of image to save original values.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols of pixels.
        for (int j = 0; j < width; j++)
        {
            // Corner cases of image
            if (i == 0 && j == 0)
            {
                // Top left corner
                int neighbors = 4;

                BYTE blue_values[] = {copy[i][j].rgbtBlue, copy[i][j + 1].rgbtBlue,
                                      copy[i + 1][j].rgbtBlue, copy[i + 1][j + 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen, copy[i][j + 1].rgbtGreen,
                                       copy[i + 1][j].rgbtGreen, copy[i + 1][j + 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed, copy[i][j + 1].rgbtRed,
                                     copy[i + 1][j].rgbtRed, copy[i + 1][j + 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (i == 0 && j == width - 1)
            {
                // top right corner
                int neighbors = 4;

                BYTE blue_values[] = {copy[i][j].rgbtBlue, copy[i][j - 1].rgbtBlue,
                                      copy[i + 1][j - 1].rgbtBlue, copy[i + 1][j].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen, copy[i][j - 1].rgbtGreen,
                                       copy[i + 1][j - 1].rgbtGreen, copy[i + 1][j].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed, copy[i][j - 1].rgbtRed,
                                     copy[i + 1][j - 1].rgbtRed, copy[i + 1][j].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (i == height - 1 && j == 0)
            {
                // bottom left corner
                int neighbors = 4;

                BYTE blue_values[] = {copy[i][j].rgbtBlue, copy[i - 1][j].rgbtBlue,
                                      copy[i - 1][j + 1].rgbtBlue, copy[i][j + 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen, copy[i - 1][j].rgbtGreen,
                                       copy[i - 1][j + 1].rgbtGreen, copy[i][j + 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed, copy[i - 1][j].rgbtRed,
                                     copy[i - 1][j + 1].rgbtRed, copy[i][j + 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (i == height - 1 && j == width - 1)
            {
                // bottom right corner
                int neighbors = 4;

                BYTE blue_values[] = {copy[i][j].rgbtBlue, copy[i - 1][j - 1].rgbtBlue,
                                      copy[i - 1][j].rgbtBlue, copy[i][j - 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen, copy[i - 1][j - 1].rgbtGreen,
                                       copy[i - 1][j].rgbtGreen, copy[i][j - 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed, copy[i - 1][j - 1].rgbtRed,
                                     copy[i - 1][j].rgbtRed, copy[i][j - 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }

            // Border cases of image
            else if (i == 0 && j > 0 && j < width - 1)
            {
                // Top border
                int neighbors = 6;

                BYTE blue_values[] = {copy[i][j].rgbtBlue,         copy[i][j - 1].rgbtBlue,
                                      copy[i + 1][j - 1].rgbtBlue, copy[i + 1][j].rgbtBlue,
                                      copy[i + 1][j + 1].rgbtBlue, copy[i][j + 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen,         copy[i][j - 1].rgbtGreen,
                                       copy[i + 1][j - 1].rgbtGreen, copy[i + 1][j].rgbtGreen,
                                       copy[i + 1][j + 1].rgbtGreen, copy[i][j + 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed,         copy[i][j - 1].rgbtRed,
                                     copy[i + 1][j - 1].rgbtRed, copy[i + 1][j].rgbtRed,
                                     copy[i + 1][j + 1].rgbtRed, copy[i][j + 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                // bottom border
                int neighbors = 6;

                BYTE blue_values[] = {copy[i][j].rgbtBlue,         copy[i][j - 1].rgbtBlue,
                                      copy[i - 1][j - 1].rgbtBlue, copy[i - 1][j].rgbtBlue,
                                      copy[i - 1][j + 1].rgbtBlue, copy[i][j + 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen,         copy[i][j - 1].rgbtGreen,
                                       copy[i - 1][j - 1].rgbtGreen, copy[i - 1][j].rgbtGreen,
                                       copy[i - 1][j + 1].rgbtGreen, copy[i][j + 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed,         copy[i][j - 1].rgbtRed,
                                     copy[i - 1][j - 1].rgbtRed, copy[i - 1][j].rgbtRed,
                                     copy[i - 1][j + 1].rgbtRed, copy[i][j + 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (j == 0 && i > 0 && i < height - 1)
            {
                // left border
                int neighbors = 6;

                BYTE blue_values[] = {copy[i][j].rgbtBlue,         copy[i - 1][j].rgbtBlue,
                                      copy[i - 1][j + 1].rgbtBlue, copy[i][j + 1].rgbtBlue,
                                      copy[i + 1][j + 1].rgbtBlue, copy[i + 1][j].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen,         copy[i - 1][j].rgbtGreen,
                                       copy[i - 1][j + 1].rgbtGreen, copy[i][j + 1].rgbtGreen,
                                       copy[i + 1][j + 1].rgbtGreen, copy[i + 1][j].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed,         copy[i - 1][j].rgbtRed,
                                     copy[i - 1][j + 1].rgbtRed, copy[i][j + 1].rgbtRed,
                                     copy[i + 1][j + 1].rgbtRed, copy[i + 1][j].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
            else if (j == width - 1 && i > 0 && i < height - 1)
            {
                // right border
                int neighbors = 6;

                BYTE blue_values[] = {copy[i][j].rgbtBlue,         copy[i - 1][j - 1].rgbtBlue,
                                      copy[i - 1][j].rgbtBlue,     copy[i][j - 1].rgbtBlue,
                                      copy[i + 1][j - 1].rgbtBlue, copy[i + 1][j].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen,         copy[i - 1][j - 1].rgbtGreen,
                                       copy[i - 1][j].rgbtGreen,     copy[i][j - 1].rgbtGreen,
                                       copy[i + 1][j - 1].rgbtGreen, copy[i + 1][j].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed,         copy[i - 1][j - 1].rgbtRed,
                                     copy[i - 1][j].rgbtRed,     copy[i][j - 1].rgbtRed,
                                     copy[i + 1][j - 1].rgbtRed, copy[i + 1][j].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }

            else
            {
                int neighbors = 9;

                BYTE blue_values[] = {copy[i][j].rgbtBlue,         copy[i - 1][j - 1].rgbtBlue,
                                      copy[i - 1][j].rgbtBlue,     copy[i - 1][j + 1].rgbtBlue,
                                      copy[i][j - 1].rgbtBlue,     copy[i][j + 1].rgbtBlue,
                                      copy[i + 1][j - 1].rgbtBlue, copy[i + 1][j].rgbtBlue,
                                      copy[i + 1][j + 1].rgbtBlue};

                BYTE green_values[] = {copy[i][j].rgbtGreen,         copy[i - 1][j - 1].rgbtGreen,
                                       copy[i - 1][j].rgbtGreen,     copy[i - 1][j + 1].rgbtGreen,
                                       copy[i][j - 1].rgbtGreen,     copy[i][j + 1].rgbtGreen,
                                       copy[i + 1][j - 1].rgbtGreen, copy[i + 1][j].rgbtGreen,
                                       copy[i + 1][j + 1].rgbtGreen};

                BYTE red_values[] = {copy[i][j].rgbtRed,         copy[i - 1][j - 1].rgbtRed,
                                     copy[i - 1][j].rgbtRed,     copy[i - 1][j + 1].rgbtRed,
                                     copy[i][j - 1].rgbtRed,     copy[i][j + 1].rgbtRed,
                                     copy[i + 1][j - 1].rgbtRed, copy[i + 1][j].rgbtRed,
                                     copy[i + 1][j + 1].rgbtRed};

                // Sets the RGB values of a pixel to the average of the surrounding pixels.
                int blue = get_color_avg(blue_values, neighbors);
                image[i][j].rgbtBlue = blue;

                int green = get_color_avg(green_values, neighbors);
                image[i][j].rgbtGreen = green;

                int red = get_color_avg(red_values, neighbors);
                image[i][j].rgbtRed = red;
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Make copy of image to save values.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Iterate through rows of image
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols of image.
        for (int j = 0; j < width; j++)
        {

            // Corner cases of image
            if (i == 0 && j == 0)
            {
                // Top left corner
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    0,                          // top left
                    0,                          // top center
                    0,                          // top right
                    0,                          // left center
                    copy[i][j].rgbtBlue,        // center
                    copy[i][j + 1].rgbtBlue,    // right center
                    0,                          // bottom left
                    copy[i + 1][j].rgbtBlue,    // bottom center
                    copy[i + 1][j + 1].rgbtBlue // bottom right
                };

                BYTE green_values[] = {
                    0,                           // top left
                    0,                           // top center
                    0,                           // top right
                    0,                           // left center
                    copy[i][j].rgbtGreen,        // center
                    copy[i][j + 1].rgbtGreen,    // right center
                    0,                           // bottom left
                    copy[i + 1][j].rgbtGreen,    // bottom center
                    copy[i + 1][j + 1].rgbtGreen // bottom right
                };

                BYTE red_values[] = {
                    0,                         // top left
                    0,                         // top center
                    0,                         // top right
                    0,                         // left center
                    copy[i][j].rgbtRed,        // center
                    copy[i][j + 1].rgbtRed,    // right center
                    0,                         // bottom left
                    copy[i + 1][j].rgbtRed,    // bottom center
                    copy[i + 1][j + 1].rgbtRed // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (i == 0 && j == width - 1)
            {
                // top right corner
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    0,                           // top left
                    0,                           // top center
                    0,                           // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    0,                           // right center
                    copy[i + 1][j - 1].rgbtBlue, // bottom left
                    copy[i + 1][j].rgbtBlue,     // bottom center
                    0                            // bottom right
                };

                BYTE green_values[] = {
                    0,                            // top left
                    0,                            // top center
                    0,                            // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    0,                            // right center
                    copy[i + 1][j - 1].rgbtGreen, // bottom left
                    copy[i + 1][j].rgbtGreen,     // bottom center
                    0                             // bottom right
                };

                BYTE red_values[] = {
                    0,                          // top left
                    0,                          // top center
                    0,                          // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    0,                          // right center
                    copy[i + 1][j - 1].rgbtRed, // bottom left
                    copy[i + 1][j].rgbtRed,     // bottom center
                    0                           // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (i == height - 1 && j == 0)
            {
                // bottom left corner
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    0,                           // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    copy[i - 1][j + 1].rgbtBlue, // top right
                    0,                           // left center
                    copy[i][j].rgbtBlue,         // center
                    copy[i][j + 1].rgbtBlue,     // right center
                    0,                           // bottom left
                    0,                           // bottom center
                    0                            // bottom right
                };

                BYTE green_values[] = {
                    0,                            // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    copy[i - 1][j + 1].rgbtGreen, // top right
                    0,                            // left center
                    copy[i][j].rgbtGreen,         // center
                    copy[i][j + 1].rgbtGreen,     // right center
                    0,                            // bottom left
                    0,                            // bottom center
                    0                             // bottom right
                };

                BYTE red_values[] = {
                    0,                          // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    copy[i - 1][j + 1].rgbtRed, // top right
                    0,                          // left center
                    copy[i][j].rgbtRed,         // center
                    copy[i][j + 1].rgbtRed,     // right center
                    0,                          // bottom left
                    0,                          // bottom center
                    0                           // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (i == height - 1 && j == width - 1)
            {
                // bottom right corner
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    copy[i - 1][j - 1].rgbtBlue, // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    0,                           // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    0,                           // right center
                    0,                           // bottom left
                    0,                           // bottom center
                    0                            // bottom right
                };

                BYTE green_values[] = {
                    copy[i - 1][j - 1].rgbtGreen, // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    0,                            // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    0,                            // right center
                    0,                            // bottom left
                    0,                            // bottom center
                    0                             // bottom right
                };

                BYTE red_values[] = {
                    copy[i - 1][j - 1].rgbtRed, // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    0,                          // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    0,                          // right center
                    0,                          // bottom left
                    0,                          // bottom center
                    0                           // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }

            // Border cases of image
            else if (i == 0 && j > 0 && j < width - 1)
            {
                // Top border
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    0,                           // top left
                    0,                           // top center
                    0,                           // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    copy[i][j + 1].rgbtBlue,     // right center
                    copy[i + 1][j - 1].rgbtBlue, // bottom left
                    copy[i + 1][j].rgbtBlue,     // bottom center
                    copy[i + 1][j + 1].rgbtBlue  // bottom right
                };

                BYTE green_values[] = {
                    0,                            // top left
                    0,                            // top center
                    0,                            // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    copy[i][j + 1].rgbtGreen,     // right center
                    copy[i + 1][j - 1].rgbtGreen, // bottom left
                    copy[i + 1][j].rgbtGreen,     // bottom center
                    copy[i + 1][j + 1].rgbtGreen  // bottom right
                };

                BYTE red_values[] = {
                    0,                          // top left
                    0,                          // top center
                    0,                          // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    copy[i][j + 1].rgbtRed,     // right center
                    copy[i + 1][j - 1].rgbtRed, // bottom left
                    copy[i + 1][j].rgbtRed,     // bottom center
                    copy[i + 1][j + 1].rgbtRed  // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                // bottom border
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    copy[i - 1][j - 1].rgbtBlue, // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    copy[i - 1][j + 1].rgbtBlue, // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    copy[i][j + 1].rgbtBlue,     // right center
                    0,                           // bottom left
                    0,                           // bottom center
                    0                            // bottom right
                };

                BYTE green_values[] = {
                    copy[i - 1][j - 1].rgbtGreen, // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    copy[i - 1][j + 1].rgbtGreen, // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    copy[i][j + 1].rgbtGreen,     // right center
                    0,                            // bottom left
                    0,                            // bottom center
                    0                             // bottom right
                };

                BYTE red_values[] = {
                    copy[i - 1][j - 1].rgbtRed, // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    copy[i - 1][j + 1].rgbtRed, // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    copy[i][j + 1].rgbtRed,     // right center
                    0,                          // bottom left
                    0,                          // bottom center
                    0                           // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (j == 0 && i > 0 && i < height - 1)
            {
                // left border
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    0,                           // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    copy[i - 1][j + 1].rgbtBlue, // top right
                    0,                           // left center
                    copy[i][j].rgbtBlue,         // center
                    copy[i][j + 1].rgbtBlue,     // right center
                    0,                           // bottom left
                    copy[i + 1][j].rgbtBlue,     // bottom center
                    copy[i + 1][j + 1].rgbtBlue  // bottom right
                };

                BYTE green_values[] = {
                    0,                            // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    copy[i - 1][j + 1].rgbtGreen, // top right
                    0,                            // left center
                    copy[i][j].rgbtGreen,         // center
                    copy[i][j + 1].rgbtGreen,     // right center
                    0,                            // bottom left
                    copy[i + 1][j].rgbtGreen,     // bottom center
                    copy[i + 1][j + 1].rgbtGreen  // bottom right
                };

                BYTE red_values[] = {
                    0,                          // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    copy[i - 1][j + 1].rgbtRed, // top right
                    0,                          // left center
                    copy[i][j].rgbtRed,         // center
                    copy[i][j + 1].rgbtRed,     // right center
                    0,                          // bottom left
                    copy[i + 1][j].rgbtRed,     // bottom center
                    copy[i + 1][j + 1].rgbtRed  // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
            else if (j == width - 1 && i > 0 && i < height - 1)
            {
                // right border

                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    copy[i - 1][j - 1].rgbtBlue, // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    0,                           // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    0,                           // right center
                    copy[i + 1][j - 1].rgbtBlue, // bottom left
                    copy[i + 1][j].rgbtBlue,     // bottom center
                    0                            // bottom right
                };

                BYTE green_values[] = {
                    copy[i - 1][j - 1].rgbtGreen, // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    0,                            // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    0,                            // right center
                    copy[i + 1][j - 1].rgbtGreen, // bottom left
                    copy[i + 1][j].rgbtGreen,     // bottom center
                    0                             // bottom right
                };

                BYTE red_values[] = {
                    copy[i - 1][j - 1].rgbtRed, // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    0,                          // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    0,                          // right center
                    copy[i + 1][j - 1].rgbtRed, // bottom left
                    copy[i + 1][j].rgbtRed,     // bottom center
                    0                           // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }

            else
            {
                int neighbors = 9;
                // top left, top center, top right, left center, center, right center, bottom left,
                // bottom center, bottom right.
                BYTE blue_values[] = {
                    copy[i - 1][j - 1].rgbtBlue, // top left
                    copy[i - 1][j].rgbtBlue,     // top center
                    copy[i - 1][j + 1].rgbtBlue, // top right
                    copy[i][j - 1].rgbtBlue,     // left center
                    copy[i][j].rgbtBlue,         // center
                    copy[i][j + 1].rgbtBlue,     // right center
                    copy[i + 1][j - 1].rgbtBlue, // bottom left
                    copy[i + 1][j].rgbtBlue,     // bottom center
                    copy[i + 1][j + 1].rgbtBlue  // bottom right
                };

                BYTE green_values[] = {
                    copy[i - 1][j - 1].rgbtGreen, // top left
                    copy[i - 1][j].rgbtGreen,     // top center
                    copy[i - 1][j + 1].rgbtGreen, // top right
                    copy[i][j - 1].rgbtGreen,     // left center
                    copy[i][j].rgbtGreen,         // center
                    copy[i][j + 1].rgbtGreen,     // right center
                    copy[i + 1][j - 1].rgbtGreen, // bottom left
                    copy[i + 1][j].rgbtGreen,     // bottom center
                    copy[i + 1][j + 1].rgbtGreen  // bottom right
                };

                BYTE red_values[] = {
                    copy[i - 1][j - 1].rgbtRed, // top left
                    copy[i - 1][j].rgbtRed,     // top center
                    copy[i - 1][j + 1].rgbtRed, // top right
                    copy[i][j - 1].rgbtRed,     // left center
                    copy[i][j].rgbtRed,         // center
                    copy[i][j + 1].rgbtRed,     // right center
                    copy[i + 1][j - 1].rgbtRed, // bottom left
                    copy[i + 1][j].rgbtRed,     // bottom center
                    copy[i + 1][j + 1].rgbtRed  // bottom right
                };

                // Uses the Sobel filter algorithm by applying the Sobel operator "kernel"
                // vertically and horizontally to each pixel. Rounds the sqaure root of the sum of
                // gx^2 and gy^2. Then checks if the channel value is valid and corrects it if not.

                float blue_gx = get_gx(blue_values, neighbors);
                float blue_gy = get_gy(blue_values, neighbors);
                int blue_sobel = round(sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2))));
                blue_sobel = check_bounds(blue_sobel);
                image[i][j].rgbtBlue = blue_sobel;

                float green_gx = get_gx(green_values, neighbors);
                float green_gy = get_gy(green_values, neighbors);
                int green_sobel = round(sqrt((pow(green_gx, 2)) + (pow(green_gy, 2))));
                green_sobel = check_bounds(green_sobel);
                image[i][j].rgbtGreen = green_sobel;

                float red_gx = get_gx(red_values, neighbors);
                float red_gy = get_gy(red_values, neighbors);
                int red_sobel = round(sqrt((pow(red_gx, 2)) + (pow(red_gy, 2))));
                red_sobel = check_bounds(red_sobel);
                image[i][j].rgbtRed = red_sobel;
            }
        }
    }
    return;
}

// produces the average of a RGBTRIPLE array.
int get_color_avg(BYTE values[], int neighbors)
{
    float sum = 0.0;
    for (int i = 0; i < neighbors; i++)
    {
        sum += values[i];
    }

    return round(sum / neighbors);
}

// Applies the Sobel operator to the pixel and gets a weighted sum horizontally.
float get_gx(BYTE values[], int neighbors)
{
    float sum = 0;
    float gx_Kernel[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    for (int i = 0; i < neighbors; i++)
    {
        sum += values[i] * gx_Kernel[i];
    }

    return sum;
}

// Applies the Sobel operator to the pixel and gets a weighted sum vertically.
float get_gy(BYTE values[], int neighbors)
{
    float sum = 0;
    float gy_Kernel[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < neighbors; i++)
    {
        sum += values[i] * gy_Kernel[i];
    }

    return sum;
}

// Keeps the Sobel algorithm in the proper bounds of RGB max 255.
int check_bounds(int sobel)
{
    if (sobel > 0 && sobel < 256)
    {
        return sobel;
    }
    else if (sobel < 0)
    {
        return 0;
    }
    else
    {
        return 255;
    }
}
