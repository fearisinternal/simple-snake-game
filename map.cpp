#include <iostream>
#include <curses.h>
#include <thread>
#include "map.h"

void SnakeMap::drawMap()
{
    std::system("clear");
    for (auto i = 0; i < MAP_HEIGHT; i++)
    {
        for (auto j = 0; j < MAP_WIDTH; j++)
        {
            std::cout << " " << gameMap[i][j];
        }
        std::cout << std::endl;
    }
}

void SnakeMap::clearMap()
{
    for (auto i = 0; i < MAP_HEIGHT; i++)
    {
        for (auto j = 0; j < MAP_WIDTH; j++)
        {
            gameMap[i][j] = MAP_POINT;
        }
    }
}

void SnakeMap::createMap()
{
    clearMap();
    if (apple.first == snake.snakeParts[0].first && apple.second == snake.snakeParts[0].second)
    {
        appleIsEaten = true;
        score++;
        snake.length++;
    }
    snake.moveForward();
    drawSnake();
    UpdateApplePoint();
    gameMap[apple.first][apple.second] = APPLE;
    drawMap();
    std::cout << "Your score: " << score << std::endl;
}

void SnakeMap::UpdateApplePoint()
{
    if (appleIsEaten)
    {
        srand(time(0));
        apple.first = rand() % MAP_HEIGHT;
        apple.second = rand() % MAP_WIDTH;
        appleIsEaten = false;
    }
}

void SnakeMap::drawSnake()
{
    for (auto s : snake.snakeParts)
    {
        if (gameMap[s.first][s.second] == SNAKE_PART || gameMap[s.first][s.second] == SNAKE_HEAD)
        {
            gameOver = true;
        }
        gameMap[s.first][s.second] = SNAKE_PART;
    }
    gameMap[snake.snakeParts[0].first][snake.snakeParts[0].second] = SNAKE_HEAD;
}

void SnakeMap::startGame()
{
    std::thread keyChecker(&Snake::chooseDirection, &snake);
    keyChecker.detach();
    while (true)
    {
        if (gameOver)
        {
            break;
        }
        createMap();
        usleep(PAUSE_MOMENT);
    }
    endGame();
}

void SnakeMap::endGame()
{
    drawMap();
    std::cout << "Game Over! Your score: " << score << std::endl;
}

void SnakeMap::startScreen()
{
    do
    {
        clearMap();
        drawMap();
        std::cout << "Press Enter to start\n";
    } while (getchar() != '\n');
    startGame();
}