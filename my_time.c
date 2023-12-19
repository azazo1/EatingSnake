//
// Created by azazo1 on 2023/12/19.
//

#include "my_time.h"
#include <windows.h>
#include <time.h>

time_ms_t getTime() {
    SYSTEMTIME tmpTime;
    GetSystemTime(&tmpTime);
    return time(NULL) * 1000 + (int64_t) tmpTime.wMilliseconds;
}