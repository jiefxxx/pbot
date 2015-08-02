#ifndef DEF_TIME_TOOLS
#define DEF_TIME_TOOLS

#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <time.h>

#define TIME_MIC 1000
#define TIME_MIL TIME_MIC*1000
#define TIME_SEC TIME_MIL*1000
#define TIME_MIN TIME_SEC*60
#define TIME_HOU TIME_MIN*60
#define TIME_DAY TIME_HOU*24

uint64_t timeStamp();

#endif
