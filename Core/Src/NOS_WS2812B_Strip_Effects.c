#include "NOS_WS2812B_Strip_Effects.h"
#include "NOS_WS2812B_Strip.h"

void NOS_WS2812B_Strip_Effects_AddEffect(WS2812B_Strip* strip,Effect_Struct effect)
{
    if(strip->effectsCounter < 10)
    {
        switch(effect.effectId)
        {
            case EFFECT_BREATHE_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[strip->effectsCounter],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_RAINBOW_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[strip->effectsCounter],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_DOTS_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[strip->effectsCounter],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_WALKING_PIXELS_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[strip->effectsCounter],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_STEADY_COLOR_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[strip->effectsCounter],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
        }

        //NOS_WS2812B_Strip_Effects_Check_Conflicts(strip,effect);
        strip->effectsCounter++;
    }
}

void NOS_WS2812B_Strip_Effects_Handler(WS2812B_Strip* strip)
{
    for(int i = 0; i < strip->effectsCounter; i++)
    {
        switch(strip->effects[i].effectId)
        {
            case EFFECT_BREATHE_ID:
                NOS_WS2812B_Strip_Effect_Breathe_Handler(strip,&strip->effects[i]);
                break;
            case EFFECT_RAINBOW_ID:
                NOS_WS2812B_Strip_Effect_Rainbow_Handler(strip,&strip->effects[i]);
                break;
            case EFFECT_DOTS_ID:
                NOS_WS2812B_Strip_Effect_Dots_Handler(strip,&strip->effects[i]);
                break;
            case EFFECT_WALKING_PIXELS_ID:
                NOS_WS2812B_Strip_Effect_Walking_Pixels_Handler(strip,&strip->effects[i]);
                break;
            case EFFECT_STEADY_COLOR_ID:
                NOS_WS2812B_Strip_Effect_Steady_Color_Handler(strip,&strip->effects[i]);
                break;
        }
    }
}

void NOS_WS2812B_Strip_Effects_Check_Conflicts(WS2812B_Strip* strip,Effect_Struct effect)
{
    PixelColor color = {0,0,0};
    switch(effect.effectId)
    {
        case EFFECT_RAINBOW_ID:

            NOS_WS2812B_Strip_Effect_Enable(strip,EFFECT_RAINBOW_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_STEADY_COLOR_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_DOTS_ID);
            
            NOS_WS2812B_Strip_ColorFill(strip, color);
        break;
        
        case EFFECT_DOTS_ID:

            NOS_WS2812B_Strip_Effect_Enable(strip,EFFECT_DOTS_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_RAINBOW_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_WALKING_PIXELS_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_STEADY_COLOR_ID);

            NOS_WS2812B_Strip_ColorFill(strip,color);
        break;

        case EFFECT_WALKING_PIXELS_ID:

            NOS_WS2812B_Strip_Effect_Enable(strip,EFFECT_WALKING_PIXELS_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_DOTS_ID);

            NOS_WS2812B_Strip_ColorFill(strip,color);
        break;

        case EFFECT_STEADY_COLOR_ID:

            NOS_WS2812B_Strip_Effect_Enable(strip,EFFECT_STEADY_COLOR_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_RAINBOW_ID);
            NOS_WS2812B_Strip_Effect_Disable(strip,EFFECT_DOTS_ID);

            NOS_WS2812B_Strip_ColorFill(strip,color);
        break;
    }
}

void NOS_WS2812B_Strip_Effects_UpdateEffect(WS2812B_Strip* strip,Effect_Struct effect)
{
        switch(effect.effectId)
        {
            case EFFECT_BREATHE_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[0],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_RAINBOW_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[1],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_DOTS_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[2],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_WALKING_PIXELS_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[3],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
            case EFFECT_STEADY_COLOR_ID:
                NOS_WS2812B_Strip_Effect_Init(&strip->effects[4],&effect.color,effect.speed.data,effect.step.data,effect.minValue,effect.maxValue,effect.param1,effect.param2,effect.param3,effect.param4,effect.effectId,effect.enabled);
                break;
        }

        //NOS_WS2812B_Strip_Effects_Check_Conflicts(strip,effect);
    NOS_WS2812B_Strip_Clear(strip);
}

