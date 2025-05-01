#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "raylib.h"
#include <stdlib.h>
typedef void (*drawPixel_func)(int x, int y, Color c, void *ctx);
void drawCircle(const Vector2 *center, int radius, const Color *c,
                drawPixel_func drawPixel, void *ctx);
/**
 * Draws a line between two points using Bresenham's line algorithm.
 *
 * @param point    The starting point of the line (x1, y1)
 * @param point2   The ending point of the line (x2, y2)
 * @param c        The color to draw the line with
 * @param draw_pixel Function pointer to plot a pixel at (x,y) with color c
 */
void drawLine(const Vector2 *point1, const Vector2 *point2, const Color *c,
              int line_width, drawPixel_func drawPixel, void *ctx);
void drawPolygon(const Vector2 *points, size_t count, const Color *c,
                 drawPixel_func drawPixel, void *ctx);
void drawSquare(const Vector2 *start, const Vector2 *end, const Color *c,
                drawPixel_func drawPixel, void *ctx);
#endif
