#ifndef NOS_LIB
#define NOS_LIB

#include "NOS_Includes.h"

#ifdef WS2812B_MODULE_ENABLED
#include "WS2812B_Effects.h"
#include "NOS_WS2812B_Strip.h"
#include "NOS_Strip_UART.h"
#include "NOS_BaseColors.h"
#endif

#ifdef UART_MODULE_ENABLED
#include "NOS_UART.h"
#endif

#ifdef MEMORY_MODULE_ENABLED
#include "NOS_Flash.h"
#include "NOS_RAM.h"
#endif

#include "NOS_Time.h"
#include "NOS_Math.h"

#endif 