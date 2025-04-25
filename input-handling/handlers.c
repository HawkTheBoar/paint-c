#include "handlers.h"
#include "algorithms/algorithms.h"
#include "definitions.h"
#include "editordata.h"
#include "pixelBuffer/pixelBuffer.h"
#include "utils/utils.h"
#include <math.h>
#include <raylib.h>
#define drawpixel (drawPixel_func) DrawPixel
static Vector2 point1 = {-1, -1}, point2 = {-1, -1};
static void invalidatePoint(Vector2 *p) {
  p->x = -1;
  p->y = -1;
};
static int editToleration = 10;
static Vector2 *editPoint;
static Color *editColor = &GREEN;
static Color *editPointColor = &RED;
static int editPointRadius = 5;
void markPoints(Vector2 *points, size_t count) {
  for (size_t i = 0; i < count; i++) {
    drawCircle(points + i, editPointRadius, editPointColor, drawpixel, NULL);
  }
}
void line_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    if (isPointValid(point1) && isPointValid(point2)) {
      ClearBackground(WHITE);
      drawLine(&point1, &point2, &BLACK, pixelBuffer_setPixel, buffer);
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
void line_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer) {
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      point1 = GetMousePosition();
      break;

    case MOUSE_DRAG:
      point2 = GetMousePosition();
      ClearBackground(WHITE);
      drawLine(&point1, &point2, editColor, drawpixel, NULL);
      break;

    case MOUSE_RELEASE:
      ClearBackground(WHITE);
      drawLine(&point1, &point2, editColor, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      Vector2 mousePos = GetMousePosition();
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
        *editPoint = GetMousePosition();
        ClearBackground(WHITE);
        drawLine(&point1, &point2, editColor, drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawLine(&point1, &point2, editColor, drawpixel, NULL);
      markPoints((Vector2[]){point1, point2}, 2);
      break;
    }
    break;
  }
}
// point1 ... center
// point2 ... the outer point
static float radius;
void circle_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
  switch (key) {
  case KEY_ENTER:
    if (isPointValid(point1) && isPointValid(point2)) {
      ClearBackground(WHITE);
      drawCircle(&point1, radius, &BLACK, pixelBuffer_setPixel, buffer);
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
void circle_mouse_handler(int mouseButton, int mouseEvent,
                          pixelBuffer *buffer) {
  switch (mouseButton) {
  case MOUSE_LEFT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:
      point1 = GetMousePosition();
      break;

    case MOUSE_DRAG:
      point2 = GetMousePosition();
      radius = getVectorDistance(point1, point2);
      ClearBackground(WHITE);
      drawCircle(&point1, radius, editColor, drawpixel, NULL);
      break;

    case MOUSE_RELEASE:
      ClearBackground(WHITE);
      drawCircle(&point1, radius, editColor, drawpixel, NULL);
      markPoints((Vector2[]){point1}, 1);
      break;
    }
    break;
  case MOUSE_RIGHT_BUTTON:
    switch (mouseEvent) {
    case MOUSE_PRESS:;
      Vector2 mousePos = GetMousePosition();
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
        *editPoint = GetMousePosition();
        ClearBackground(WHITE);
        // if editing the radius, recalculate it
        if (editPoint == &point2) {
          radius = getVectorDistance(point1, point2);
        }
        drawCircle(&point1, radius, editColor, drawpixel, NULL);
      }
      break;

    case MOUSE_RELEASE:
      editPoint = NULL;
      ClearBackground(WHITE);
      drawCircle(&point1, radius, editColor, drawpixel, NULL);
      markPoints((Vector2[]){point1}, 1);
      break;
    }
    break;
  }
}

void polygon_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {
}
void polygon_mouse_handler(int mouseButton, int mouseEvent,
                           pixelBuffer *buffer) {}

void square_key_handler(int key, pixelBuffer *buffer, EditorData *editordata) {}
void square_mouse_handler(int mouseButton, int mouseEvent,
                          pixelBuffer *buffer) {}
