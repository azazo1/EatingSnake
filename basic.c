//
// Created by azazo1 on 2023/12/19.
//

#include "basic.h"
#include "stdlib.h"

Location randomLoc() {
    Location loc = {
            .x = rand() % MAP_SIZE,
            .y = rand() % MAP_SIZE
    };
    return loc;
}

Location getLoc(int x, int y) {
    Location loc = {
            .x = x,
            .y = y
    };
    return loc;
}