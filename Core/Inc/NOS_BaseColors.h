#ifndef NOS_BASECOLORS
#define NOS_BASECOLORS

#include "NOS_Includes.h"
/**
  * @brief  Base colors enum.
  */
typedef enum NOS_BaseColors_e {BLUE,OCEAN,CYAN,TURQUOISE,GREEN,SGREEN,YELLOW,ORANGE,RED,RASPBERRY,MAGENTA,VIOLET} NOS_BaseColors;

/**
  * @brief  Pixelcolor set by r,g,b.
  * @param color pointer on pixelcolor
  * @param rgb rgb value
  * @retval void,in future will be NOS_System_State
  */
void NOS_PixelColor_SetColor(PixelColor* color,uint8_t R,uint8_t G,uint8_t B);

/**
  * @brief  Get PixelColor by name from basecolors enum
  * @param color color name
  * @retval PixelColor
  */
PixelColor NOS_GetBaseColor(NOS_BaseColors color);


#endif