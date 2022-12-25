#include "config.h"
#include "clog.h"
#include "common.h"

#define _TIMER_DEBUG
#ifdef _TIMER_DEBUG
#define timer_log_e QPLOG_ERR
#define timer_log_w	QPLOG_WAR
#define timer_log_d	QPLOG_DEB
#else
#define timer_log_e(fmt, ...)
#define timer_log_w(fmt, ...)
#define timer_log_d(fmt, ...)
#endif

static struct Timer g_stTimer[MAX_TIMER_NUM];

static struct Timer *pstNowTimer;
static struct Timer *pstTimer_Start;
static struct Timer *pstTimer_End;

static int CompareTimer(const struct Timer* pstTimerItem)
{
	struct Timer* pstTimer = NULL;
    if(!pstTimerItem) {
        timer_log_e("%s(in) TimerItem:error", __FUNCTION__);
        return 0;
    }

    pstTimer = pstTimer_Start;

    while(1) {
        if(pstTimerItem->pEvent == pstTimer ->pEvent) {
            return 0;
        }

        pstTimer = pstTimer->pstNextTimer;
        if((NULL == pstTimer) || (INVALID_INTERVAL == pstTimer->Interval) || (INTERVAL_MAX == pstTimer->Interval_type)) {
            break;
        }
    }
    return 1;
}
static int InsertTimerItem(const struct Timer* pstTimerItem)
{
    struct Timer* pstTimer = NULL;
    int sdRes = TIMER_SUCCESS;

    pstTimer = pstNowTimer;

    if(CompareTimer(pstTimerItem)) {
		if(pstTimer != NULL) {
            if(pstTimer->Interval == INVALID_INTERVAL) {
                pstTimer->type = pstTimerItem->type;
                pstTimer->mode = pstTimerItem->mode;
                pstTimer->Interval = pstTimerItem->Interval;
                pstTimer->Degree = pstTimerItem->Degree;
                pstTimer->pEvent = pstTimerItem->pEvent;
                pstTimer->Interval_type = pstTimerItem->Interval_type;
                pstNowTimer = pstNowTimer->pstNextTimer;
            } else {
                sdRes = 1;
            }
        } else {
            timer_log_e("%s(in) Array full", __FUNCTION__);
            sdRes = TIMER_FULL;
        }
    } else {
        sdRes = TIMER_ISEXIST;
    }
    return sdRes;
}
static void FreeTimer(struct Timer** pstP1Address, struct Timer* pstTimer, struct Timer* pstP1_Pre)
{
    struct Timer *pstP1 = *pstP1Address;
    struct Timer *pstP2;
    pstP1->type			 = MAX_TYPE;
    pstP1->mode          = MAX_TIMER_MODE; //need default invalid mode
    pstP1->Interval      = INVALID_INTERVAL;
    pstP1->Degree        = 0;
    pstP1->pEvent        = 0;
    pstP1->Interval_type = INTERVAL_MAX;

    if(pstNowTimer == NULL)
		pstNowTimer = pstP1;

    if(pstP1 == pstTimer) {
        pstTimer_Start = pstTimer_Start->pstNextTimer;
        pstP1_Pre->pstNextTimer = pstTimer_Start;
        pstP2 = pstTimer_End->pstNextTimer;
        pstTimer_End->pstNextTimer = *pstP1Address;
        pstTimer_End = *pstP1Address;
        pstTimer_End->pstNextTimer = pstP2;
        *pstP1Address = pstP1_Pre;
    } else if(pstP1->pstNextTimer != NULL) {
        pstP1_Pre->pstNextTimer = (*pstP1Address)->pstNextTimer;
        pstP2 = pstTimer_End->pstNextTimer;
        pstTimer_End->pstNextTimer = *pstP1Address;
        pstTimer_End = *pstP1Address;
        pstTimer_End->pstNextTimer = pstP2;
        *pstP1Address = pstP1_Pre;
    }
}

static int DeleteTimerByType(unsigned char bType)
{
    struct Timer *pstTimer;
    struct Timer *pstP1;
    struct Timer *pstP1_Pre;
    struct Timer stForPre;
    unsigned char bRes = 0;
    pstTimer = NULL;
    pstP1 = NULL;
    pstP1_Pre = &stForPre;
    if (bType >= MAX_TYPE)
    {
        timer_log_e("%s(in) type:error", __FUNCTION__);
        bRes = 1;
        return bRes;
    }

    pstTimer = pstTimer_Start;
    pstP1 = pstTimer;

    while(1) {
        if(bType == pstP1->type) {
            FreeTimer(&pstP1, pstTimer, pstP1_Pre);
        }
        pstP1_Pre = pstP1;
        pstP1 = pstP1->pstNextTimer;
        pstTimer = pstTimer_Start;
        if((NULL == pstP1) || (INVALID_INTERVAL == pstP1->Interval)) {
            break;
        }
    }
    return bRes;
}

