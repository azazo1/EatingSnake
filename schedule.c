//
// Created by azazo1 on 2023/12/19.
//

#include "schedule.h"

void initLoopSchedule(Schedule *schedule, time_ms_t delay, time_ms_t period, void (*run)()) {
    schedule->delay = delay;
    schedule->period = period;
    schedule->run = run;
    schedule->lastTriggeredTime = -1;
    schedule->startTime = getTime();
    schedule->repeat = true;
    schedule->available = true;
}

void initSchedule(Schedule *schedule, time_ms_t delay, void (*run)()) {
    schedule->delay = delay;
    schedule->period = -1;
    schedule->run = run;
    schedule->lastTriggeredTime = -1;
    schedule->startTime = getTime();
    schedule->repeat = false;
    schedule->available = true;
}

void cancelSchedule(Schedule *schedule) {
    schedule->available = false;
}

bool checkSchedule(const Schedule *schedule) {
    Schedule tmpSch = *schedule;
    time_ms_t nowTime = getTime();
    bool check;
    if (tmpSch.repeat) {
        if (tmpSch.lastTriggeredTime == -1) {
            check = nowTime - tmpSch.startTime > tmpSch.delay;
        } else {
            check = nowTime - tmpSch.lastTriggeredTime > tmpSch.period;
        }
    } else {
        check = nowTime - tmpSch.startTime > tmpSch.delay;
    }
    return schedule->available && check;
}

void triggerSchedule(Schedule *schedule) {
    schedule->lastTriggeredTime = getTime();
    if (!schedule->repeat) {
        schedule->available = false;
    }
    schedule->run();
}