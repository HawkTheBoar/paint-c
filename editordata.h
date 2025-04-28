#ifndef EDITORDATA_H
#define EDITORDATA_H
#include "raylib.h"
typedef struct {
  Color editorColor;
  int currentInputHandler;
  Vector2 clampedMousePos;
} EditorData;
#endif // !EDITORDATA_H
