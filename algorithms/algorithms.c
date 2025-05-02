#include "algorithms.h"
#include "definitions.h"
#include "math.h"
#include "pixelBuffer/pixelBuffer.h"
#include "utils/utils.h"
#include <raylib.h>
#include <stdlib.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846 // Fallback definition
#endif
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
                drawPixel_func draw_pixel, void *ctx) {
  if (!isPointValid(*center))
    return;
  int x = 0;
  int y = radius;
  int d = 1 - radius; // Decision parameter

  // Plot the initial points in all octants
  while (x <= y) {
    // Plot points in all 8 octants simultaneously
    draw_pixel(center->x + x, center->y + y, *c, ctx); // Octant 1
    draw_pixel(center->x + y, center->y + x, *c, ctx); // Octant 2
    draw_pixel(center->x - x, center->y + y, *c, ctx); // Octant 4
    draw_pixel(center->x - y, center->y + x, *c, ctx); // Octant 3
    draw_pixel(center->x + x, center->y - y, *c, ctx); // Octant 8
    draw_pixel(center->x + y, center->y - x, *c, ctx); // Octant 7
    draw_pixel(center->x - x, center->y - y, *c, ctx); // Octant 5
    draw_pixel(center->x - y, center->y - x, *c, ctx); // Octant 6

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
#ifndef DASH_LENGTH
#define DASH_LENGTH 5
#endif

#ifndef GAP_LENGTH
#define GAP_LENGTH 5
#endif

void drawLine(const Vector2 *point, const Vector2 *point2, const Color *c,
              int line_width, int isDotted, drawPixel_func draw_pixel,
              void *ctx) {
  int x1 = point->x;
  int y1 = point->y;
  int x2 = point2->x;
  int y2 = point2->y;

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  bool is_steep = dy > dx;

  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;

  int err = dx - dy;

  int total_dash = DASH_LENGTH + GAP_LENGTH;
  int dash_counter = 0;
  bool use_dash = isDotted;

  line_width = line_width < 1 ? 1 : line_width;

  int start_offset = -(line_width / 2);
  int end_offset = start_offset + line_width - 1;

  while (1) {
    if (use_dash) {
      if (dash_counter < DASH_LENGTH) {
        if (is_steep) {
          for (int ox = start_offset; ox <= end_offset; ++ox) {
            draw_pixel(x1 + ox, y1, *c, ctx);
          }
        } else {
          for (int oy = start_offset; oy <= end_offset; ++oy) {
            draw_pixel(x1, y1 + oy, *c, ctx);
          }
        }
      }
      dash_counter = (dash_counter + 1) % total_dash;
    } else {
      if (is_steep) {
        for (int ox = start_offset; ox <= end_offset; ++ox) {
          draw_pixel(x1 + ox, y1, *c, ctx);
        }
      } else {
        for (int oy = start_offset; oy <= end_offset; ++oy) {
          draw_pixel(x1, y1 + oy, *c, ctx);
        }
      }
    }

    if (x1 == x2 && y1 == y2)
      break;

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}
void drawPolygon(const Vector2 *points, size_t count, const Color *c,
                 drawPixel_func drawPixel, void *ctx) {
  if (count < 1)
    return;
  for (size_t i = 1; i < count; i++) {
    drawLine(points + i, points + i - 1, c, 1, 0, drawPixel, ctx);
  }
  drawLine(&points[0], &points[count - 1], c, 1, 0, drawPixel, ctx);
}
void drawSquare(const Vector2 *start, const Vector2 *end, const Color *c,
                drawPixel_func drawPixel, void *ctx) {
  Vector2 point1 = {start->x, end->y};
  Vector2 point3 = {end->x, start->y};
  drawPolygon((Vector2[]){point1, *end, point3, *start}, 4, c, drawPixel, ctx);
}
Vector2 snapTo(Vector2 p1, Vector2 p2) {
  // Calculate the vector from p1 to p2
  Vector2 delta = {p2.x - p1.x, p2.y - p1.y};

  // Calculate the angle in radians (-π to π)
  float angle = atan2f(delta.y, delta.x);

  // Snap to nearest 45 degrees (π/4 radians)
  float snapped_angle = roundf(angle / (M_PI / 4)) * (M_PI / 4);

  // Calculate the maximum possible length that stays within bounds
  float max_length_x = (delta.x >= 0) ? (PIXELBUFFER_WIDTH - p1.x) : p1.x;
  float max_length_y = (delta.y >= 0) ? (PIXELBUFFER_HEIGHT - p1.y) : p1.y;

  // The maximum length we can use while staying within bounds
  float cos_angle = cosf(snapped_angle);
  float sin_angle = sinf(snapped_angle);

  float max_length = INFINITY;

  if (fabsf(cos_angle) > 0.0001f) {
    float max_x = max_length_x / fabsf(cos_angle);
    max_length = fminf(max_length, max_x);
  }

  if (fabsf(sin_angle) > 0.0001f) {
    float max_y = max_length_y / fabsf(sin_angle);
    max_length = fminf(max_length, max_y);
  }

  // Use the original length or the maximum allowed length, whichever is smaller
  float original_length = sqrtf(delta.x * delta.x + delta.y * delta.y);
  float length = fminf(original_length, max_length);

  // Create new snapped vector
  Vector2 snapped_point = {p1.x + cosf(snapped_angle) * length,
                           p1.y + sinf(snapped_angle) * length};

  // Ensure we're exactly at the border if we're at the limit
  snapped_point.x = clamp(snapped_point.x, 0, PIXELBUFFER_WIDTH);
  snapped_point.y = clamp(snapped_point.y, 0, PIXELBUFFER_HEIGHT);

  return snapped_point;
}