void NOS_WS2812B_Strip_Effect_Init(Effect_Struct* effect,PixelColor* color,uint16_t speed,uint16_t step,uint16_t minValue,uint16_t maxValue,uint16_t param1,uint16_t param2,uint16_t param3,uint16_t param4,uint8_t effectID,bool enabled)
{
        NOS_Math_SinValue_Init(&effect->value,minValue,maxValue,step);
        effect->minValue = minValue;
        effect->maxValue = maxValue;
        effect->speed.data = speed;
        effect->step.data = step;
        effect->enabled = enabled;
        if(color != NULL)
        {
            NOS_PixelColor_SetColor(&effect->color,color->R,color->G,color->B);
        }
        else
        {
            NOS_PixelColor_SetColor(&effect->color,0,0,0);
        }

        effect->effectId = effectID;
        
        effect->param1 = param1;
        effect->param2 = param2;
        effect->param3 = param3;
        effect->param4 = param4;
}

void NOS_WS2812B_Strip_Effect_Copy(Effect_Struct* destination,Effect_Struct* source)
{
    NOS_Math_SinValue_Init(&destination->value,source->minValue,source->maxValue,source->step.data);
    destination->minValue = source->minValue;
    destination->maxValue = source->maxValue;
    destination->speed.data = source->speed.data;
    destination->step.data = source->step.data;
    destination->enabled = source->enabled;
    NOS_PixelColor_SetColor(&destination->color,source->color.R,source->color.G,source->color.B);
    destination->effectId = source->effectId;   
}

void NOS_WS2812B_Strip_Effect_Breathe_Handler(WS2812B_Strip* strip,Effect_Struct* effect)
{
    if(strip != NULL)
    {
        if(effect != NULL)
        {
            if(effect->enabled)
            {
                if(effect->timer > effect->speed.data)
                {
                    NOS_Math_SinValue_Handler(&effect->value);
                    NOS_WS2812B_Strip_SetBright(strip,effect->value.value);
                    NOS_WS2812B_Strip_Update(strip);
                    effect->timer = 0;
                }
                effect->timer++;
            }
        }
    }
}

void NOS_WS2812B_Strip_Effect_Rainbow_Handler(WS2812B_Strip* strip,Effect_Struct* effect)
{
    if(strip != NULL)
    {
        if(effect != NULL)
        {
            if(effect->enabled)
            {
                if(effect->timer > effect->speed.data)
                {
                    NOS_Math_SinValue_Handler(&effect->value);

                    uint16_t number = NOS_Math_GetSinValue(&effect->value);
                    uint8_t iteration = number / 0x7F;

                    PixelColor curr = { 0,0,0 };
                    number = number - 0x7F * iteration;

                    switch (iteration)
                    {
                        case 0:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.G = number;
                        break;

                        case 1:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.G = 0x7F + number;
                        break;

                        case 2:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.B = 0xFF - number;
                        break;

                        case 3:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.B = 0x7F - number;
                        break;

                        case 4:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.R = number;
                        break;

                        case 5:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.R = 0x7F + number;
                        break;

                        case 6:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.G = 0xFF - number;
                        break;

                        case 7:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.G = 0x7F - number;
                        break;

                        case 8:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.B = number;
                        break;

                        case 9:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.B = 0x7F + number;
                        break;

                        case 10:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.R = 0xFF - number;
                        break;

                        case 11:
                        curr = NOS_GetBaseColor((NOS_BaseColors)iteration);
                        curr.R = 0x7F - number;
                        break;

                        default:
                        break;
                    }
                    

                    NOS_WS2812B_Strip_ColorFill(strip,curr);
                    NOS_WS2812B_Strip_Update(strip);
                    effect->timer = 0;
                }
                effect->timer++;
            }
        }
    }
}

