#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
struct Button {
  Vector2 position;
  Vector2 size;
  char *text;
};
#endif // !BUTTON_H