static int DeleteTimerByMode(unsigned char bMode)
{
    struct Timer *pstTimer;
    struct Timer *pstP1;
    struct Timer *pstP1_Pre;
    struct Timer stForPre;
    unsigned char bRes = 0;
    pstTimer = NULL;
    pstP1 = NULL;
    pstP1_Pre = &stForPre;
    if(bMode >= MAX_TIMER_MODE) {
        timer_log_e("%s(in) Mode:error", __FUNCTION__);
        return 1;
    }
    pstTimer = pstTimer_Start;
    pstP1 = pstTimer;

    while(1) {
        if(bMode == pstP1->mode) {
            FreeTimer(&pstP1, pstTimer, pstP1_Pre);
        }
        pstP1_Pre = pstP1;
        pstP1 = pstP1->pstNextTimer;
        pstTimer = pstTimer_Start;
        if((NULL == pstP1) || (INVALID_INTERVAL == pstP1->Interval)) {
            break;
        }
    }
    return bRes;
}

static int DeleteTimerByEvent(int (*pEvent)(void))
{
    struct Timer *pstTimer;
    struct Timer *pstP1;
    struct Timer *pstP1_Pre;
    struct Timer stForPre;
    unsigned char bRes = 0;
    pstTimer = NULL;
    pstP1 = NULL;
    pstP1_Pre = &stForPre;
    if(pEvent == 0) {
        timer_log_e("%s(in) Event fuction:error", __FUNCTION__);
        return 1;
    }
    pstTimer = pstTimer_Start;
    pstP1 = pstTimer;
    while(1) {
        if(pEvent == pstP1->pEvent) {
            FreeTimer(&pstP1, pstTimer, pstP1_Pre);
        }
        pstP1_Pre = pstP1;
        pstP1 = pstP1->pstNextTimer;
        pstTimer = pstTimer_Start;
        if((pstP1 == NULL) || (pstP1->Interval == INVALID_INTERVAL)) {
            break;
        }
    }
    return bRes;
}

unsigned int GetTimerCount(void)
{
//	return TIM_GetCount(System_Timer_Type_3);
	return 0;
}

void TimerInit(void)
{
    struct Timer *pstTimerItem;
    int i;

//	TIM_Init(System_Timer_Type_3, 5000, 8000, timer_callback);
    
	pstTimerItem = g_stTimer;
    pstTimer_Start = g_stTimer;
    pstNowTimer = g_stTimer;
    pstTimer_End = &g_stTimer[MAX_TIMER_NUM - 1];
    for(i = 0; i < MAX_TIMER_NUM; i++) {
        pstTimerItem->type = MAX_TYPE;
        pstTimerItem->mode          = MAX_TIMER_MODE; //need default invalid mode
        pstTimerItem->Interval      = INVALID_INTERVAL;
        pstTimerItem->Degree        = 0;
        pstTimerItem->pEvent        = 0;
        pstTimerItem->Interval_type = INTERVAL_MAX;
        if(i == (MAX_TIMER_NUM - 1)) {
            pstTimerItem->pstNextTimer = NULL;
        } else {
            pstTimerItem->pstNextTimer = &g_stTimer[i + 1];
        }
        pstTimerItem++;
    }
}

void TimerDelete(int sdType, int sdSubType, int (*pEvent)(void))
{
    switch (sdType)
    {
    case TYPE:
        DeleteTimerByType(sdSubType);
        break;
    case MODE:
        DeleteTimerByMode(sdSubType);
        break;
    case EVENT:
        DeleteTimerByEvent(pEvent);
        break;
    default:
        timer_log_e("%s(in) sdType:error", __FUNCTION__);
        break;
    }
}

