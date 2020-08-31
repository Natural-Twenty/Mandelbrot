// Mandelbrot: Pixel coloring functions
// pixelColor.c
//
// Completed by
//  The Minh Tran 
//
// Modified on 2018-09-03
// 
//
// Version 1.0.3: Finalised color scheme
// Version 1.0.2: Experimented with colors
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Initial release.

#include "mandelbrot.h"
#include "pixelColor.h"
#include<math.h>

#define maxIteration 1024

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make the Mandelbrot look amazing.
struct pixel pixelColor(int steps) {
    struct pixel color = {
        .red = steps, 
        .green = steps, 
        .blue = steps
    };

    int mod_steps1 = steps % 9;
    int mod_steps2 = steps % 5;
    int mod_steps3 = steps % 7;

    
    if (steps == NO_ESCAPE) {
    // Black
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else {
        color.red = 28*mod_steps1;
        color.green = 51*mod_steps2 + 50;
        color.blue = 36*mod_steps3 + 30;
    }

    return color;
    
}
