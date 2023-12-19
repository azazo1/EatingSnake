//
// Created by azazo1 on 2023/12/19.
//

#ifndef EATINGSNAKE_FOOD_H
#define EATINGSNAKE_FOOD_H

#include "basic.h"

#define FOOD_CHAR '*'
typedef struct {
    Location loc;
} Food;

Food food;

/**
 * 绘制所有食物到gameGraph
 * */
void drawFood();

/**
 * 刷新食物的位置
 * */
void refreshFood();


#endif //EATINGSNAKE_FOOD_H
