#ifndef HANDLERS_H
#define HANDLERS_H
#include "raylib.h"
#define MOUSE_DRAG 1
#define MOUSE_PRESS 2
#define MOUSE_RELEASE 3
void line_key_handler(int key, Vector2 *buffer);
void line_mouse_handler(int mouseButton, int mouseEvent, Vector2 *buffer);

void circle_key_handler(int key, Vector2 *buffer);
void circle_mouse_handler(int mouseButton, int mouseEvent, Vector2 *buffer);

void polygon_key_handler(int key, Vector2 *buffer);
void polygon_mouse_handler(int mouseButton, int mouseEvent, Vector2 *buffer);

void square_key_handler(int key, Vector2 *buffer);
void square_mouse_handler(int mouseButton, int mouseEvent, Vector2 *buffer);

#endif
