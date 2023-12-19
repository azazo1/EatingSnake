//
// Created by azazo1 on 2023/12/19.
//

#include "food.h"

void drawFood() {
    gameGraph[food.loc.y][food.loc.x] = FOOD_CHAR;
}

void refreshFood() {
    Food newFood;
    newFood.loc = randomLoc();
    food = newFood;
}