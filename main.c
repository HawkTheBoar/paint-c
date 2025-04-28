#include "algorithms/algorithms.h"
#include "definitions.h"
#include "editordata.h"
#include "input-handling/handle-input.h"
#include "pixelBuffer/pixelBuffer.h"
#include "raylib.h"
#include "utils/utils.h"
#include <stdio.h>
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
  EditorData editorData = {BLACK, 0, (Vector2){0, 0}};
  char text[100];
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Vector2 mousePos = GetMousePosition();
    editorData.clampedMousePos =
        (Vector2){clamp(mousePos.x, 0, SCREEN_HEIGHT),
                  clamp(mousePos.y, 0, SCREEN_HEIGHT - 100)};
    // Update the bufferTexture if changed
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

    // Draw
    BeginDrawing();
    sprintf(text, "x: %f y: %f", editorData.clampedMousePos.x,
            editorData.clampedMousePos.y);
    DrawText(text, 25, 25, 20, BLACK);
    handle_input(buffer, &editorData);
    DrawTexture(bufferTexture, 0, 0, WHITE);
    // You can add more drawing here
    EndDrawing();
  }

  // Cleanup
  pixelBuffer_destroy(buffer);
  CloseWindow();
  return 0;
}
