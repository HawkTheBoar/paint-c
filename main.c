#include "algorithms/algorithms.h"
#include "raylib.h"
int main() {
  // Initialize window
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "My Raylib Window");

  // Set background color (R, G, B, A) - values range from 0-255
  Color bgColor = (Color){25, 25, 40, 255}; // Dark blue-gray

  // Set target FPS (optional)
  SetTargetFPS(60);
  // Main game loop
  Vector2 point = {150, 150};
  Vector2 point2 = {500, 500};
  Vector2 point3 = {200, 300};
  Vector2 points[] = {point, point2, point3};
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(bgColor);
    // You can add more drawing here
    // drawLine(&point2, &point3, &BLACK, DrawPixel);
    //    drawPolygon(points, 3, &BLACK, DrawPixel);
    drawSquare(&point, &point2, &BLACK, DrawPixel);
    EndDrawing();
  }

  // Cleanup
  CloseWindow();
  return 0;
}
