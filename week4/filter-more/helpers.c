// 11.05.23 written by ROI
// 16.05.23 commented
// The program turns .bmp images according to options -g/-r/-b/-e into reflected, grey, blured or edged one.
// The detailes of the task: https://cs50.harvard.edu/x/2023/psets/4/filter/more/
// Usage examples:
// ./filter -g IMAGE.bmp GREY.bmp // to get grey image GREY.bmp from IMAGE.bmp
// ./filter -r IMAGE.bmp REFLECTED.bmp // to get reflected image REFLECTED.bmp from IMAGE.bmp
// ./filter -b IMAGE.bmp BLURED.bmp // to get blured image BLURED.bmp from IMAGE.bmp
// ./filter -e IMAGE.bmp EDGED.bmp // to get edged image EDGED.bmp from IMAGE.bmp


#include "helpers.h"
#include <stdio.h>  // printf() - roi
#include <string.h> // memcpy() - roi
#include <math.h>   // sqrt(), round() - roi

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)  // image[j][i].rgbtRed, ...Green and ...Blue all get the everage of them - roi
    {
        for (int i = 0; i < width; i++)
        {
            image[j][i].rgbtRed =
            image[j][i].rgbtGreen =
            image[j][i].rgbtBlue = round((image[j][i].rgbtRed + image[j][i].rgbtGreen + image[j][i].rgbtBlue) / 3);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Swap;
    for (int j = 0; j < height; j++)
    {
        int k = width;
        for (int i = 0; i < width/2; i++) // reflection via axis y in the middle of the .bmp - roi
        {
            Swap = image[j][i];
            image[j][i] = image[j][k];
            image[j][k] = Swap;
            --k;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Origin[height][width];

    // printf("sizeof(BYTE)) = %lu\n", sizeof(BYTE)); // checked: 1. the size of BYTE and 2. if BYTE can be used as an argument of sizof()
    memcpy(Origin, image, height * width * 3 * (sizeof(BYTE))); //Origin = image - roi

    // converstion everything EXTPT the 1st "0"and the last "height-1" line as well as the 1st "0" and the last "width-1" columns - roi
    for (int j = 1, n = height-1; j < n; j++)
    {
        for (int i = 1, k = width-1; i < k; i++)
        {
           image[j][i].rgbtRed = (Origin[j-1][i-1].rgbtRed + Origin[j-1][i].rgbtRed + Origin[j-1][i+1].rgbtRed +
                                  Origin[j]  [i-1].rgbtRed + Origin[j]  [i].rgbtRed + Origin[j]  [i+1].rgbtRed +
                                  Origin[j+1][i-1].rgbtRed + Origin[j+1][i].rgbtRed + Origin[j+1][i+1].rgbtRed) / 9;
           image[j][i].rgbtGreen = (Origin[j-1][i-1].rgbtGreen + Origin[j-1][i].rgbtGreen + Origin[j-1][i+1].rgbtGreen +
                                    Origin[j]  [i-1].rgbtGreen + Origin[j]  [i].rgbtGreen + Origin[j]  [i+1].rgbtGreen +
                                    Origin[j+1][i-1].rgbtGreen + Origin[j+1][i].rgbtGreen + Origin[j+1][i+1].rgbtGreen) / 9;
           image[j][i].rgbtBlue = (Origin[j-1][i-1].rgbtBlue + Origin[j-1][i].rgbtBlue + Origin[j-1][i+1].rgbtBlue +
                                  Origin[j]  [i-1].rgbtBlue + Origin[j]  [i].rgbtBlue + Origin[j]  [i+1].rgbtBlue +
                                  Origin[j+1][i-1].rgbtBlue + Origin[j+1][i].rgbtBlue + Origin[j+1][i+1].rgbtBlue) / 9;
        }
    }
    for (int i = 1, k = width-1; i < k; i++) // the 1st "=0" and the last "=height - 1" lines converstion - roi
    {
        // blur 4 the 1st line - roi
        int j = 0;
        image[1][i].rgbtRed = (Origin[j]  [i-1].rgbtRed + Origin[j]  [i].rgbtRed + Origin[j]  [i+1].rgbtRed +
                               Origin[j+1][i-1].rgbtRed + Origin[j+1][i].rgbtRed + Origin[j+1][i+1].rgbtRed) / 6;
        image[1][i].rgbtGreen = (Origin[j]  [i-1].rgbtGreen + Origin[j]  [i].rgbtGreen + Origin[j]  [i+1].rgbtGreen +
                                 Origin[j+1][i-1].rgbtGreen + Origin[j+1][i].rgbtGreen + Origin[j+1][i+1].rgbtGreen) / 6;
        image[1][i].rgbtBlue = (Origin[j]  [i-1].rgbtBlue + Origin[j]  [i].rgbtBlue + Origin[j]  [i+1].rgbtBlue +
                               Origin[j+1][i-1].rgbtBlue + Origin[j+1][i].rgbtBlue + Origin[j+1][i+1].rgbtBlue) / 6;
        // blur 4 the las line - roi
        j = height - 1;
        image[height][i].rgbtRed = (Origin[j-1][i-1].rgbtRed + Origin[j-1][i].rgbtRed + Origin[j-1][i+1].rgbtRed +
                               Origin[j][i-1].rgbtRed + Origin[j][i].rgbtRed + Origin[j][i+1].rgbtRed) / 6;
        image[height][i].rgbtGreen = (Origin[j-1][i-1].rgbtGreen + Origin[j-1][i].rgbtGreen + Origin[j-1][i+1].rgbtGreen +
                                 Origin[j] [i-1].rgbtGreen + Origin[j][i].rgbtGreen + Origin[j] [i+1].rgbtGreen) / 6;
        image[height][i].rgbtBlue = (Origin[j-1][i-1].rgbtBlue + Origin[j-1][i].rgbtBlue + Origin[j-1][i+1].rgbtBlue +
                                     Origin[j][i-1].rgbtBlue + Origin[j][i].rgbtBlue + Origin[j][i+1].rgbtBlue) / 6;
    }
    for (int j = 1, n = height-1; j < n; j++)
    {
        int i = 0; // for 1st collumn - roi
        image[j][i].rgbtRed = (Origin[j-1][i].rgbtRed + Origin[j-1][i+1].rgbtRed +
                               Origin[j]  [i].rgbtRed + Origin[j]  [i+1].rgbtRed +
                               Origin[j+1][i].rgbtRed + Origin[j+1][i+1].rgbtRed) / 6;
        image[j][i].rgbtGreen = (Origin[j-1][i].rgbtGreen + Origin[j-1][i+1].rgbtGreen +
                                 Origin[j]  [i].rgbtGreen + Origin[j]  [i+1].rgbtGreen +
                                 Origin[j+1][i].rgbtGreen + Origin[j+1][i+1].rgbtGreen) / 6;
        image[j][i].rgbtBlue = (Origin[j-1][i].rgbtBlue + Origin[j-1][i+1].rgbtBlue +
                                Origin[j]  [i].rgbtBlue + Origin[j]  [i+1].rgbtBlue +
                                Origin[j+1][i].rgbtBlue + Origin[j+1][i+1].rgbtBlue) / 6;
        i = width-1; // for the last collumn - roi
        image[j][i].rgbtRed = (Origin[j-1][i-1].rgbtRed + Origin[j-1][i].rgbtRed +
                               Origin[j]  [i-1].rgbtRed + Origin[j]  [i].rgbtRed +
                               Origin[j+1][i-1].rgbtRed + Origin[j+1][i].rgbtRed) / 6;
        image[j][i].rgbtGreen = (Origin[j-1][i-1].rgbtGreen + Origin[j-1][i].rgbtGreen +
                                 Origin[j]  [i-1].rgbtGreen + Origin[j]  [i].rgbtGreen +
                                 Origin[j+1][i-1].rgbtGreen + Origin[j+1][i].rgbtGreen) / 6;
        image[j][i].rgbtBlue = (Origin[j-1][i-1].rgbtBlue + Origin[j-1][i].rgbtBlue +
                                Origin[j]  [i-1].rgbtBlue + Origin[j]  [i].rgbtBlue +
                                Origin[j+1][i-1].rgbtBlue + Origin[j+1][i].rgbtBlue) / 6;
    }
    // the "4" corner pixels convertion - roi
    //ther cornters of matriy image[j][i] are: image[0][0] image[height-1][width-1] image[height-1][0] image[0][width-1] - roi

    // Blur für left upper cornter pixel image[0][0] - roi
    int j = 0;
    int i = 0;

    // debug printf - roi
    /*printf("image[%i][%i].rgbtRed =  %i\n", j, i, image[j][i].rgbtRed);
    printf("image[%i][%i].rgbtGreen =  %i\n", j, i, image[j][i].rgbtGreen);
    printf("image[%i][%i].rgbtBlue =  %i\n\n", j, i, image[j][i].rgbtBlue);*/

    image[j][i].rgbtRed = (Origin[j]  [i].rgbtRed + Origin[j]  [i+1].rgbtRed +
                           Origin[j+1][i].rgbtRed + Origin[j+1][i+1].rgbtRed) / 4;
    image[j][i].rgbtGreen = (Origin[j]  [i].rgbtGreen + Origin[j]  [i+1].rgbtGreen +
                             Origin[j+1][i].rgbtGreen + Origin[j+1][i+1].rgbtGreen) / 4;
    image[j][i].rgbtBlue = (Origin[j]  [i].rgbtBlue + Origin[j]  [i+1].rgbtBlue +
                           Origin[j+1][i].rgbtBlue + Origin[j+1][i+1].rgbtBlue) / 4;

    // Blur für right under cornter pixel image[height-1][width-1] - roi
    j = height - 1;
    i = width - 1;

    image[j][i].rgbtRed = (Origin[j-1][i-1].rgbtRed + Origin[j-1][i].rgbtRed +
                           Origin[j]  [i-1].rgbtRed + Origin[j]  [i].rgbtRed) / 4;
    image[j][i].rgbtGreen = (Origin[j-1][i-1].rgbtGreen + Origin[j-1][i].rgbtGreen +
                             Origin[j]  [i-1].rgbtGreen + Origin[j]  [i].rgbtGreen) / 4;
    image[j][i].rgbtBlue = (Origin[j-1][i-1].rgbtBlue + Origin[j-1][i].rgbtBlue +
                            Origin[j]  [i-1].rgbtBlue + Origin[j]  [i].rgbtBlue) / 4;

    // Blur für right upper cornter pixel image[height-1][0] - roi
    j = height - 1;
    i = 0;

    image[j][i].rgbtRed = (Origin[j-1][i].rgbtRed + Origin[j-1][i+1].rgbtRed +
                           Origin[j]  [i].rgbtRed + Origin[j]  [i+1].rgbtRed) / 4;
    image[j][i].rgbtGreen = (Origin[j-1][i].rgbtGreen + Origin[j-1][i+1].rgbtGreen +
                             Origin[j]  [i].rgbtGreen + Origin[j]  [i+1].rgbtGreen) / 4;
    image[j][i].rgbtBlue = (Origin[j-1][i].rgbtBlue + Origin[j-1][i+1].rgbtBlue +
                            Origin[j]  [i].rgbtBlue + Origin[j]  [i+1].rgbtBlue) / 4;

    // Blur für cornter pixel image[0][width-1] - roi
    j = 0;
    i = width - 1;

    image[j][i].rgbtRed = (Origin[j]  [i-1].rgbtRed + Origin[j]  [i].rgbtRed +
                           Origin[j+1][i-1].rgbtRed + Origin[j+1][i].rgbtRed) / 4;
    image[j][i].rgbtGreen = (Origin[j]  [i-1].rgbtGreen + Origin[j]  [i].rgbtGreen +
                             Origin[j+1][i-1].rgbtGreen + Origin[j+1][i].rgbtGreen) / 4;
    image[j][i].rgbtBlue = (Origin[j]  [i-1].rgbtBlue + Origin[j]  [i].rgbtBlue +
                            Origin[j+1][i-1].rgbtBlue + Origin[j+1][i].rgbtBlue) / 4;

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx, Gy;
    int Origin_height = height + 2;
    int Origin_width = width + 2;

    RGBTRIPLE Origin[Origin_height][Origin_width];

    // Making the copy of array image + adding black border(frame) to the arrey Origin - roi
    for (int j = 0; j < Origin_height; j++)
    {
        for (int i = 0; i < Origin_width; i++)
        {
            if (j == 0 || i == 0 || j == Origin_height - 1 || i ==  Origin_width - 1)
            {
                  // Making the pixels of the array border (frame) black - roi
                  Origin[j][i].rgbtRed = 0;
                  Origin[j][i].rgbtGreen = 0;
                  Origin[j][i].rgbtBlue = 0;
            }
            else
            {
                  // For the rest of pixels copying the picture of image - roi
                  Origin[j][i] = image[j-1][i-1];
            }
        }
    }

    // making the edged image from Original, that is bigger on 2 lines and 2 collumns at the borders (kind of black frame) - roi
    for (int j = 0, n = j + 1; j < height; j++, n++)
    {
        for (int i = 0, k = i + 1; i < width; i++, k++)
        {
           Gx = (-1 * Origin[n-1][k-1].rgbtRed + 0 * Origin[n-1][k].rgbtRed + 1 * Origin[n-1][k+1].rgbtRed +
                 -2 * Origin[n]  [k-1].rgbtRed + 0 * Origin[n]  [k].rgbtRed + 2 * Origin[n]  [k+1].rgbtRed +
                 -1 * Origin[n+1][k-1].rgbtRed + 0 * Origin[n+1][k].rgbtRed + 1 * Origin[n+1][k+1].rgbtRed);

           Gy = (-1 * Origin[n-1][k-1].rgbtRed + -2 * Origin[n-1][k].rgbtRed + -1 * Origin[n-1][k+1].rgbtRed +
                  0 * Origin[n]  [k-1].rgbtRed +  0 * Origin[n]  [k].rgbtRed +  0 * Origin[n]  [k+1].rgbtRed +
                  1 * Origin[n+1][k-1].rgbtRed +  2 * Origin[n+1][k].rgbtRed +  1 * Origin[n+1][k+1].rgbtRed);

           image[j][i].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
           if (image[j][i].rgbtRed > 255)
           {
                image[j][i].rgbtRed = 255;
           }

          Gx = (-1 * Origin[n-1][k-1].rgbtGreen + 0 * Origin[n-1][k].rgbtGreen + 1 * Origin[n-1][k+1].rgbtGreen +
                -2 * Origin[n]  [k-1].rgbtGreen + 0 * Origin[n]  [k].rgbtGreen + 2 * Origin[n]  [k+1].rgbtGreen +
                -1 * Origin[n+1][k-1].rgbtGreen + 0 * Origin[n+1][k].rgbtGreen + 1 * Origin[n+1][k+1].rgbtGreen);

           Gy = (-1 * Origin[n-1][k-1].rgbtGreen + -2 * Origin[n-1][k].rgbtGreen + -1 * Origin[n-1][k+1].rgbtGreen +
                  0 * Origin[n]  [k-1].rgbtGreen +  0 * Origin[n]  [k].rgbtGreen +  0 * Origin[n]  [k+1].rgbtGreen +
                  1 * Origin[n+1][k-1].rgbtGreen +  2 * Origin[n+1][k].rgbtGreen +  1 * Origin[n+1][k+1].rgbtGreen);

           image[j][i].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
           if (image[j][i].rgbtGreen > 255)
           {
                image[j][i].rgbtGreen = 255;
           }

           Gx = (-1 * Origin[n-1][k-1].rgbtBlue + 0 * Origin[n-1][k].rgbtBlue + 1 * Origin[n-1][k+1].rgbtBlue +
                 -2 * Origin[n]  [k-1].rgbtBlue + 0 * Origin[n]  [k].rgbtBlue + 2 * Origin[n]  [k+1].rgbtBlue +
                 -1 * Origin[n+1][k-1].rgbtBlue + 0 * Origin[n+1][k].rgbtBlue + 1 * Origin[n+1][k+1].rgbtBlue);

           Gy = (-1 * Origin[n-1][k-1].rgbtBlue + -2 * Origin[n-1][k].rgbtBlue + -1 * Origin[n-1][k+1].rgbtBlue +
                  0 * Origin[n]  [k-1].rgbtBlue +  0 * Origin[n]  [k].rgbtBlue +  0 * Origin[n]  [k+1].rgbtBlue +
                  1 * Origin[n+1][k-1].rgbtBlue +  2 * Origin[n+1][k].rgbtBlue +  1 * Origin[n+1][k+1].rgbtBlue);

           image[j][i].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
           if (image[j][i].rgbtBlue > 255)
           {
                image[j][i].rgbtBlue = 255;
           }
        }
    }
    return;
}
