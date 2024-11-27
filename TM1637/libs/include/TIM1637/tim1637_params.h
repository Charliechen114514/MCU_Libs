#pragma once

/*
    This file is gonna support the Params of TIM1637
*/

/*
    TIM1637 Support Display 6 bits, the array size shell be used
    Support settings in building :)
*/
#ifndef __SUPPORT_DISP_N
#define SUPPORT_DISP_N  (6) 
#else
#define SUPPORT_DISP_N  __SUPPORT_DISP_N
#endif

#ifndef __COLON_INDEX_N
#define COLON_INDEX_N (1)
#else
#define COLON_INDEX_N __COLON_INDEX_N
#endif

#if COLON_INDEX_N >= SUPPORT_DISP_N
#error  "Error in setting colon index! index are overflowed!"
#endif

#define COLON_DISP_MAGIC 0x80

#define SET_COLON(DISP_ARR) do{DISP_ARR[COLON_INDEX_N] |= COLON_DISP_MAGIC;}while(0)
#define OFF_COLON(DISP_ARR) do{DISP_ARR[COLON_INDEX_N] &= ~COLON_DISP_MAGIC;}while(0)

/* Minimize the includings */
typedef unsigned char uint8_t;
typedef uint8_t DisplayArray[SUPPORT_DISP_N];

/*
    Followings are struct Tables
*/
typedef struct{
    uint8_t char_;
    uint8_t disp_magic;
}TIMDisplaySrcPair;

//
#define FAILED_SEARCH       (-1)
uint8_t search_display_one(uint8_t wanna);

