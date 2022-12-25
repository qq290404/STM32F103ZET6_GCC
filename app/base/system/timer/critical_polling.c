#include "config.h"

#define MAX_EVENT_NUM          8

struct CRITICAL
{
	int 	(*pEvent)(void);
	struct	CRITICAL *next;
};

static struct CRITICAL   g_stCriticalEvent[MAX_EVENT_NUM];
static struct CRITICAL*  pstEventHead = NULL;

static inline int CheckCriticalEvent(int (*pEvent)(void))
{
	struct CRITICAL* pstCriticalEvent = pstEventHead;

	while(pstCriticalEvent != NULL) {
		if(pstCriticalEvent->pEvent == pEvent)
			return 0;
		pstCriticalEvent = pstCriticalEvent->next;
	}
	return 1;
}

int InsertCriticalEvent(int (*pEvent)(void))
{
	struct CRITICAL* pstCriticalEvent = g_stCriticalEvent;
	struct CRITICAL* p_end;

	if(pstEventHead == NULL)
		pstEventHead = g_stCriticalEvent;

	if(!CheckCriticalEvent(pEvent))
		return 1;

	for(int i = 0; i < MAX_EVENT_NUM; i++) {
		if(pstCriticalEvent->pEvent != NULL) {
			 pstCriticalEvent++;
			 continue;
		} else {
			pstCriticalEvent->pEvent = pEvent;

			p_end = pstEventHead;
			while(p_end != NULL) {
				if(p_end->next == NULL)
					break;
				p_end = p_end->next;
			}

			if(pstCriticalEvent != pstEventHead)
				p_end->next = pstCriticalEvent;
			pstCriticalEvent->next = NULL;
			return 0;
		}
	}
	return 1;
}

int DeleCriticalEvent(int (*pEvent)(void))
{
	struct CRITICAL* pstCriticalEvent = pstEventHead;
	struct CRITICAL* p = pstCriticalEvent;

	while(pstCriticalEvent) {
		if(pstCriticalEvent->pEvent == pEvent) {
			if(pstCriticalEvent == pstEventHead)
				pstEventHead = pstCriticalEvent->next;
			else
				p->next = pstCriticalEvent->next;

			pstCriticalEvent->next = NULL;
			pstCriticalEvent->pEvent = NULL;
			return 0;
		}
		p = pstCriticalEvent;
		pstCriticalEvent = pstCriticalEvent->next;
	}
	return 1;
}

void CriticalPolling(void)
{
	struct CRITICAL* pstCriticalEvent = pstEventHead;

	while(pstCriticalEvent != NULL){
		if(pstCriticalEvent->pEvent != NULL)
			pstCriticalEvent->pEvent();
		pstCriticalEvent = pstCriticalEvent->next;
	}
}
