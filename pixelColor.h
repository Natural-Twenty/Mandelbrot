// Mandelbrot: Pixel coloring function
// pixelColor.h
//
// 
//
// You can compile the full server with the command
// dcc -o mandelbrotServer server.c mandelbrot.c pixelColor.c
//
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Initial release.


#ifndef _PIXELCOLOR_H_
#define _PIXELCOLOR_H_

struct pixel pixelColor(int steps);

#endif // !defined(_PIXELCOLOR_H_)
