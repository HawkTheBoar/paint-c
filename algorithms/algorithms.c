#include "algorithms.h"
#include <raylib.h>
#include <stdlib.h>
void drawCircle(const Vector2 *center, int radius, const Color *c,
                drawPixel_func draw_pixel) {}
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
