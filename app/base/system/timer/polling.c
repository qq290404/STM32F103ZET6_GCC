#include "config.h"
#include "common.h"

static int rtc_10ms	   = 0;
static int rtc_100ms   = 0;
static int stc_polling = 0;

static inline int ABS(int* a, int* b)
{
	int ret = 0;
	if(*a > *b) {
		ret = *a - *b;
	} else {
		ret = 100 - *b + *a;
	}
	return ret;
}
static inline int DIFF(int* nowTime, int* stcTime)
{
	return ABS(nowTime, stcTime);
}

void polling(void)
{
    int dTimenow;
	int dDiff;

    CheckTimer(INTERVAL_DIRECT);
    dTimenow = GetTimerCount();
    dDiff = DIFF(&dTimenow, &stc_polling);
    if(dDiff <= 0) {	
        return;
    } else {
        CheckTimer(INTERVAL_1MS);
        stc_polling = dTimenow;
        dTimenow = GetTimerCount();
		dDiff = ABS(&dTimenow, &rtc_10ms);
        if(dDiff >= 10) {
			//10ms
            rtc_10ms = dTimenow;
            CheckTimer(INTERVAL_10MS);
           dTimenow = GetTimerCount();
			dDiff = ABS(&dTimenow, &rtc_100ms);			
            if(dDiff >= 100) {
                CheckTimer(INTERVAL_100MS);
                rtc_100ms = dTimenow;
            }
        }
    }
}

