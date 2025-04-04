#include "NOS_BaseColors.h"

void NOS_PixelColor_SetColor(PixelColor* color,uint8_t R,uint8_t G,uint8_t B)
{
    color->R = R;
    color->G = G;
    color->B = B;
}

PixelColor NOS_GetBaseColor(NOS_BaseColors color)
{
    PixelColor result = {0,0,0};
    
    switch(color)
    {
        case BLUE:
            NOS_PixelColor_SetColor(&result,0x00,0x00,0xFF);
        break;

        case OCEAN:
            NOS_PixelColor_SetColor(&result,0x00,0x7F,0xFF);
        break;

        case CYAN:
            NOS_PixelColor_SetColor(&result,0x00,0xFF,0xFF);
        break;

        case TURQUOISE:
            NOS_PixelColor_SetColor(&result,0x00,0xFF,0x7F);
        break;

        case GREEN:
            NOS_PixelColor_SetColor(&result,0x00,0xFF,0x00);
        break;

        case SGREEN:
            NOS_PixelColor_SetColor(&result,0x7F,0xFF,0x00);
        break;

        case YELLOW:
            NOS_PixelColor_SetColor(&result,0xFF,0xFF,0x00);
        break;

        case ORANGE:
            NOS_PixelColor_SetColor(&result,0xFF,0x7F,0x00);
        break;

        case RED:
            NOS_PixelColor_SetColor(&result,0xFF,0x00,0x00);
        break;

        case RASPBERRY:
            NOS_PixelColor_SetColor(&result,0xFF,0x00,0x7F);
        break;

        case MAGENTA:
            NOS_PixelColor_SetColor(&result,0xFF,0x00,0xFF);
        break;

        case VIOLET:
            NOS_PixelColor_SetColor(&result,0x7F,0x00,0xFF);
        break;
        
    }
    return result;
}