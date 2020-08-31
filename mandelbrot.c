// Mandelbrot: Mandelbrot generation functions
// mandelbrot.c
//
// Completed by
//  The Minh Tran
//
// Modified on 2018-09-03
// 
//
// Version 2.0.3: Added comments to outline purpose
// Version 2.0.2: Rewrote code for readability (added functions, meaningful
//                variable names, etc)
// Version 2.0.1: Added drawMandelbrot function.
// Version 2.0.0: Added escapeSteps function.
// Version 1.0.2: Fix minor typos in comments.
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Initial release.

#include <stdio.h>

#include<math.h>

#include "mandelbrot.h"
#include "pixelColor.h"

// Squaring function
static float square(float a) {
    float result = a * a;
    return result;
}
// Function to calculate the square of an absolute of a complex number
static float squareAbsOf(struct complex w) {
    float result = square(w.re) + square(w.im);
    return result;
    
}
// Function to multiply
static float Multiply(double a, double b) {
    float result = a * b;
    return result;
}    

// Take a pixel grid and and the path from the web browser used to
// request the 'tile'.
//
// The requestPath will be in the form "/mandelbrot/2/{zoom}/{x}/{y}.bmp".
// In the query, 'x' and 'y' are decimals and describe the 'center' of the
// tile and need to be converted into a complex number.
// 'zoom' is an integer representing the zoom level for the tile.

void serveMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    char *requestPath
) {
    struct complex center = {0.0, 0.0};
    int z = 7;

    sscanf(
        requestPath,
        "/mandelbrot/2/%d/%lf/%lf.bmp",
        &z, &center.re, &center.im
    );

    // Use drawMandelbrot to draw the image.
    drawMandelbrot(pixels, center, z);
}

// Draw a single Mandelbrot tile, by calculating and colouring each of
// the pixels in the tile.
//
// The function "returns" this tile by filling in the `pixels` 2D array
// that is passed in to the function.
//
// The `pixels` array is TILE_SIZE high and TILE_SIZE wide.
// The bottom left corner of the image is pixels[0][0].
//
// `center` is a complex number, representing the center of the tile.
// `z` is used to calculate the distance between each pixel in the image.
// Each pixel is 2^(-z) apart from each other.

void drawMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    struct complex center,
    int z

) {
    int x = 0; // Starting index for the x dimension (horizontal)
    int y = 0; // Starting index for the y dimension (vertical)
    float x_co, y_co; //Co-ordinates spanning a circle around the center input. 
    float zoom = pow(2, -z); //Distance between each pizel

    struct complex num;
    // x and y coordinates that span around the centre. Each pixel has some
    // distance between them dependent on the zoom.
    x_co = (center.re - ((TILE_SIZE/2) * zoom));
    y_co = (center.im - ((TILE_SIZE/2) * zoom));
    
    // Nested for-loops to account for a two-dimesional array.
    for (y = 0; y < TILE_SIZE; y++) {
        
        for (x = 0; x < TILE_SIZE; x++) {
            // The co-ordinates represent a complex number that will be used as
            // an input to the escapeSteps function.
            num.re = x_co + zoom/2 + (x * zoom);
            num.im = y_co + zoom/2 + (y * zoom);           

            int escResult = escapeSteps(num);                
            pixels[y][x] =  pixelColor(escResult);
                        
        }
                
    }    
    
}

// Determine the number of steps required to escape the Mandelbrot set,
// for the given complex number `c`.
int escapeSteps(struct complex c) {

    int steps = 0;
    
    // initiate the zero-complex        
    struct complex z = {
        .re = 0,
        .im = 0
    };
    
    // while-loop to determine whether a complex number is in the set or not
    while ((steps < MAX_STEPS) && (squareAbsOf(z) <= 4)) {
    
        // Create copies of z for use in calculations.
        double cpyOfRealZ = z.re;
        double cpyOfImagZ = z.im;
        
        // Make z = to z squared plus input which is a complex number
        // Recall if z = a +bi, real-z squared = a^2 - b^2 
        //             and imaginary-z squared = 2 * a * b 
        z.re = square(cpyOfRealZ) - square(cpyOfImagZ) + c.re;
        z.im = 2 * Multiply(cpyOfRealZ, cpyOfImagZ) + c.im;
        
        // steps increases by 1 each time to ensure eventual termination
        steps++;
        
        // If the loop runs fully, 
        if (steps == MAX_STEPS) {
            return NO_ESCAPE;
        }        
    
    }
    return steps;    
}

