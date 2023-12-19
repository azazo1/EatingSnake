//
// Created by azazo1 on 2023/12/19.
//

#ifndef EATINGSNAKE_SNAKE_H
#define EATINGSNAKE_SNAKE_H

#include "basic.h"

enum Direction {
    LEFT, UP, DOWN, RIGHT
};

typedef struct SnakeNode {
    Location loc;
    struct SnakeNode *next;
    enum Direction direction; // 存在意义：每次移动时将一个节点的移动方向继承到下一个节点，降低了计算的麻烦性
} SnakeNode;

SnakeNode head;

/**
 * 初始化蛇的头部信息
 * */
void initSnake();

/**
 * 在gameGraph上绘制蛇身
 * */
void drawSnake();

/**
 * 添加蛇尾节点
 * */
void appendSnakeNode();

/**
 * 蛇移动
 * */
void moveSnake();

/**
 * 检查该位置是否在蛇身内(不判断蛇头)
 * */
bool inSnake(Location loc);

#endif //EATINGSNAKE_SNAKE_H
