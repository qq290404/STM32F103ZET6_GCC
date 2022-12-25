#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#define MAX_TIMER_NUM     (30)
#define INVALID_INTERVAL  (0xffff)

enum PollingTimerErrCode_e
{
	TIMER_ERR     = -1,
	TIMER_SUCCESS = 0,
	TIMER_FULL    = 1,
	TIMER_ISEXIST = 2
};

//For mode type
enum
{
    ONE_TIME,
    MULTI_TIME,
    EXECUTE_BY_CONDITION,
    MAX_TIMER_MODE,
};

//For Callback type
enum
{
    SYSTEM_TYPE,
    USB_TYPE,
    CARD_TYPE,
    DISC_TYPE,
    MAX_TYPE,
};

//the mode of deleting timer
enum
{
    TYPE,
    MODE,
    EVENT,
};

//Interval_type
enum
{
    INTERVAL_DIRECT,
    INTERVAL_1MS,
    INTERVAL_10MS,
    INTERVAL_100MS,
    INTERVAL_MAX,
};

struct Timer
{
    uint8_t   mode;               /*!<  ONE_TIME , MULTI_TIME */
    uint8_t   type;               /*!<  SYSTEM_TYPE, USB_TYPE.MAX_TYPE */
    uint16_t  Interval;           /*!<  Interval for timer, */
    uint16_t  Degree;             /*!<  Calculate times until equal Interval */
    int     (*pEvent)(void);    /*!<  Need executed function */
    uint16_t  Interval_type;      /*!< Interval type */
    struct Timer *pstNextTimer; /*!< pointer to next timer */
    uint8_t   execing;            /*!< for in pEvent call modify */
    uint8_t   reset;              /*!< for in pEvent call modify */
};

/*---------------------------------------------------------------------------*
*                          FUNCTION   DECLARATIONS                          *
*---------------------------------------------------------------------------*/
void polling();
void polling_bytype(uint8_t type);
void CriticalPolling(void);
void InitCriticalEvent(void);
int InsertCriticalEvent(int (*pEvent)(void));
int DeleCriticalEvent(int (*pEvent)(void));
void UserPolling(void);
int InsertUserEvent(int (*pEvent)(void), int freq, int type);
int DeleUserEvent(int (*pEvent)(void));

int CheckTimer(uint16_t dInterval_type);
int CheckTimer_bytype(uint8_t type, uint16_t dInterval_type);

unsigned int GetTimerCount(void);
void TimerInit(void);
void TimerDelete(int sdType, int sdSubType, int (*pEvent)(void));
int TimerInsert(
    uint8_t  bMode,                // ONE_TIME , MULTI_TIME
    uint8_t  bType,  // Necessary, Disc_Module......MaxType
    uint16_t dInterval,            // Interval for timer
    uint16_t dDegree,              // Calculate times until equal Interval
    int    (*pEvent)(void), // Need executed function
    uint16_t dInterval_type
);
void TimerModify(
    uint8_t  bMode,            // ONE_TIME , MULTI_TIME
    uint8_t  bType,            // Necessary, Disc_Module......MaxCallbackType
    uint16_t dInterval,        // Interval for timer, M
    uint16_t dDegree,          // Calculate times until equal Interval
    int    (*pEvent)(void),  // executed function
    uint16_t dInterval_type
);

int TimerReset(int (*pEvent)(void));
void TimerSystemModuleInsert(void);
int CheckTimerExist(int (*pEvent)(void));

#endif //_TIMER_H_
