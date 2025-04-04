#include "NOS_Math.h"

int NOS_Math_NormalizeValue(int value,int maxValue)
{
    while(value >= maxValue)
    {
        value = value - maxValue;
    }
    
    return value;
}

int NOS_Math_GetNumberPower(int value)
{
    int probe = 10;
    int power = 1;
    while (value >= probe)
    {
        power++;
        probe = probe * 10;
    }
    return power;
}

int NOS_Math_GetSinValue(SinValue* value)
{
    return value->value;
}

void NOS_Math_SinValue_Handler(SinValue* value)
{
    if(value->rise)
    {
        value->value += value->increment;
        if(value->value > value->maxValue)
        {
            value->value = value->maxValue;
            value->rise = false;
            value->fall = true;
        }
    }
    else if(value->fall)
    {
        value->value -= value->increment;
        if(value->value < value->minValue)
        {
            value->value = value->minValue;
            value->fall = false;
            value->rise = true;
        }
    }
}

void NOS_Math_SinValue_Init(SinValue* value,int minValue,int maxValue,int increment)
{
    value->value = minValue;
    value->minValue = minValue;
    value->maxValue = maxValue;
    value->rise = true;
    value->fall = false;
    value->increment = increment;
}