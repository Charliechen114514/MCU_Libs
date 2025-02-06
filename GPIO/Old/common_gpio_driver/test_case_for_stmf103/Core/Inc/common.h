#pragma once
/*
    Time:           2024.10.26
    Program File:   common.h
    Author:         Charliechen
    Desp:           This is the header file of Common Operations
*/

/*
    Parts of compound delay
*/

typedef struct{
    int second;
    int milisecond;
}DelayTime;
void createDelayTime(DelayTime* delayTime, int sec, int mili);
void tidyDelayTime(DelayTime* wait_tidy);
void systemGlobalDelay(DelayTime* delayTime);
