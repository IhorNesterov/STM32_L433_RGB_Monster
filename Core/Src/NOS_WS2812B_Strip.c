#include "NOS_WS2812B_Strip.h"
#include "NOS_BaseColors.h"
#include "WS2812B_Effects.h"

void NOS_WS2812B_Strip_FullInit(WS2812B_Strip* strip,uint8_t* buff,PixelColor* pixels,int lenght)
{
    strip->pixels = pixels;
    strip->frameBuffer = buff;
    strip->pixelCount = lenght;
    strip->bright = 100;
    strip->effectsCounter = 0;
}

void NOS_WS2812B_Strip_CoreSetPixel(WS2812B_Strip* strip,int pixelPos,uint8_t r, uint8_t g, uint8_t b)
{
    if(strip->frameBuffer != NULL && pixelPos <= strip->pixelCount)
    {
        strip->frameBuffer[pixelPos * 3] = r;
        strip->frameBuffer[pixelPos * 3 + 1] = g;
        strip->frameBuffer[pixelPos * 3 + 2] = b;
    }
}

void NOS_WS2812B_Strip_SetPixel(WS2812B_Strip* strip,int pixelPos,uint8_t r, uint8_t g, uint8_t b)
{
    if(strip->pixels != NULL && pixelPos <= strip->pixelCount)
    {
        strip->pixels[pixelPos].R = r;
        strip->pixels[pixelPos].G = g;
        strip->pixels[pixelPos].B = b;
    }         
}

void NOS_WS2812B_Strip_Clear(WS2812B_Strip* strip)
{
    for(int i = 0; i < strip->pixelCount; i++)
    {
        NOS_WS2812B_Strip_SetPixel(strip,i,0,0,0);
        NOS_WS2812B_Strip_CoreSetPixel(strip,i,0,0,0);
    }
}

void NOS_WS2812B_Strip_Update(WS2812B_Strip* strip)
{
    float coef = (float)strip->bright / 100;
    for(int i = 0; i < strip->pixelCount; i++)
    {
        uint8_t currR = (float)strip->pixels[i].R * coef;
        uint8_t currG = (float)strip->pixels[i].G * coef;
        uint8_t currB = (float)strip->pixels[i].B * coef;
        NOS_WS2812B_Strip_CoreSetPixel(strip,i,currR,currG,currB);
    }

}

void NOS_WS2812B_Strip_TestFill(WS2812B_Strip* strip)
{
    int currPixel = 0;
    int currColor = 0;
    
    while(currPixel < strip->pixelCount)
    {
        NOS_WS2812B_Strip_SetPixelByPixelColor(strip,currPixel,NOS_GetBaseColor(currColor));
        
        currColor++;
        if(currColor > 11)
        {
            currColor = 0;
        }

        currPixel++;
    }
}

void NOS_WS2812B_Strip_ColorFill(WS2812B_Strip* strip,PixelColor color)
{
    for(int i = 0; i < strip->pixelCount; i++)
    {
        NOS_WS2812B_Strip_SetPixel(strip,i,color.R,color.G,color.B);
    }
}

void NOS_WS2812B_Strip_SetPixelByRGB(WS2812B_Strip* strip,int pixelPos,uint32_t rgb)
{
    uint8_t R = (rgb & 0x00FF0000) >> 16;
    uint8_t G = (rgb & 0x0000FF00) >> 8;
    uint8_t B = rgb & 0x000000FF;

    NOS_WS2812B_Strip_SetPixel(strip,pixelPos,R,G,B);
}

void NOS_WS2812B_Strip_SetPixelByPixelColor(WS2812B_Strip* strip,int pixelPos, PixelColor color)
{
    NOS_WS2812B_Strip_SetPixel(strip,pixelPos,color.R,color.G,color.B);
}

void NOS_WS2812B_Strip_SetBright(WS2812B_Strip* strip,uint8_t bright)
{
    strip->bright = bright;
}





