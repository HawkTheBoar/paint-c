#include "input-handling/handle-input.h"
#include "definitions.h"
#include "editordata.h"
#include "input-handling/handlers.h"
#include "pixelBuffer/pixelBuffer.h"
#include "raylib.h"
#include "stdio.h"
typedef void (*key_handler_func)(int key, pixelBuffer *buffer,
                                 EditorData *editordata);
typedef void (*mouse_handler_func)(int mouseButton, int mouseEvent,
                                   pixelBuffer *buffer, EditorData *editordata);
typedef struct {
  key_handler_func key_handler;
  mouse_handler_func mouse_handler;
} handler;

key_handler_func key_handler;
mouse_handler_func mouse_handler;

handler handlers[] = {{line_key_handler, line_mouse_handler},
                      {circle_key_handler, circle_mouse_handler},
                      {polygon_key_handler, polygon_mouse_handler},
                      {square_key_handler, square_mouse_handler},
                      {eraser_key_handler, eraser_mouse_handler},
                      {filler_key_handler, filler_mouse_handler}};
void handle_input(pixelBuffer *pixelBuffer, EditorData *editordata) {
  int key = GetKeyPressed();
  key_handler = handlers[editordata->currentInputHandler].key_handler;
  mouse_handler = handlers[editordata->currentInputHandler].mouse_handler;
  // key overrides for all input
  int handler_count = sizeof(handlers) / sizeof(handler) - 1;
  switch (key) {
  case KEY_SPACE:
    editordata->shouldSnap = !editordata->shouldSnap;
    return;
  case KEY_C:
    pixelBuffer_clear(pixelBuffer);
    ClearBackground(WHITE);
    return;
  case KEY_ONE:
    if (editordata->currentInputHandler + 1 > handler_count)
      return;
    switch_handler(editordata, editordata->currentInputHandler + 1);
    printf("CURRENT HANDLER: %d\n", editordata->currentInputHandler);
    return;
  case KEY_TWO:
    if (editordata->currentInputHandler - 1 < 0)
      return;
    switch_handler(editordata, editordata->currentInputHandler - 1);
    printf("CURRENT HANDLER: %d\n", editordata->currentInputHandler);
    return;
  case KEY_P:
    if (editordata->size + 1 > MAX_EDITOR_SIZE)
      return;
    editordata->size += 1;
    return;
  case KEY_M:
    if (editordata->size - 1 <= 0)
      return;
    editordata->size -= 1;
    return;
  }
  // Handle key input
  key_handler(key, pixelBuffer, editordata);

  // This is so that i can use mouse events as switch state
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_PRESS, pixelBuffer, editordata);
  } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_PRESS, pixelBuffer, editordata);
  } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_RELEASE, pixelBuffer, editordata);
  } else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_RELEASE, pixelBuffer, editordata);
  } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_DRAG, pixelBuffer, editordata);
  } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    mouse_handler(MOUSE_RIGHT_BUTTON, MOUSE_DRAG, pixelBuffer, editordata);
  } else {
    mouse_handler(MOUSE_LEFT_BUTTON, MOUSE_IDLE, pixelBuffer, editordata);
  }
}
