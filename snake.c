//
// Created by azazo1 on 2023/12/19.
//

#include <malloc.h>
#include <stdlib.h>
#include "snake.h"

/**
 * 初始化蛇的头部信息
 * */
void initSnake() {
    gameInfo.nodeLength = 1; // 暂时是1，待会变
    head.direction = RIGHT;
    head.next = NULL;
    head.loc = getLoc(INITIAL_SNAKE_LENGTH - 1, 0);
    for (int i = 0; i < INITIAL_SNAKE_LENGTH - 1; ++i) {
        appendSnakeNode();
    }
}

/**
 * 在gameGraph上绘制蛇身
 * */
void drawSnake() {
    SnakeNode *node = &head;
    for (int i = 0; i < gameInfo.nodeLength; ++i, node = node->next) {
        char ch;
        switch (node->direction) {
            case UP:
                ch = '^';
                break;
            case DOWN:
                ch = 'v';
                break;
            case LEFT:
                ch = '<';
                break;
            case RIGHT:
                ch = '>';
                break;
        }
        gameGraph[node->loc.y][node->loc.x] = ch;
    }
}

/**
 * 添加蛇尾节点
 * */
void appendSnakeNode() {
    int x, y;
    SnakeNode *last = &head;
    SnakeNode *newNode = (SnakeNode *) malloc(sizeof(SnakeNode));
    for (int i = 0; i < gameInfo.nodeLength - 1; ++i, last = last->next);
    last->next = newNode;
    // 注意以下都是反向接上的，如原末尾节点向右则在左侧添加一个节点
    switch (last->direction) {
        case LEFT: {
            x = last->loc.x + 1;
            y = last->loc.y;
            break;
        }
        case RIGHT: {
            x = last->loc.x - 1;
            y = last->loc.y;
            break;
        }
        case UP: {
            x = last->loc.x;
            y = last->loc.y + 1;
            break;
        }
        case DOWN: {
            x = last->loc.x;
            y = last->loc.y - 1;
            break;
        }
    }
    newNode->loc = getLoc(x, y);
    newNode->next = NULL;
    newNode->direction = last->direction;
    gameInfo.nodeLength++;
}

void moveSnake() {
    SnakeNode *node = &head;
    enum Direction preNodeDirection = head.direction;
    enum Direction tmp;
    for (int i = 0; i < gameInfo.nodeLength; ++i, node = node->next) {
        switch (node->direction) { // 移动
            case UP: {
                node->loc.y--;
                break;
            }
            case DOWN: {
                node->loc.y++;
                break;
            }
            case LEFT: {
                node->loc.x--;
                break;
            }
            case RIGHT: {
                node->loc.x++;
                break;
            }
        }
        // 继承方向改变
        tmp = node->direction;
        node->direction = preNodeDirection;
        preNodeDirection = tmp;
    }
}

bool inSnake(Location loc) {
    SnakeNode *node = head.next;
    for (int i = 0; i < gameInfo.nodeLength-1; ++i, node = node->next) {
        if (loc.x == node->loc.x) {
            if (loc.y == node->loc.y) {
                return true;
            }
        }
    }
    return false;
}