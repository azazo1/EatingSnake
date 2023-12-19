cmake_minimum_required(VERSION 3.26)
project(EatingSnake C)

set(CMAKE_C_STANDARD 11)

add_executable(EatingSnake main.c
        main.h
        schedule.c
        schedule.h
        my_time.c
        my_time.h
        snake.c
        snake.h
        basic.c
        basic.h
        food.c
        food.h
)
