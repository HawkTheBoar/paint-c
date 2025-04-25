#include "pixelBuffer.h"
#include "definitions.h"
#include "raylib.h"
#include <stdlib.h>
int isPointValid(Vector2 point) {
  return point.x >= 0 && point.y >= 0 && point.x <= SCREEN_WIDTH &&
         point.y <= SCREEN_HEIGHT;
}
int arePointsValid(const Vector2 *points, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (!isPointValid(points[i]))
      return false;
  }
  return true;
}
void pixelBuffer_setPixel(int x, int y, Color c, void *ctx) {
  if (!isPointValid((Vector2){x, y}))
    return;
  pixelBuffer *buffer = (pixelBuffer *)ctx;
  buffer->mainBuffer[y][x] = c;
  buffer->hasChanged = 1;
}
void pixelBuffer_destroy(pixelBuffer *buffer) {
  free(buffer->mainBuffer);
  free(buffer);
}
pixelBuffer *pixelBuffer_create() {
  pixelBuffer *buffer = malloc(sizeof(pixelBuffer));
  buffer->mainBuffer = malloc(SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Color));
  buffer->hasChanged = 1;
  return buffer;
}
