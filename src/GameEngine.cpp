
#include "GameEngine.hpp"
#include <cstdlib>
#include <ctime>

GameEngine::GameEngine(int width, int height)
    : width(width), height(height), score(0), gameOver(false), currentDirection(Direction::RIGHT) {
    // Initialize the snake's starting position
    snake.push_back({width / 2, height / 2});

    // Seed the random number generator to spawn food randomly
    std::srand(std::time(nullptr));
    SpawnFood();
}

void GameEngine::Step() {
    if (!gameOver) {
        MoveSnake();     // Move the snake according to the current direction
        CheckCollision(); // Check for collisions (self or walls)
    }
}

void GameEngine::ChangeDirection(Direction newDir) {
    // Prevent reversing direction directly
    if ((currentDirection == Direction::UP && newDir != Direction::DOWN) ||
        (currentDirection == Direction::DOWN && newDir != Direction::UP) ||
        (currentDirection == Direction::LEFT && newDir != Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && newDir != Direction::LEFT)) {
        currentDirection = newDir;
    }
}

void GameEngine::MoveSnake() {
    // Calculate the new head position based on the current direction
    Position newHead = snake.front();
    switch (currentDirection) {
        case Direction::UP:    newHead.y -= 1; break;
        case Direction::DOWN:  newHead.y += 1; break;
        case Direction::LEFT:  newHead.x -= 1; break;
        case Direction::RIGHT: newHead.x += 1; break;
    }

    // Insert the new head position to the front of the snake
    snake.insert(snake.begin(), newHead);

    // Check if the snake has eaten the food
    if (newHead.x == food.x && newHead.y == food.y) {
        score++;
        SpawnFood(); // Generate new food if snake eats the current one
    } else {
        // If no food was eaten, remove the tail (standard snake movement)
        snake.pop_back();
    }
}

void GameEngine::CheckCollision() {
    Position head = snake.front();
    
    // Check if the snake hits the walls
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
        gameOver = true;
    }

    // Check if the snake hits itself
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].x == head.x && snake[i].y == head.y) {
            gameOver = true;
            break;
        }
    }
}

void GameEngine::SpawnFood() {
    // Generate a random position for the food within the game bounds
    food.x = std::rand() % width;
    food.y = std::rand() % height;
}
