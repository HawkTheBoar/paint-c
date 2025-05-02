#include "button/button.h"
#include <raylib.h>
#include <stdlib.h>
Button *button_create(int posX, int posY, char *sprite_src, char *name) {
  Button *b = malloc(sizeof(Button));
  b->texture = malloc(sizeof(Texture2D));
  *b->texture = LoadTexture(sprite_src);
  b->bounds = (Rectangle){posX, posY, b->texture->width, b->texture->height};
  b->posX = posX;
  b->posY = posY;
  b->name = name;
  return b;
}
int button_is_clicked(Button *button) {
  return CheckCollisionPointRec(GetMousePosition(), button->bounds) &&
         IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
void button_draw(Button *button) {
  DrawTexture(*button->texture, button->posX, button->posY, WHITE);
}
void button_destroy(Button *button) {
  UnloadTexture(*button->texture);
  free(button->texture);
  free(button);
}
