#include "tim1637_params.h"

static const TIMDisplaySrcPair DisplaySources[] = {
        {0,     0x3F},
        {1,     0x06},
        {2,     0x5B},
        {3,     0x4F},
        {4,     0x66},
        {5,     0x6D},
        {6,     0x7D},
        {7,     0x07},
        {8,     0x7F},
        {9,     0x6F},
        {'0',     0x3F},
        {'1',     0x06},
        {'2',     0x5B},
        {'3',     0x4F},
        {'4',     0x66},
        {'5',     0x6D},
        {'6',     0x7D},
        {'7',     0x07},
        {'8',     0x7F},
        {'9',     0x6F},
        {'a',     0x77},
        {'b',     0x7C},
        {'c',     0x58},
        {'d',     0x5E},
        {'e',     0x79},
        {'f',     0x71},
        {'h',     0x76},
        {'l',     0x38},
        {'n',     0x54},
        {'p',     0x73},
        {'u',     0x3E},
        {'A',     0x77},
        {'B',     0x7C},
        {'C',     0x39},
        {'D',     0x5E},
        {'E',     0x79},
        {'F',     0x71},
        {'H',     0x76},
        {'L',     0x38},
        {'N',     0x54},
        {'P',     0x73},
        {'U',     0x3E},
        {' ',     0x00},
};

#define SRC_SIZE    (sizeof(DisplaySources)/sizeof(DisplaySources[0]))

uint8_t search_display_one(uint8_t wanna)
{
    for(int each_one = 0; each_one < SRC_SIZE; each_one++){
        if(wanna == DisplaySources[each_one].char_){
            return DisplaySources[each_one].disp_magic;
        }
    }
    return FAILED_SEARCH;
}

