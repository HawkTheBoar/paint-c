#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H
#include "definitions.h"
#include "raylib.h"
#include <stdlib.h>
typedef struct {
  Color (*mainBuffer)[SCREEN_HEIGHT];
  int hasChanged;
} pixelBuffer;
int isPointValid(Vector2 point);
int arePointsValid(const Vector2 *points, size_t count);
void pixelBuffer_setPixel(int x, int y, Color c, void *ctx);
void pixelBuffer_destroy(pixelBuffer *buffer);
pixelBuffer *pixelBuffer_create();
#endif // !PIXELBUFFER_H
