#include "input-handling/handle-input.h"
#include "editordata.h"
#include "input-handling/handlers.h"
#include "pixelBuffer/pixelBuffer.h"
#include "raylib.h"
typedef void (*key_handler_func)(int key, pixelBuffer *buffer,
                                 EditorData *editordata);
typedef void (*mouse_handler_func)(int mouseButton, int mouseEvent,
                                   pixelBuffer *buffer);
typedef struct {
  key_handler_func key_hanlder;
  mouse_handler_func mouse_handler;
} handler;

key_handler_func key_handler;
mouse_handler_func mouse_handler;

handler handlers[] = {
    {line_key_handler, line_mouse_handler},
    {circle_key_handler, circle_mouse_handler},
    {polygon_key_handler, polygon_mouse_handler},
    {square_key_handler, square_mouse_handler},
};
void handle_input(pixelBuffer *pixelBuffer, EditorData *editordata) {
  int key = GetKeyPressed();
  key_handler = handlers[editordata->currentInputHandler].key_hanlder;
  mouse_handler = handlers[editordata->currentInputHandler].mouse_handler;
  // key overrides for all input
  // Handle key input
  key_handler(key, pixelBuffer, editordata);

  // This is so that i can use mouse events as switch state
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
