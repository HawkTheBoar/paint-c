#include "button/button.h"
#include "definitions.h"
#include "editordata.h"
#include "input-handling/handle-input.h"
#include "input-handling/handle-ui.h"
#include "pixelBuffer/pixelBuffer.h"
#include "raylib.h"
#include "utils/utils.h"
int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
  // Set target FPS (optional)
  SetTargetFPS(60);

  pixelBuffer *buffer = pixelBuffer_create();
  // Set the background to be White at the start.

  BeginDrawing();
  ClearBackground(WHITE);
  EndDrawing();
  // Main game loop
  Texture2D bufferTexture;
  EditorData editorData = {BLACK, 0, (Vector2){0, 0}, false, 0, 0, 5};
  handle_ui_init();
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // normalize the mousePosition
    Vector2 mousePos = GetMousePosition();
    editorData.isOutOfBounds = !isPointValid(mousePos);
    editorData.clampedMousePos =
        (Vector2){clamp(mousePos.x, 0, PIXELBUFFER_WIDTH),
                  clamp(mousePos.y, 0, PIXELBUFFER_HEIGHT)};
    // Update the bufferTexture if change
    if (buffer->hasChanged) {
      UnloadTexture(bufferTexture);
      Image bufferImage = {.data = buffer->mainBuffer,
                           .width = (SCREEN_WIDTH),
                           .height = (SCREEN_HEIGHT),
                           .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
                           .mipmaps = 1};
      bufferTexture = LoadTextureFromImage(bufferImage);
      buffer->hasChanged = 0;
    }

    BeginDrawing();
    // Draw
    DrawTexture(bufferTexture, 0, 0, WHITE);
    handle_ui(&editorData);
    handle_input(buffer, &editorData);
    // You can add more drawing here
    EndDrawing();
  }

  // Cleanup
  handle_ui_destroy();
  pixelBuffer_destroy(buffer);
  CloseWindow();
  return 0;
}
