#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
typedef struct {
  Texture2D *texture;
  Rectangle bounds;
  int posX;
  int posY;
  char *name;
} Button;
Button *button_create(int posX, int posY, char *sprite_src, char *name);
void button_destroy(Button *button);
int button_is_clicked(Button *button);
void button_draw(Button *button);
#endif // !BUTTON_H
