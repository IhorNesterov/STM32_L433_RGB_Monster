#include "NOS_Includes.h"
#include "NOS_BaseColors.h"

#define EFFECT_BREATHE_ID 0x20
#define EFFECT_RAINBOW_ID 0x21
#define EFFECT_DOTS_ID 0x22
#define EFFECT_WALKING_PIXELS_ID 0x23
#define EFFECT_STEADY_COLOR_ID 0x24

/* Effects main */
void NOS_WS2812B_Strip_Effects_AddEffect(WS2812B_Strip* strip,Effect_Struct effect);

void NOS_WS2812B_Strip_Effects_UpdateEffect(WS2812B_Strip* strip,Effect_Struct effect);

void NOS_WS2812B_Strip_Effects_Handler(WS2812B_Strip* strip);

void NOS_WS2812B_Strip_Effect_Copy(Effect_Struct* destination,Effect_Struct* source);

void NOS_WS2812B_Strip_Effect_Init(Effect_Struct* effect,PixelColor* color,uint16_t speed,uint16_t step,uint16_t minValue,uint16_t maxValue,uint16_t param1,uint16_t param2,uint16_t param3,uint16_t param4,uint8_t effectID,bool enabled);

void NOS_WS2812B_Strip_Effect_Enable(WS2812B_Strip* strip,uint8_t effectId);

void NOS_WS2812B_Strip_Effect_Disable(WS2812B_Strip* strip,uint8_t effectId);

/* Breathe effect */

void NOS_WS2812B_Strip_Effect_Breathe_Handler(WS2812B_Strip* strip,Effect_Struct* effect);

/* Rainbow effect */

void NOS_WS2812B_Strip_Effect_Rainbow_Handler(WS2812B_Strip* strip,Effect_Struct* effect);

/* Dots Effect */

void NOS_WS2812B_Strip_Effect_Dots_Handler(WS2812B_Strip* strip,Effect_Struct* effect);

/* Walking pixels Effect */

void NOS_WS2812B_Strip_Effect_Walking_Pixels_Handler(WS2812B_Strip* strip,Effect_Struct* effect);

/* Steady color Effect */

void NOS_WS2812B_Strip_Effect_Steady_Color_Handler(WS2812B_Strip* strip,Effect_Struct* effect);

