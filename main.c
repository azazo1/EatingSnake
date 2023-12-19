#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"
#include "schedule.h"
#include "snake.h"
#include "food.h"

#define DEBUG

void initGameInfo() {
    gameInfo.state = PREGAME;
    gameInfo.rst = -1;
    gameInfo.nodeLength = 0;
#ifdef DEBUG
    gameInfo.randSeed = 1;
#else
    gameInfo.randSeed = (unsigned int) getTime();
#endif
}

/**
 * 清空gameGraph内容
 * 此操作不会反映到屏幕上
 * */
void clearGraphBuffer() {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            gameGraph[i][j] = ' ';
        }
    }
}

/**
 * 更新gameGraph
 * */
void updateGraphBuffer() {
    drawSnake();
    drawFood();
}

/**
 * 将gameGraph显示到屏幕上，
 * 注意，除了此函数，其他所有函数不会改变显示输出
 * */
void showGraph() {
    system("cls");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            printf("%c", gameGraph[i][j]);
        }
        printf("\n");
    }
}

/**
 * 显示游戏开始前的提示语
 * */
void showPregameMessage() {
    printf("%s", preGameGraph);
    printf("%s", tutorial);
}

/**
 * 闪烁这一行
 * */
void flickerLine() {
    static bool show = true;
    if (show) {
        printf("\r----------------------------------------------------------");
    } else {
        printf("\r**********************************************************"); // 58 chars
    }
    show = !show;
}

/**
 * 显示一行波纹
 * */
void wave() {
    static char right[27] = {'>','>','>','-','-','-','>','>','>','-','-','-','>','>','>','-','-','-','>','>','>','-','-','-','>','>','>'};
    static char left[27] = {'<','<','<','-','-','-','<','<','<','-','-','-','<','<','<','-','-','-','<','<','<','-','-','-','<','<','<'};
    char leftFirst = left[0];
    char rightLast = right[26];
    for (int i = 0; i < 26; ++i) {
        left[i] = left[i + 1];
    }
    for (int i = 25; i >= 0; --i) {
        right[i + 1] = right[i];
    }
    left[26] = leftFirst;
    right[0] = rightLast;
    printf("\r");
    for (int i = 0; i < 27; ++i) {
        printf("%c", left[i]);
    }
    printf("[SPACE]");
    for (int i = 0; i < 27; ++i) {
        printf("%c", right[i]);
    }
}

/**
 * 游戏开始前等待
 * */
void waitForStart() {
    Schedule schedule;
    initLoopSchedule(&schedule, 0, 16, wave);
    while (1) {
        if (checkSchedule(&schedule)) { // 闪烁这一行
            triggerSchedule(&schedule);
        }
        if (kbhit()) {
            if (getch() == ' ') { // 此循环等待空格按下
                break;
            }
        }
        Sleep(60);
    }
    cancelSchedule(&schedule);
}

/**
 * 处理蛇头吃食物
 * */
void handleFoodEat() {
    int x = head.loc.x;
    int y = head.loc.y;
    if (x == food.loc.x) {
        if (y == food.loc.y) {
            appendSnakeNode();
            do {
                refreshFood();
            } while (inSnake(food.loc));
        }
    }
}

/**
 * 处理蛇头超出地图边界
 * */
void handleCrossBorder() {
    int x = head.loc.x;
    int y = head.loc.y;
    if (0 <= x && x <= MAP_SIZE) {
        if (0 <= y && y <= MAP_SIZE) {
            return;
        }
    }
    gameInfo.state = GAME_OVER;
}

/**
 * 处理蛇头撞到蛇身
 * */
void handleEatSelf() {
    if (inSnake(head.loc)) {
        gameInfo.state = GAME_OVER;
    }
}

bool inputPending = false;

/**
 * 更新游戏状态并显示画面
 * */
void update() {
    inputPending = false;
    moveSnake();
    handleCrossBorder();
    handleEatSelf();
    handleFoodEat();
    clearGraphBuffer();
    updateGraphBuffer();
    showGraph();
}


/**
 * 处理用户输入:
 * Space：暂停游戏，若检测到Space按下则进入字符读取循环，直到Space再次按下
 * WASD：改变蛇头方向
 * */
void handleInput() {
    static enum Direction rawDirection = RIGHT; // 储存在蛇移动后的方向(未被按键更改过
    if (inputPending == false) {
        rawDirection = head.direction;
    }
    if (kbhit()) {
        int get = getch();
        switch (get) {
            case 'w': {
                if (rawDirection != DOWN) {
                    head.direction = UP;
                }
                inputPending = true;
                break;
            }
            case 'a': {
                if (rawDirection != RIGHT) {
                    head.direction = LEFT;
                }
                inputPending = true;
                break;
            }
            case 's': {
                if (rawDirection != UP) {
                    head.direction = DOWN;
                }
                inputPending = true;
                break;
            }
            case 'd': {
                if (rawDirection != LEFT) {
                    head.direction = RIGHT;
                }
                inputPending = true;
                break;
            }
            case ' ': {
                while (getch() != ' '); // 再次等待空格按下恢复游戏
                inputPending = true;
                break;
            }
            case 'q': {
                gameInfo.state = GAME_OVER;
                inputPending = true;
                break;
            }
            default: {
            }
        }
    }
}

void showGameRst() {
    system("cls");
    printf("%s", gameOverGraph);
    printf("Your Score Is %d, press Space to quit.", gameInfo.nodeLength);
    while (getch() != ' '); // 空格结束游戏
}

void gameLoop() {
    initGameInfo();
    showPregameMessage();
    waitForStart();
    gameInfo.state = GAMING;
    srand(gameInfo.randSeed);
    clearGraphBuffer(); // 清空显示缓存
    initSnake();
    refreshFood();
    Schedule updateSch;
    initLoopSchedule(&updateSch, 0, SNAKE_MOVE_INTERVAL, update);
    while (gameInfo.state == GAMING) {
        handleInput();
        if (checkSchedule(&updateSch)) {
            triggerSchedule(&updateSch);
        }
        Sleep(10);
    }
    showGameRst();
}

int main() {
    gameLoop();
}
