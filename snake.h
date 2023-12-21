#include "elements.h"
#include <vector>
#include <mutex>
#include <unistd.h>

class Snake
{
public:
    Snake();
    void moveForward();
    void chooseDirection();
    std::pair<int, int> direction{0, 1};
    std::vector<std::pair<int, int>> snakeParts;
    std::mutex m;
    bool isDead = false;
    int length = SNAKE_LENGTH;
};