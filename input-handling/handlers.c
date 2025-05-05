#include "handlers.h"
#include "algorithms/algorithms.h"
#include "definitions.h"
#include "editordata.h"
#include "pixelBuffer/pixelBuffer.h"
#include "utils/utils.h"
#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define drawpixel (drawPixel_func) draw_pixel
static Vector2 point1 = {-1, -1}, point2 = {-1, -1};
static void invalidatePoint(Vector2 *p) {
  p->x = -1;
  p->y = -1;
};
static int editToleration = 10;
static Vector2 *editPoint;
static Color *editPointColor = &RED;
static int editPointRadius = 5;
static float radius;
static Vector2 polygonPoints[POLYGON_BUFFER_SIZE];
static size_t polygonPointCount = 0;
void draw_pixel(int x, int y, Color c, void *ctx) { DrawPixel(x, y, c); }
void switch_handler(EditorData *editordata, int nextHandler) {
  // invalidate all points set up to this point
  editPoint = NULL;
  invalidatePoint(&point1);
  invalidatePoint(&point2);
  polygonPointCount = 0;
  radius = 0;
  ClearBackground(WHITE);
  editordata->currentInputHandler = nextHandler;
}
static void markPoints(Vector2 *points, size_t count) {
  for (size_t i = 0; i < count; i++) {
    drawCircle(points + i, editPointRadius, editPointColor, drawpixel, NULL);
  }
}
void line_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    if (isPointValid(point1) && isPointValid(point2)) {
      ClearBackground(WHITE);
      drawLine(&point1, &point2, &editordata->editorColor, editordata->size,
               editordata->isDotted, pixelBuffer_setPixel, buffer);
      invalidatePoint(&point1);
      invalidatePoint(&point2);
    }
    break;
  case KEY_ESCAPE:
    ClearBackground(WHITE);
    invalidatePoint(&point1);
    invalidatePoint(&point2);
    break;
  }
}
void line_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                        EditorData *editordata) {
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      point1 = editordata->clampedMousePos;
      break;

    case MOUSE_DRAG:
      point2 = editordata->clampedMousePos;
      if (editordata->shouldSnap)
        point2 = snapTo(point1, point2);
      ClearBackground(WHITE);
      drawLine(&point1, &point2, &editordata->editorColor, editordata->size,
               editordata->isDotted, drawpixel, NULL);
      break;

    case MOUSE_RELEASE:
      ClearBackground(WHITE);
      drawLine(&point1, &point2, &editordata->editorColor, editordata->size,
               editordata->isDotted, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      Vector2 mousePos = editordata->clampedMousePos;
      float distance = getVectorDistance(mousePos, point1);
      float distance2 = getVectorDistance(mousePos, point2);
      if (fmin(distance, distance2) < editToleration) {
        editPoint = distance > distance2 ? &point2 : &point1;
      } else {
        editPoint = NULL;
      }
      break;

    case MOUSE_DRAG:
      if (editPoint != NULL) {
        *editPoint = editordata->clampedMousePos;
        if (editordata->shouldSnap) {

          if (editPoint == &point1) {
            *editPoint = snapTo(point2, *editPoint);
          } else {
            *editPoint = snapTo(point1, *editPoint);
          }
        }
        ClearBackground(WHITE);
        drawLine(&point1, &point2, &editordata->editorColor, editordata->size,
                 editordata->isDotted, drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawLine(&point1, &point2, &editordata->editorColor, editordata->size,
               editordata->isDotted, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
    break;
  }
}
// point1 ... center
// point2 ... the outer point
// radius .. float radius
void circle_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    if (isPointValid(point1) && isPointValid(point2)) {
      ClearBackground(WHITE);
      drawCircle(&point1, radius, &editordata->editorColor,
                 pixelBuffer_setPixel, buffer);
      invalidatePoint(&point1);
      invalidatePoint(&point2);
    }
    break;
  case KEY_ESCAPE:
    ClearBackground(WHITE);
    invalidatePoint(&point1);
    invalidatePoint(&point2);
    break;
  }
}
void circle_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                          EditorData *editordata) {
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      point1 = editordata->clampedMousePos;
      break;

    case MOUSE_DRAG:
      point2 = editordata->clampedMousePos;
      radius = getVectorDistance(point1, point2);
      ClearBackground(WHITE);
      drawCircle(&point1, radius, &editordata->editorColor, drawpixel, NULL);
      break;

    case MOUSE_RELEASE:
      ClearBackground(WHITE);
      drawCircle(&point1, radius, &editordata->editorColor, drawpixel, NULL);
      markPoints((Vector2[]){point1}, 1);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      Vector2 mousePos = editordata->clampedMousePos;
      float distance =
          getVectorDistance(mousePos, point1); // distance to the center
                                               // distance to radius
      float distance2 = fabs(distance - radius);
      if (fmin(distance, distance2) < editToleration) {
        editPoint = distance > distance2 ? &point2 : &point1;
      } else {
        editPoint = NULL;
      }
      break;

    case MOUSE_DRAG:
      if (editPoint != NULL) {
        *editPoint = editordata->clampedMousePos;
        ClearBackground(WHITE);
        // if editing the radius, recalculate it
        if (editPoint == &point2) {
          radius = getVectorDistance(point1, point2);
        }
        drawCircle(&point1, radius, &editordata->editorColor, drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawCircle(&point1, radius, &editordata->editorColor, drawpixel, NULL);
      markPoints((Vector2[]){point1}, 1);
      break;
    }
    break;
  }
}
// Vector2 polygonPoints[POLYGON_BUFFER_SIZE];
// size_t polygonPointCount = 0;
void polygon_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    ClearBackground(WHITE);
    drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                pixelBuffer_setPixel, buffer);
    polygonPointCount = 0;
    break;
  case KEY_ESCAPE:
    ClearBackground(WHITE);
    polygonPointCount = 0;
    break;
  }
}
int pointAdded = 1;
void polygon_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                           EditorData *editordata) {
  if (polygonPointCount > POLYGON_BUFFER_SIZE)
    return;
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      if (editordata->isOutOfBounds) {
        pointAdded = 0;
        break;
      }
      pointAdded = 1;
      polygonPointCount++;
      polygonPoints[polygonPointCount - 1] = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                  drawpixel, NULL);
      break;
    case MOUSE_DRAG:
      if (!pointAdded) {
        break;
      }
      polygonPoints[polygonPointCount - 1] = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                  drawpixel, NULL);
      break;
    case MOUSE_RELEASE:
      if (!pointAdded) {
        break;
      }
      polygonPoints[polygonPointCount - 1] = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                  drawpixel, NULL);
      markPoints(polygonPoints, polygonPointCount);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      // find the point that has the minimum distance
      Vector2 mousePoint = editordata->clampedMousePos;
      Vector2 *minPoint = &polygonPoints[0];
      float minDistance = getVectorDistance(polygonPoints[0], mousePoint);
      for (size_t i = 1; i < polygonPointCount; i++) {
        float distance = getVectorDistance(polygonPoints[i], mousePoint);
        if (distance < minDistance) {
          minDistance = distance;
          minPoint = &polygonPoints[i];
        }
      }
      printf("minDistance: %f\n", minDistance);
      if (minDistance < editToleration) {
        printf("Chosen point");
        editPoint = minPoint;
      } else {
        editPoint = NULL;
      }
      break;

    case MOUSE_DRAG:
      if (editPoint != NULL) {
        *editPoint = editordata->clampedMousePos;
        ClearBackground(WHITE);
        drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                    drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawPolygon(polygonPoints, polygonPointCount, &editordata->editorColor,
                  drawpixel, NULL);
      markPoints(polygonPoints, polygonPointCount);
      break;
    }
    break;
  }
}
// point1 .. start of square
// point2 .. end of square
void square_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    ClearBackground(WHITE);
    drawSquare(&point1, &point2, &editordata->editorColor, pixelBuffer_setPixel,
               buffer);
    break;
  case KEY_ESCAPE:
    ClearBackground(WHITE);
    invalidatePoint(&point1);
    invalidatePoint(&point2);
    break;
  }
}
void square_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                          EditorData *editordata) {
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      point1 = editordata->clampedMousePos;
      point2 = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawSquare(&point1, &point2, &editordata->editorColor, drawpixel, NULL);
      break;
    case MOUSE_DRAG:
      point2 = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawSquare(&point1, &point2, &editordata->editorColor, drawpixel, NULL);
      break;
    case MOUSE_RELEASE:
      point2 = editordata->clampedMousePos;
      ClearBackground(WHITE);
      drawSquare(&point1, &point2, &editordata->editorColor, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      Vector2 mousePos = editordata->clampedMousePos;
      float distance = getVectorDistance(mousePos, point1);
      float distance2 = getVectorDistance(mousePos, point2);
      if (fmin(distance, distance2) < editToleration) {
        editPoint = distance > distance2 ? &point2 : &point1;
      } else {
        editPoint = NULL;
      }
      break;

    case MOUSE_DRAG:
      if (editPoint != NULL) {
        *editPoint = editordata->clampedMousePos;
        ClearBackground(WHITE);
        drawSquare(&point1, &point2, &editordata->editorColor, drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawSquare(&point1, &point2, &editordata->editorColor, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
  }
}
void eraser_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                          EditorData *editordata) {
  Vector2 mousePos = editordata->clampedMousePos;
  int size = editordata->size;
  ClearBackground(WHITE);
  Vector2 point1 = (Vector2){mousePos.x - size / 2., mousePos.y - size / 2.};
  Vector2 point2 = (Vector2){mousePos.x + size / 2., mousePos.y + size / 2.};
  drawSquare(&point1, &point2, editPointColor, drawpixel, NULL);
  if (mouseEvent == MOUSE_IDLE)
    return;
  for (int x = point1.x; x < point2.x; x++)
    for (int y = point1.y; y < point2.y; y++)
      pixelBuffer_setPixel(x, y, (Color){0, 0, 0, 0}, buffer);
}
void eraser_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  return;
}
static void fill(int startX, int startY, pixelBuffer *buffer,
                 EditorData *editordata) {
  if (startX < 0 || startX >= PIXELBUFFER_WIDTH || startY < 0 ||
      startY >= PIXELBUFFER_HEIGHT)
    return;

  Color targetColor = buffer->mainBuffer[startY][startX];
  Color fillColor = editordata->editorColor;

  // Early exit if starting pixel is already filled or not the target
  if (ColorIsEqual(buffer->mainBuffer[startY][startX], fillColor) ||
      !ColorIsEqual(buffer->mainBuffer[startY][startX], targetColor))
    return;

  Vector2 *queue =
      malloc(PIXELBUFFER_WIDTH * PIXELBUFFER_HEIGHT * sizeof(Vector2));
  int front = 0, rear = 0;

  // Enqueue starting point and mark it immediately
  queue[rear++] = (Vector2){startX, startY};
  pixelBuffer_setPixel(startX, startY, fillColor, buffer);

  // Neighbor offsets: right, left, up, down
  const int dx[] = {1, -1, 0, 0};
  const int dy[] = {0, 0, -1, 1};

  while (front < rear) {
    Vector2 current = queue[front++];

    // Check all 4 neighbors
    for (int i = 0; i < 4; i++) {
      int newX = current.x + dx[i];
      int newY = current.y + dy[i];

      if (newX < 0 || newX >= PIXELBUFFER_WIDTH || newY < 0 ||
          newY >= PIXELBUFFER_HEIGHT)
        continue;

      if (ColorIsEqual(buffer->mainBuffer[newY][newX], targetColor)) {
        pixelBuffer_setPixel(newX, newY, fillColor, buffer);
        queue[rear++] = (Vector2){newX, newY};
      }
    }
  }

  free(queue);
}
void filler_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer,
                          EditorData *editordata) {
  Vector2 mousePos = editordata->clampedMousePos;
  if (mouseEvent == MOUSE_PRESS && mouseButton == MOUSE_LEFT_BUTTON)
    fill(mousePos.x, mousePos.y, buffer, editordata);
}
void filler_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  return;
}
