
#include "GameEngine.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

GameEngine::GameEngine(int width, int height)
    : width(width), height(height), score(0), gameOver(false), steps(0), currentDirection(Direction::RIGHT)
{
    snake.push_back({width / 2, height / 2});
    std::srand(std::time(nullptr));
    SpawnFood();
}

void GameEngine::Step()
{
    if (!gameOver)
    {
        MoveSnake();
        CheckCollision();
        steps++;
    }
}

void GameEngine::ChangeDirection(Direction newDir)
{
    if ((currentDirection == Direction::UP && newDir != Direction::DOWN) ||
        (currentDirection == Direction::DOWN && newDir != Direction::UP) ||
        (currentDirection == Direction::LEFT && newDir != Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && newDir != Direction::LEFT))
    {
        currentDirection = newDir;
    }
}

void GameEngine::MoveSnake()
{
    Position newHead = snake.front();
    switch (currentDirection)
    {
        case Direction::UP:    newHead.y -= 1; break;
        case Direction::DOWN:  newHead.y += 1; break;
        case Direction::LEFT:  newHead.x -= 1; break;
        case Direction::RIGHT: newHead.x += 1; break;
    }

    snake.insert(snake.begin(), newHead);

    if (newHead.x == food.x && newHead.y == food.y)
    {
        score++;
        SpawnFood();
    }
    else
    {
        snake.pop_back(); // Standard snake movement, remove tail
    }
}

void GameEngine::CheckCollision()
{
    Position head = snake.front();
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
        gameOver = true;

    for (size_t i = 1; i < snake.size(); i++)
    {
        if (snake[i].x == head.x && snake[i].y == head.y)
        {
            gameOver = true;
            break;
        }
    }
}

void GameEngine::SpawnFood()
{
    food.x = std::rand() % width;
    food.y = std::rand() % height;
}

GameState GameEngine::GetGameState() const
{
    GameState state;
    state.steps = steps;
    state.score = score;
    state.headPosition = snake.front();
    state.tailPosition = snake.back();
    state.foodPosition = food;

    // Calculating distances
    state.distanceToFood = std::abs(snake.front().x - food.x) + std::abs(snake.front().y - food.y);
    state.distanceToLeftWall = snake.front().x;
    state.distanceToRightWall = width - snake.front().x - 1;
    state.distanceToTopWall = snake.front().y;
    state.distanceToBottomWall = height - snake.front().y - 1;

    state.currentDirection = currentDirection;
    state.isGameOver = gameOver;

    return state;
}

