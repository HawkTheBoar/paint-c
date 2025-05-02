#ifndef EDITORDATA_H
#define EDITORDATA_H
#include "raylib.h"
#include <stdbool.h>
typedef struct {
  Color editorColor;
  int currentInputHandler;
  Vector2 clampedMousePos;
  int shouldSnap;
  int isDotted;
  int size;
} EditorData;
#endif // !EDITORDATA_H
