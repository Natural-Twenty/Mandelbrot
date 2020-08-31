// Mandelbrot: Mandelbrot generation functions
// mandelbrot.h
//
// 
//
// You can compile the full server with the command
// dcc -o mandelbrotServer server.c mandelbrot.c pixelColor.c
//
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Initial release.


#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

// Size of each image
//
// Each tile should be TILE_SIZE pixels wide and TILE_SIZE pixels tall.
//
// Make sure this value is unchanged
#define TILE_SIZE 512

// Escape Steps
//
// The maximum number of steps that we loop to test if a complex number
// is in the mandelbrot set.
//
// Any number that is assumed to be in the mandelbrot set has NO_ESCAPE
// number of steps.
//
// Make sure this value is unchanged
#define MAX_STEPS 256
#define NO_ESCAPE -1

// Structs used by the program

// BMP is made of pixels
struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Complex Numbers
// Complex number is (re + im * i)
struct complex {
    double re;
    double im;
};

// Functions
void serveMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    char *requestPath
);
void drawMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    struct complex center,
    int z
);
int escapeSteps(struct complex c);

#endif // !defined(_MANDELBROT_H_)
