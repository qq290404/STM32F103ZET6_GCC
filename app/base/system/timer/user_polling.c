#include "config.h"
#include "common.h"

#define MAX_EVENT_NUM          8 
struct USERINPUT
{
	int type;
	int freq;
	int Degree;
	int (*pEvent)(void);
	struct USERINPUT* next;
};

static struct USERINPUT   g_stUserEvent[MAX_EVENT_NUM];
static struct USERINPUT*  pstEventHead = NULL;

static int rtc_userpolling = 0;
static int rtc_user10ms = 0;
static int rtc_user100ms = 0;

static inline int ABS(int* a, int* b)
{
	return (*a >= *b ? (*a - *b) : (*b -*a));
}
static inline int DIFF(int* nowTime, int* stcTime)
{
	*nowTime = (*nowTime)/10;
	return ABS(nowTime, stcTime);
}

static inline int CompUserEvent(int (*pEvent)(void))
{
	struct USERINPUT* pstEvent = pstEventHead;

	while(pstEvent != NULL) {
		if(pstEvent->pEvent == pEvent)
			return 0;
		pstEvent = pstEvent->next;
	}
	return 1;
}

int CheckUserEvent(unsigned short dInterval_type)
{
	struct USERINPUT *pstTimer;
	struct USERINPUT *pstP1;
	pstTimer = NULL;
	pstP1 = NULL;
	pstTimer = pstEventHead;
	pstP1 = pstTimer;
	while(pstP1 != NULL) {
		if(pstP1->type == dInterval_type) {
			pstP1->Degree++;
			if(pstP1->Degree >= pstP1->freq) {
				if(pstP1->pEvent) {
					pstP1->pEvent();
				}
				pstP1->Degree = 0;
			}
		}
		pstP1 = pstP1->next;
		pstTimer = pstEventHead;
	}
	return 0;
}

int InsertUserEvent(int (*pEvent)(void), int freq, int type) 
{
	struct USERINPUT* pstEvent = g_stUserEvent;
	struct USERINPUT* p_end;

	if(pstEventHead == NULL)
		pstEventHead = g_stUserEvent;

	if(!CompUserEvent(pEvent))
		return 1;

	for(int i = 0; i < MAX_EVENT_NUM; i++) {
		if(pstEvent->pEvent != NULL) {
			pstEvent++;
			continue;
		} else {
			pstEvent->pEvent = pEvent;
			pstEvent->freq = freq;
			pstEvent->type = type;

			p_end = pstEventHead;
			while(p_end != NULL) {
				if(p_end->next == NULL)
					break;
				p_end = p_end->next;
			}
			if(pstEvent != pstEventHead)
				p_end->next = pstEvent;
			pstEvent->next = NULL;
			return 0;
		}
	}
	return 1;
}

int DeleUserEvent(int (*pEvent)(void)) 
{
	struct USERINPUT* pstEvent = pstEventHead;
	struct USERINPUT* p = pstEvent;

	while(pstEvent) {
		if(pstEvent->pEvent == pEvent) {
			if(pstEvent == pstEventHead)
				pstEventHead = pstEvent->next;
			else
				p->next = pstEvent->next;
			pstEvent->next = NULL;
			pstEvent->pEvent = NULL;
			pstEvent->freq = 0;
			pstEvent->type = INTERVAL_MAX;
			return 0;
		}
		p = pstEvent;
		pstEvent = pstEvent->next;
	}
	return 1;
}

void UserPolling(void)
{
	int dTimenow;
	int dDiff;

	CheckUserEvent(INTERVAL_DIRECT);

	dTimenow = GetTimerCount();
	dDiff = DIFF(&dTimenow, &rtc_userpolling);
	if(dDiff < 2) {
		return; //2ms
	} else {
		CheckUserEvent(INTERVAL_1MS);
		rtc_userpolling = dTimenow;
		dTimenow = GetTimerCount();
		dDiff = ABS(&dTimenow, &rtc_user10ms);

		if(dDiff >= 10) { //10ms
			rtc_user10ms = dTimenow;
			CheckUserEvent(INTERVAL_10MS);

			dTimenow = GetTimerCount();
			dDiff = ABS(&dTimenow, &rtc_user100ms);
			if(dDiff >= 100) {
				CheckUserEvent(INTERVAL_100MS);
				rtc_user100ms = dTimenow;
			}
		}
	}
}