int CheckTimer(uint16_t dInterval_type)
{
    struct Timer *pstTimer;
    struct Timer *pstP1;
    struct Timer *pstP1_Pre;
    struct Timer  stForPre;
    int sdResPEvent = 0;
    int sdRes = 0;
    pstTimer = NULL;
    pstP1 = NULL;
    pstP1_Pre = &stForPre;
    pstTimer = pstTimer_Start;
    pstP1 = pstTimer;
    while(pstP1 != NULL) {
        if(pstP1->Interval != INVALID_INTERVAL) {
            if(pstP1->Interval_type == dInterval_type) {
                pstP1->Degree++;
                if(pstP1->Degree >= pstP1->Interval) {
                    if(pstP1->pEvent) {
                        sdResPEvent = pstP1->pEvent();
                    } else {
                        FreeTimer(&pstP1, pstTimer, pstP1_Pre);
                    }

                    if(ONE_TIME == pstP1->mode) {
                        FreeTimer(&pstP1, pstTimer, pstP1_Pre);
                    } else if(MULTI_TIME == pstP1->mode) {
                        pstP1->Degree = 0;
                    } else if(EXECUTE_BY_CONDITION == pstP1->mode) {
                        if(sdResPEvent) {
                            FreeTimer(&pstP1, pstTimer, pstP1_Pre);
                        } else {
                            pstP1->Degree = 0;
                        }
                    } else {
                        sdRes = 1;
                        timer_log_d("%s(in) mode invalid error", __FUNCTION__);
                    }
                }
            }
        } else {
            sdRes = 1;
            break;
        }
        pstP1_Pre = pstP1;
        pstP1 = pstP1->pstNextTimer;
        pstTimer = pstTimer_Start;
    }
    return sdRes;
}

int TimerInsert(uint8_t bMode, uint8_t bType, uint16_t dInterval, uint16_t dDegree, int (*pEvent)(void), uint16_t dInterval_type)
{
    int dRes = TIMER_SUCCESS;
    struct Timer *pstTimer;
    struct Timer stTimerItem;
    pstTimer = &stTimerItem;
    pstTimer->type = bType;
    pstTimer->mode = bMode;
    pstTimer->Interval = dInterval;
    pstTimer->Degree = dDegree;
    pstTimer->pEvent = pEvent;
    pstTimer->Interval_type = dInterval_type;
    if((pstTimer->type < MAX_TYPE)
            && (pstTimer->mode < MAX_TIMER_MODE)
            && (pstTimer->pEvent != 0)
            && (pstTimer->Degree <= pstTimer->Interval)
            && (pstTimer->Interval_type < INTERVAL_MAX)) {
		dRes = InsertTimerItem(pstTimer);
    } else {
        dRes = TIMER_ERR;
        timer_log_e("%s(in) AddTimerItem invalid", __FUNCTION__);
    }
    return dRes;
}
int TimerReset(int (*pEvent)(void))
{
    int dRes = TIMER_ERR;
    struct Timer *pstTimer;
    pstTimer = pstTimer_Start;

    while(1) {
        if(pEvent == pstTimer ->pEvent) {
            pstTimer->Degree = 0;
            dRes = TIMER_SUCCESS;
            break;
        }

        pstTimer = pstTimer->pstNextTimer;
        if((NULL == pstTimer) || (INVALID_INTERVAL == pstTimer->Interval) || (INTERVAL_MAX == pstTimer->Interval_type)) {
            break;
        }
    }

    return dRes;
}

int CheckTimerExist(int (*pEvent)(void))
{
    struct Timer *pstP1;
    unsigned char bRes = 0;
    pstP1 = NULL;
    pstP1 = pstTimer_Start;
    while(1) {
        if(pEvent == pstP1->pEvent) {
            return 1;
        }
        if(pstP1 == pstTimer_End) {
			break;
        }
        pstP1 = pstP1->pstNextTimer;
    }
    return bRes;
}

void PrintfTimerItemArray(void)
{
    timer_log_d("\n\rBelow are g_stTimer[i]");
    for(int i = 0; i < MAX_TIMER_NUM; i++) {
        timer_log_d("g_stTimer[%d] address is %x", i, &g_stTimer[i]);
        timer_log_d("g_stTimer[%d].Interval=%x", i, g_stTimer[i].Interval);
        timer_log_d("g_stTimer[%d].Degree=%x", i, g_stTimer[i].Degree);
        timer_log_d("g_stTimer[%d].mode=%x", i, g_stTimer[i].mode);
        timer_log_d("g_stTimer[%d].type=%x", i, g_stTimer[i].type);
        timer_log_d("g_stTimer[%d].Interval_type=%x", i, g_stTimer[i].Interval_type);
        timer_log_d("g_stTimer[%d].pEvent=%x", i, g_stTimer[i].pEvent);
        timer_log_d("next_pointer:%x,start:%x", g_stTimer[i].pstNextTimer, pstTimer_Start);
    }
    timer_log_d(PRINTF_END_TAG);
}
