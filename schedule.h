//
// Created by azazo1 on 2023/12/19.
//

#ifndef EATINGSNAKE_SCHEDULE_H
#define EATINGSNAKE_SCHEDULE_H

#include "my_time.h"
#include <stdbool.h>

typedef struct {
    time_ms_t startTime; //
    time_ms_t delay; // 距离第一次触发的时间间隔
    time_ms_t period; // 每次触发的时间间隔（若非可重复则没有用）
    time_ms_t lastTriggeredTime; // 上一次被触发的时间戳，初始为-1，用于标记第一次触发
    bool repeat; // 是否重复触发
    bool available; // 是否还有效
    void (*run)(); // 要触发的任务, 注意不要放置长时间任务
} Schedule;

/**
 * 初始化一个可重复的Schedule
 * */
void initLoopSchedule(Schedule *schedule, time_ms_t delay, time_ms_t period, void (*run)());

/**
 * 初始化一个非可重复的Schedule
 * */
void initSchedule(Schedule *schedule, time_ms_t delay, void (*run)());

/**
 * 检查Schedule是否可触发（时间到且仍有效）
 * */
bool checkSchedule(const Schedule *schedule);

/**
 * 让Schedule不再有效，以后都不会被触发
 * */
void cancelSchedule(Schedule *schedule);

/**
 * 触发一个Schedule（无论其是否有效）
 * 并：
 * 更新lastTriggeredTime
 * 若非可重复Schedule，则会将available置false
 * */
void triggerSchedule(Schedule *schedule);

#endif //EATINGSNAKE_SCHEDULE_H
