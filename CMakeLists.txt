cmake_minimum_required(VERSION 3.22)
project(snake_game)

add_executable(snake_game 
            elements.h
            snake.h
            snake.cpp
            map.h
            map.cpp
            main.cpp)
target_include_directories(snake_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(snake_game curses)
