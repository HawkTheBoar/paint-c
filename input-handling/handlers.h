#ifndef HANDLERS_H
#define HANDLERS_H
#include "editordata.h"
#define MOUSE_DRAG 1
#define MOUSE_PRESS 2
#define MOUSE_RELEASE 3
#include "pixelBuffer/pixelBuffer.h"
void line_key_handler(int key, pixelBuffer *buffer, EditorData *editordata);
void line_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer);

void circle_key_handler(int key, pixelBuffer *buffer, EditorData *editordata);
void circle_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer);

void polygon_key_handler(int key, pixelBuffer *buffer, EditorData *editordata);
void polygon_mouse_handler(int mouseButton, int mouseEvent,
                           pixelBuffer *buffer);

void square_key_handler(int key, pixelBuffer *buffer, EditorData *editordata);
void square_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer);

#endif