void NOS_WS2812B_Strip_Effect_Dots_Handler(WS2812B_Strip* strip,Effect_Struct* effect)
{
    if(effect->enabled)
    {
	uint32_t i;
	PixelColor temp = {0,0,0};
	bool isR;
	bool isG;
	bool isB;
    uint32_t random = 50;
    uint32_t fadeOutFactor = 40;
    PixelColor color = {0,0,0};

    NOS_PixelColor_SetColor(&color,effect->color.R,effect->color.G,effect->color.B);

    if(effect->timer >= effect->speed.data)
    {

	if(color.R == 0xFF)
	{
		isR = true;
	}
	else
	{
		isR = false;
	}

	if(color.G == 0xFF)
	{
		isG = true;
	}
	else
	{
		isG = false;
	}
	if(color.B == 0xFF)
	{
		isB = true;
	}
	else
	{
		isB = false;
	}

	for( i = 0; i < strip->pixelCount; i++)
	{
        temp.R = strip->pixels[i].R;
        temp.G = strip->pixels[i].G;
        temp.B = strip->pixels[i].B;

		if(rand() % random == 0)
		{	
			if(isR)
			{
				temp.R = 255;
			}
			
			if(isG)
			{
				temp.G = 255;
			}

			if(isB)
			{
				temp.B = 255;
			}
		}

		if(isR)
		{
		if(temp.R > fadeOutFactor)
			temp.R -= temp.R/fadeOutFactor;
		else
			temp.R = 0;
		}

		if(isG)
		{
		if(temp.G > fadeOutFactor)
			temp.G -= temp.G/fadeOutFactor;
		else
			temp.G = 0;
		}

		if(isB)
		{
		if(temp.B > fadeOutFactor)
			temp.B -= temp.B/fadeOutFactor;
		else
			temp.B = 0;
		}

        NOS_WS2812B_Strip_SetPixelByPixelColor(strip,i,temp);
	}
    effect->timer = 0;
}
effect->timer++;
    }
}

void NOS_WS2812B_Strip_Effect_Walking_Pixels_Handler(WS2812B_Strip* strip,Effect_Struct* effect)
{
    if(effect->enabled)
    {
        if(effect->timer > effect->speed.data)
        {
            NOS_Math_SinValue_Handler(&effect->value);

            uint16_t pixelPos = NOS_Math_GetSinValue(&effect->value);

            for(int i = 0; i < effect->param1; i++)
            {
                if(pixelPos + i < strip->pixelCount)
                {
                    NOS_WS2812B_Strip_SetPixelByPixelColor(strip,pixelPos+i,effect->color);
                }
                else
                {
                    NOS_WS2812B_Strip_SetPixelByPixelColor(strip,(pixelPos+i) - strip->pixelCount,effect->color);
                }
            }
            effect->timer = 0;
        }
        effect->timer++;
    }
}

void NOS_WS2812B_Strip_Effect_Enable(WS2812B_Strip* strip,uint8_t effectId)
{
    if(strip != NULL)
    {
        for(int i = 0; i < strip->effectsCounter; i++)
        {
            if(strip->effects[i].effectId == effectId)
            {
                strip->effects[i].enabled = true;
            }
        }
    }
}

void NOS_WS2812B_Strip_Effect_Disable(WS2812B_Strip* strip,uint8_t effectId)
{
    if(strip != NULL)
    {
        for(int i = 0; i < strip->effectsCounter; i++)
        {
            if(strip->effects[i].effectId == effectId)
            {
                strip->effects[i].enabled = false;
            }
        }
    }
}

void NOS_WS2812B_Strip_Effect_Steady_Color_Handler(WS2812B_Strip* strip,Effect_Struct* effect)
{
    if(strip != NULL)
    {
        if(effect->enabled)
        {
            NOS_WS2812B_Strip_ColorFill(strip,effect->color);
        }
    }
}
