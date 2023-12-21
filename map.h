#pragma once
#include "elements.h"
#include "snake.h"
#include <iostream>
#include <thread>
#include <mutex>

class SnakeMap
{
public:
    void startScreen();
    void clearMap();
    void drawMap();
    void createMap();
    void UpdateApplePoint();
    void drawSnake();
    void startGame();
    void endGame();
    void moveSnake();

private:
    char gameMap[MAP_HEIGHT][MAP_WIDTH];
    std::pair<int, int> apple;
    bool appleIsEaten = true;
    Snake snake;
    bool gameOver = false;
    int score = 0;
    std::mutex m;
    // snake
};