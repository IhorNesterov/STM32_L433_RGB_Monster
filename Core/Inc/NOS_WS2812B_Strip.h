/**
 * @brief 
*/

#include "WS2812B_Core.h"
#include "NOS_Includes.h"
#include "NOS_Math.h"
#include "NOS_WS2812B_Strip_Effects.h"

#ifndef NOS_WS2812B_STRIP
#define NOS_WS2812B_STRIP


/**
  * @brief  Initialization of strip struct.
  * Warning : No Base init avalaible
  * @param strip pointer on strip; 
  * @param buff pointer on core frameBuffer
  * @param pixels pointer on pixelBuffer
  * @param lenght int count of Leds
  * @retval void,in future will be NOS_System_State
  */
void NOS_WS2812B_Strip_FullInit(WS2812B_Strip* strip,uint8_t* buff,PixelColor* pixels, int lenght);

/**
  * @brief  Pixel color set by core(No use to set up,only private use).
  * Warning : Only way to change frameBuffer(pseudo incap)
  * @param strip pointer on strip
  * @param pixelPos number of pixel
  * @param rgb rgb value
  * @retval void,in future will be NOS_System_State
  */
void NOS_WS2812B_Strip_CoreSetPixel(WS2812B_Strip* strip,int pixelPos,uint8_t r, uint8_t g, uint8_t b);

void NOS_WS2812B_Strip_SetPixel(WS2812B_Strip* strip,int pixelPos,uint8_t r, uint8_t g, uint8_t b);

void NOS_WS2812B_Strip_ColorFill(WS2812B_Strip* strip,PixelColor color);

void NOS_WS2812B_Strip_Clear(WS2812B_Strip* strip);

void NOS_WS2812B_Strip_Update(WS2812B_Strip* strip);

void NOS_WS2812B_Strip_TestFill(WS2812B_Strip* strip);

void NOS_WS2812B_Strip_SetPixelByRGB(WS2812B_Strip* strip,int pixelPos,uint32_t rgb);

void NOS_WS2812B_Strip_SetPixelByPixelColor(WS2812B_Strip* strip,int pixelPos, PixelColor color);

void NOS_WS2812B_Strip_SetBright(WS2812B_Strip* strip,uint8_t bright);

#endif