
#include "NOS_Includes.h"

void NOS_RealTime_Handler(RealTime* rt);
void NOS_RealTime_SetTime(RealTime* rt,uint8_t _hour,uint8_t _min,uint8_t _sec,TimeFormat _format);

void NOS_TimeEvent_Init(NOS_TimeEvent* timeEvent,uint32_t ticksToEnable);
void NOS_TimeEvent_Stop(NOS_TimeEvent* timeEvent);
void NOS_TimeEvent_Resume(NOS_TimeEvent* timeEvent);
void NOS_TimeEvent_TickHandler(NOS_TimeEvent* timeEvent);
bool NOS_TimeEvent_Check(NOS_TimeEvent* timeEvent);
void NOS_TimeEvent_FinishEvent(NOS_TimeEvent* timeEvent);