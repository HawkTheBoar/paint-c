#include "input-handling/handle-ui.h"
#include "button/button.h"
#include "editordata.h"
#include "input-handling/handlers.h"
#include <string.h>
typedef enum {
  BUTTON_CIRCLE,
  BUTTON_SQUARE,
  BUTTON_LINE,
  BUTTON_DOTTEDLINE,
  BUTTON_ERASER,
  BUTTON_POLYGON,
  BUTTON_BUCKET,
  NUM_BUTTONS // (Optional: Helps track total buttons)
} ButtonID;
Button *all_buttons[NUM_BUTTONS]; // Global array

void handle_ui_init() {
  all_buttons[BUTTON_CIRCLE] =
      button_create(-1, -1, "sprites/circle.png", "circle");
  all_buttons[BUTTON_SQUARE] =
      button_create(-1, -1, "sprites/square.png", "square");
  all_buttons[BUTTON_LINE] = button_create(-1, -1, "sprites/line.png", "line");
  all_buttons[BUTTON_DOTTEDLINE] =
      button_create(-1, -1, "sprites/dashed-line.png", "dashed-line");
  all_buttons[BUTTON_ERASER] =
      button_create(-1, -1, "sprites/eraser.png", "eraser");
  all_buttons[BUTTON_POLYGON] =
      button_create(-1, -1, "sprites/polygon.png", "polygon");
  all_buttons[BUTTON_BUCKET] =
      button_create(-1, -1, "sprites/bucket.png", "bucket");

  // Set positions
  const int totalWidth = (32 + 2) * 10 - 2;
  const int startX = (800 - totalWidth) / 2;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    Button *current = all_buttons[i];
    current->posX = startX + i * (32 + 2);
    current->posY = 725;
    current->bounds =
        (Rectangle){current->posX, current->posY, current->texture->width,
                    current->texture->height};
  }
}
void handle_ui(EditorData *editordata) {
  for (ButtonID i = 0; i != NUM_BUTTONS; i++) {
    Button *current = all_buttons[i];
    button_draw(current);
    if (button_is_clicked(current)) {
      switch (i) {
      case BUTTON_CIRCLE:
        switch_handler(editordata, 1);
        break;
      case BUTTON_SQUARE:
        switch_handler(editordata, 3);
        break;
      case BUTTON_LINE:
        editordata->isDotted = 0;
        switch_handler(editordata, 0);
        break;
      case BUTTON_DOTTEDLINE:
        editordata->isDotted = 1;
        switch_handler(editordata, 0);
        break;
      case BUTTON_ERASER:
        switch_handler(editordata, 4);
        break;
      case BUTTON_POLYGON:
        switch_handler(editordata, 2);
        break;
      case BUTTON_BUCKET:
        switch_handler(editordata, 5);
        break;
      default:
        break;
      }
    }
  }
  const Color palette[] = {RED,  ORANGE, YELLOW, GREEN, SKYBLUE,
                           BLUE, PURPLE, PINK,   BROWN, WHITE};

  const int swatchWidth = 32;
  const int swatchHeight = 32;
  const int startY = 767; // Position below existing buttons (725 + 25 spacing)
  const int spacing = 2;

  // Calculate total width needed and center horizontally
  const int totalWidth = (swatchWidth + spacing) * 10 - spacing;
  const int startX = (800 - totalWidth) / 2;

  // Draw and handle color swatches
  for (int i = 0; i < 10; i++) {
    Rectangle swatchRect = {startX + i * (swatchWidth + spacing), startY,
                            swatchWidth, swatchHeight};

    // Draw color swatch
    DrawRectangleRec(swatchRect, palette[i]);

    // Draw border
    DrawRectangleLinesEx(swatchRect, 1, BLACK);

    // Handle click
    if (CheckCollisionPointRec(GetMousePosition(), swatchRect) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      editordata->editorColor = palette[i];
    }
  }
}
void handle_ui_destroy() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    button_destroy(all_buttons[i]);
  }
}
