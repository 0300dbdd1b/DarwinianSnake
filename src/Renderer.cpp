
#include "Renderer.hpp"

Renderer::Renderer(int screenWidth, int screenHeight, int gridSize)
    : screenWidth(screenWidth), screenHeight(screenHeight), gridSize(gridSize) {
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(10);  // Adjust FPS as necessary
}

Renderer::~Renderer() {
    CloseWindow();
}

void Renderer::Begin() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Renderer::End() {
    EndDrawing();
}

void Renderer::Render(const GameEngine& game) {
    // Draw snake
    for (const auto& segment : game.GetSnake()) {
        DrawRectangle(segment.x * gridSize, segment.y * gridSize, gridSize, gridSize, GREEN);
    }

    // Draw food
    Position food = game.GetFood();
    DrawRectangle(food.x * gridSize, food.y * gridSize, gridSize, gridSize, RED);

    // Draw score
    DrawText(TextFormat("Score: %d", game.GetScore()), 10, 10, 20, DARKGRAY);
}
