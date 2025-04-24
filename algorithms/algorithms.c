#include "algorithms.h"
#include <raylib.h>
#include <stdlib.h>
/**
 * Draws a circle using the Midpoint Circle Algorithm (Bresenham's Circle
 * Algorithm)
 *
 * @param center    Pointer to Vector2 structure containing circle center
 * coordinates (x,y)
 * @param radius    Radius of the circle in pixels
 * @param c         Pointer to Color structure for the circle
 * @param draw_pixel Function pointer to plot a pixel at (x,y) with color c
 */
void drawCircle(const Vector2 *center, int radius, const Color *c,
                drawPixel_func draw_pixel) {
  int x = 0;
  int y = radius;
  int d = 1 - radius; // Decision parameter

  // Plot the initial points in all octants
  while (x <= y) {
    // Plot points in all 8 octants simultaneously
    draw_pixel(center->x + x, center->y + y, *c); // Octant 1
    draw_pixel(center->x + y, center->y + x, *c); // Octant 2
    draw_pixel(center->x - x, center->y + y, *c); // Octant 4
    draw_pixel(center->x - y, center->y + x, *c); // Octant 3
    draw_pixel(center->x + x, center->y - y, *c); // Octant 8
    draw_pixel(center->x + y, center->y - x, *c); // Octant 7
    draw_pixel(center->x - x, center->y - y, *c); // Octant 5
    draw_pixel(center->x - y, center->y - x, *c); // Octant 6

    // Update the decision parameter
    if (d < 0) {
      // Choose pixel E (East)
      d += 2 * x + 3;
    } else {
      // Choose pixel SE (South-East)
      d += 2 * (x - y) + 5;
      y--;
    }
    x++;
  }
}
void drawLine(const Vector2 *point, const Vector2 *point2, const Color *c,
              drawPixel_func draw_pixel) {
  // Extract coordinates for readability
  int x1 = point->x;
  int y1 = point->y;
  int x2 = point2->x;
  int y2 = point2->y;

  // Calculate differences between coordinates
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  // Determine the direction of increment for x and y
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;

  // Initialize decision parameter
  int err = dx - dy;
  int e2;

  // Main loop - continues until we reach the end point
  while (1) {
    // Plot the current pixel
    draw_pixel(x1, y1, *c);

    // Check if we've reached the end point
    if (x1 == x2 && y1 == y2)
      break;

    // Calculate next decision parameter
    e2 = 2 * err;

    // Adjust error and x-coordinate if needed
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }

    // Adjust error and y-coordinate if needed
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}
void drawPolygon(const Vector2 *points, size_t count, const Color *c,
                 drawPixel_func drawPixel) {
  if (count < 1)
    return;
  for (size_t i = 1; i < count; i++) {
    drawLine(points + i, points + i - 1, c, drawPixel);
  }
  drawLine(&points[0], &points[count - 1], c, drawPixel);
}
void drawSquare(const Vector2 *start, const Vector2 *end, const Color *c,
                drawPixel_func drawPixel) {
  Vector2 point1 = {start->x, end->y};
  Vector2 point3 = {end->x, start->y};
  drawPolygon((Vector2[]){point1, *end, point3, *start}, 4, c, drawPixel);
}
