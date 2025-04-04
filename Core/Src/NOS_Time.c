#include "NOS_Time.h"

void NOS_RealTime_Handler(RealTime *rt)
{
    rt->milliseconds++;
    if (rt->milliseconds > 999)
    {
        rt->sec++;
        if (rt->sec > 59)
        {
            rt->sec = 0;
            rt->min++;
        }

        if (rt->min > 59)
        {
            rt->min = 0;
            rt->hour++;
        }

        if (rt->hour > 23)
        {
            rt->hour = 0;
        }

        rt->milliseconds = 0;
    }
}

void NOS_RealTime_SetTime(RealTime *rt, uint8_t _hour, uint8_t _min, uint8_t _sec, TimeFormat _format)
{
    if (_hour < 24 && _min < 60 && _sec < 60)
    {
        rt->hour = _hour;
        rt->min = _min;
        rt->sec = _sec;
        rt->format = _format;
    }
}

void NOS_TimeEvent_Init(NOS_TimeEvent *timeEvent, uint32_t ticksToEnable)
{
    if (timeEvent != NULL)
    {
        timeEvent->enabled = false;
        timeEvent->stopped = false;
        timeEvent->ticksToEnable = ticksToEnable;
        timeEvent->ticks = 0;
    }
}

void NOS_TimeEvent_Stop(NOS_TimeEvent *timeEvent)
{
    timeEvent->stopped = true;
    timeEvent->ticks = 0;
}

void NOS_TimeEvent_Resume(NOS_TimeEvent *timeEvent)
{
    timeEvent->stopped = false;
    timeEvent->ticks = 0;
}

void NOS_TimeEvent_TickHandler(NOS_TimeEvent *timeEvent)
{
    timeEvent->ticks++;
    if (!timeEvent->stopped)
    {
        if (timeEvent->ticks >= timeEvent->ticksToEnable)
        {
            timeEvent->enabled = true;
        }
    }
}

bool NOS_TimeEvent_Check(NOS_TimeEvent *timeEvent)
{
    if (timeEvent->enabled && !timeEvent->stopped)
    {
        return true;
    }
    return false;
}

void NOS_TimeEvent_FinishEvent(NOS_TimeEvent *timeEvent)
{
    timeEvent->enabled = false;
    timeEvent->ticks = 0;
}