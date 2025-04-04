#ifndef NOS_TYPEDEFS
#define NOS_TYPEDEFS

#include "stdint.h"
#include "stdbool.h"
#include "stm32l4xx.h"
#include "stdlib.h"
/* Unions begin */

typedef union Short_t //uint16_t data wrap
{ 
    uint8_t bytes[2];
    uint16_t data;
} NOS_Short;

typedef union Float_t //float data wrap
{
    uint8_t bytes[4];
    float data;
} NOS_Float;

typedef union Long_t //ulong data wrap
{
  uint8_t bytes[4];
  uint32_t data;
} NOS_Long;

/* Unions end */

/* Structures begin */

/*WS2812B Matrix*/

/**
  * @brief  Point structure.
  * @param x uint16_t x point
  * @param y uint16_t y point 
  */
typedef struct Point_t
{
  uint16_t x;
  uint16_t y;
}Point;

/**
  * @brief  Color structure.
  * @param R uint8_t Red value(0-255)
  * @param G uint8_t Green value(0-255)
  * @param B uint8_t Blue value(0-255)
  */
typedef struct PixelColor_t
{
   uint8_t R;
   uint8_t G;
   uint8_t B;
} PixelColor;

typedef struct MatrixSize_t
{
  uint8_t col;
  uint8_t row;
} MatrixSize;


typedef struct IdealSymbol_t
{
  uint8_t* data;
  uint8_t lenght;
} IdealSymbol;



typedef struct  Symvol_t
{
  uint8_t data[5];
} Symvol;


typedef struct WS2812B_Matrix_t
{
    uint8_t* buffer;
    uint8_t bright;
    NOS_Short ledsCount;
    MatrixSize size;
    PixelColor textColor;
    PixelColor foneColor;
    Symvol* symvols;
} WS2812B_Matrix;



/*WS2812B Matrix*/

typedef enum TimeFormat_e{Hour24,Hour12} TimeFormat;

typedef struct RealTime_t
{
  uint32_t milliseconds;
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  TimeFormat format;
} RealTime;

/// @brief 
typedef struct NOS_TimeEvent_t
{
  uint32_t ticksToEnable;
  bool stopped;
  bool enabled;
  uint32_t ticks;
} NOS_TimeEvent;

typedef struct GPIO_PIN_t
{
  GPIO_TypeDef* Port;
  uint16_t Pin;
} GPIO_PIN;

typedef enum Language_e{English,Ukrainian} Language;
typedef enum MoveDirection_e {UP,DOWN,RIGHT,LEFT} MoveDirection;

typedef enum Signal_Level_e {LOW,HIGH} Signal_Level;
typedef enum Button_State_e
{
    Idle,pressed,released,pressDone
}Button_State;

typedef struct NOS_Button_t
{
    bool pressed;
    bool released;
    bool pressDone;
    bool stopped;
    GPIO_PinState openLevel;

    uint32_t timer;
    uint32_t pressedTime;
    uint32_t releasedTime;
    uint32_t lastDoneTime;
    uint32_t stopTime;

    GPIO_PIN* pin;

}NOS_Button;

typedef struct SinValue_t
{
    int value;

    int minValue;
    int maxValue;
    int increment;
    bool rise;
    bool fall;
}SinValue;

typedef struct Effect_Struct_t
{
  SinValue value;
  NOS_Short speed;
  NOS_Short step;

  uint16_t timer;
  uint16_t minValue;
  uint16_t maxValue;

  uint16_t param1;
  uint16_t param2;
  uint16_t param3;
  uint16_t param4;

  PixelColor color;

  bool enabled;
  uint8_t effectId;
} Effect_Struct;

typedef struct
{
    NOS_Short address;
    NOS_Short channel;
    NOS_Short byteCount;
    NOS_Long packetId;
    NOS_Long command;
    uint8_t data[512];
    NOS_Short CRC16;
} UART_Message;

/**
  * @brief  Strip structure.
  * Warning : No Base init avalaible
  * @param frameBuffer pointer on core frame buffer in WS2812B_Core 
  * @param pixels pointer on pixelBuffer
  * @param pixelCount int count of Leds in strip
  * @param bright int (0-100) brightness of led
  * @retval void,in future will be NOS_System_State
  */
typedef struct NOS_WS2812B_STRIP_t
{
    uint8_t* frameBuffer;
    PixelColor* pixels;
    int pixelCount;
    int bright;

    Effect_Struct effects[5];
    uint8_t effectsCounter;
}WS2812B_Strip;


typedef struct NOS_Flash_Chunk_t
{
  void* dataPointer;
  uint32_t flashAddress;
  size_t size;
}NOS_Flash_Chunk;

#define FLASH_CHUNKS_MAX_COUNTER 8

typedef struct NOS_Flash_Memory_Struct_t
{
  uint32_t baseFlashAddress;
  NOS_Flash_Chunk chunks[FLASH_CHUNKS_MAX_COUNTER];
  uint32_t chunksCounter;
  size_t totalSize;
}NOS_Flash_Memory_Struct;

typedef struct NOS_WS2812B_Strips_Array_t
{
  WS2812B_Strip* stripA;
  WS2812B_Strip* stripB;
  WS2812B_Strip* stripC;
  WS2812B_Strip* stripD;


}NOS_WS2812B_Strips_Array;

/* STM32 Core structures begin*/



/* STM32 Core structures end*/

/* Structures end */
#endif