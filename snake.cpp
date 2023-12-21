#include "snake.h"
#include <iostream>
#include <termios.h>
#include <bits/stdc++.h>
#include <stdio.h>

Snake::Snake()
{
    snakeParts.push_back({0, 2});
    snakeParts.push_back({0, 1});
    snakeParts.push_back({0, 0});

    struct termios terminal_info;
    tcgetattr(STDIN_FILENO, &terminal_info);
    terminal_info.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &terminal_info);
}

void Snake::moveForward()
{
    m.lock();
    int currentSize = snakeParts.size();
    if (currentSize < length)
    {
        snakeParts.push_back(snakeParts[currentSize - 1]);
    }
    for (auto i = currentSize - 1; i > 0; i--)
    {
        snakeParts[i] = snakeParts[i - 1];
    }
    snakeParts[0].first = (snakeParts[0].first + direction.first);
    if (snakeParts[0].first < 0)
        snakeParts[0].first = MAP_HEIGHT - 1;
    if (snakeParts[0].first >= MAP_HEIGHT)
        snakeParts[0].first = 0;

    snakeParts[0].second = (snakeParts[0].second + direction.second);
    if (snakeParts[0].second < 0)
        snakeParts[0].second = MAP_WIDTH - 1;
    if (snakeParts[0].second >= MAP_WIDTH)
        snakeParts[0].second = 0;
    m.unlock();
}

void Snake::chooseDirection()
{
    while (true)
    {
        if (isDead)
            break;
        char user_input = getchar();
        m.lock();
        switch (user_input)
        {
        case 'a':
            if (direction.first == 0 && direction.second == 1)
                break;
            direction = {0, -1};
            break;
        case 'w':
            if (direction.first == 1 && direction.second == 0)
                break;
            direction = {-1, 0};
            break;
        case 'd':
            if (direction.first == 0 && direction.second == -1)
                break;
            direction = {0, 1};
            break;
        case 's':
            if (direction.first == -1 && direction.second == 0)
                break;
            direction = {1, 0};
            break;
        case 32:
            while (getchar() != 32)
            {
                usleep(PAUSE_MOMENT);
            }
            break;
        case 13:
            isDead = true;
        default:
            break;
        }
        m.unlock();
    }
}