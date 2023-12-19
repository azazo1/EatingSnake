//
// Created by azazo1 on 2023/12/19.
//

#ifndef EATINGSNAKE_BASIC_H
#define EATINGSNAKE_BASIC_H

#include <stdbool.h>

#define MAP_SIZE 8 // 正方形地图尺寸
#define SNAKE_MOVE_INTERVAL 500 // 蛇身往前移动的间隔时间（毫秒）
#define INITIAL_SNAKE_LENGTH 3 // 蛇身初始长度

typedef struct Location {
    int x;
    int y;
} Location;

/**
 * 产生一个随机的Location
 * */
Location randomLoc();

/**
 * 根据 x 和 y 创建一个Location
 * */
Location getLoc(int x, int y);

enum GameState {
    PREGAME, GAMING, GAME_OVER
};

struct {
    enum GameState state; // 游戏状态
    int nodeLength; // 蛇身长度(包括头)
    unsigned int randSeed; // 游戏食物的随机种子
    int rst; // 最终蛇身长度
} gameInfo;

char gameGraph[MAP_SIZE][MAP_SIZE]; // 有一位用来存放\0

#endif //EATINGSNAKE_BASIC_H
