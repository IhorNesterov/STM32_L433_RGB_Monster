#ifndef NOS_STRIP_UART
#define NOS_STRIP_UART

#include "NOS_Includes.h"

#define UART_ADDRESS 0x65

//commands
#define SET_STRIP_PIXEL_COUNT 0x10

#define CHECK_CONNECTION 0x20

#define SET_ONE_PIXEL_COLOR_COMMAND 0x30
#define SET_ROW_PIXEL_COLOR_COMMAND 0x31
#define SET_ALL_PIXEL_ONE_COLOR_COMMAND 0x32
#define SET_BRIGHT_COMMAND 0x33
#define SET_ALL_PIXEL_COMMAND 0x35

#define SET_EFFECT_BREATHE 0x50
#define SET_EFFECT_RAINBOW 0x51
#define SET_EFFECT_DOTS 0x52
#define SET_EFFECT_WALKING_PIXELS 0x53
#define SET_EFFECT_STEADY_COLOR 0x54

#define SET_EFFECT_ACTIVE 0x71

#define EFFECTS_MAX_COUNT 10

bool NOS_Strip_UART_ParseCommand(WS2812B_Strip* strip,UART_Message* message);

bool NOS_Strip_UART_ParseStringCommand(WS2812B_Strip* strip, const char* message, int lenght);

bool NOS_Strip_UART_ParseStringCommandTest(WS2812B_Strip* strip, const char* message, int lenght);

#endif