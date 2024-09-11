
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GameEngine.hpp"
#include "raylib.h"

class Renderer {
public:
    Renderer(int screenWidth, int screenHeight, int gridSize);
    ~Renderer();

    void Render(const GameEngine& game);  // Render function to draw the game
    void Begin();  // Starts a drawing frame
    void End();    // Ends the drawing frame

private:
    int screenWidth, screenHeight;
    int gridSize;
};

#endif // RENDERER_HPP
