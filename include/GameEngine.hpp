
#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Position {
    int x, y;
};

class GameEngine {
public:
    GameEngine(int width, int height);
    void Step(); // Advances the game by one tick
    void ChangeDirection(Direction newDir);
    bool IsGameOver() const { return gameOver; }
    int GetScore() const { return score; }
    std::vector<Position> GetSnake() const { return snake; }
    Position GetFood() const { return food; }

private:
    void MoveSnake();
    void CheckCollision();
    void SpawnFood();
    
    int width, height;
    int score;
    bool gameOver;
    Direction currentDirection;
    std::vector<Position> snake;
    Position food;
};

#endif // GAME_ENGINE_HPP
