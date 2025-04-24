#include "handle-input.h"
#include "handlers.h"
#include "raylib.h"
#include <stdlib.h>
void (*key_handler)(int key, Vector2 *buffer);
void (*mouse_handler)(int mouseButton, int mouseEvent, Vector2 *buffer);
void handle_input(Vector2 *pixelBuffer) {
  int key = GetKeyPressed();
  if (key_handler == NULL) {
    key_handler = line_key_handler;
  }
  if (mouse_handler == NULL) {
    mouse_handler = line_mouse_handler;
  }
  key_handler(key, pixelBuffer);
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_PRESS, pixelBuffer);
  } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_PRESS, pixelBuffer);
  } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_RELEASE, pixelBuffer);
  } else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_RELEASE, pixelBuffer);
  } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_DRAG, pixelBuffer);
  } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_DRAG, pixelBuffer);
  }
}
