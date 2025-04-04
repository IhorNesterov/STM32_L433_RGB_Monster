#include "NOS_Strip_UART.h"
#include "NOS_WS2812B_Strip.h"

bool NOS_Strip_UART_ParseCommand(WS2812B_Strip* strip,UART_Message* message)
{
    int currPos = 0;
    NOS_Short tempShort;
    Effect_Struct tempEffect = {0};
    PixelColor color = NOS_GetBaseColor(GREEN);
    NOS_WS2812B_Strip_Effect_Init(&tempEffect,&color,0,0,0,0,0,0,0,0,0,0);

    switch (message->command.data)
    {
        case SET_STRIP_PIXEL_COUNT:

        tempShort.bytes[1] = message->data[currPos++];
        tempShort.bytes[0] = message->data[currPos++];


        if(tempShort.data > 0 && tempShort.data <= 512)
        {
            NOS_WS2812B_Strip_Clear(strip);
            strip->pixelCount = tempShort.data;
        }
        
        return true;
        break;

    case SET_EFFECT_BREATHE:

            if(message->data[currPos++] == EFFECT_BREATHE_ID)
            {
                tempEffect.effectId = EFFECT_BREATHE_ID;
            }

            if(message->data[currPos++] == 0xFF)
            {
                tempEffect.enabled = true;
            }
            else
            {
                tempEffect.enabled = false;
            }

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            uint16_t speed = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            uint16_t step = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            uint16_t min = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            uint16_t max = tempShort.data;

            tempEffect.color.R = message->data[currPos++];
            tempEffect.color.G = message->data[currPos++];
            tempEffect.color.B = message->data[currPos++];

            NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempEffect.color,speed,step,min,max,0,0,0,0,tempEffect.effectId,tempEffect.enabled);
            NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);

            return true;       
            break;
    
        case SET_EFFECT_RAINBOW:

            if(message->data[currPos++] == EFFECT_RAINBOW_ID)
            {
                tempEffect.effectId = EFFECT_RAINBOW_ID;
            }

            if(message->data[currPos++] == 0xFF)
            {
                tempEffect.enabled = true;
            }
            else
            {
                tempEffect.enabled = false;
            }

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            speed = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            step = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            min = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            max = tempShort.data;

            tempEffect.color.R = message->data[currPos++];
            tempEffect.color.G = message->data[currPos++];
            tempEffect.color.B = message->data[currPos++];

            NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempEffect.color,speed,step,min,max,0,0,0,0,tempEffect.effectId,tempEffect.enabled);
            NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
            return true;
            break;

        case SET_EFFECT_DOTS:

            if(message->data[currPos++] == EFFECT_DOTS_ID)
            {
                tempEffect.effectId = EFFECT_DOTS_ID;
            }

            if(message->data[currPos++] == 0xFF)
            {
                tempEffect.enabled = true;
            }
            else
            {
                tempEffect.enabled = false;
            }

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            speed = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            step = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            min = tempShort.data;

            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            max = tempShort.data;

            tempEffect.color.R = message->data[currPos++];
            tempEffect.color.G = message->data[currPos++];
            tempEffect.color.B = message->data[currPos++];

            NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempEffect.color,speed,step,min,max,0,0,0,0,tempEffect.effectId,tempEffect.enabled);
            NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);

            return true;       
            break;

        case SET_EFFECT_WALKING_PIXELS:
            
            if(message->data[currPos++] == EFFECT_DOTS_ID)
            {
                tempEffect.effectId = EFFECT_DOTS_ID;
            }

            if(message->data[currPos++] == 0xFF)
            {
                tempEffect.enabled = true;
            }
            else
            {
                tempEffect.enabled = false;
            }

            tempEffect.color.R = message->data[currPos++];
            tempEffect.color.G = message->data[currPos++];
            tempEffect.color.B = message->data[currPos++];

            NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempEffect.color,speed,step,min,max,0,0,0,0,tempEffect.effectId,tempEffect.enabled);
            NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);


            return true;
            break;
            
        case SET_ONE_PIXEL_COLOR_COMMAND:

            //pixelPos 
            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            int tempInt1 = tempShort.data;

            //color
            uint8_t r = message->data[currPos++];
            uint8_t g = message->data[currPos++];
            uint8_t b = message->data[currPos++];

            NOS_WS2812B_Strip_SetPixel(strip,tempInt1,r,g,b);
            return true;
            break;

        case SET_ROW_PIXEL_COLOR_COMMAND:

            //pixelPos
            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            tempInt1 = tempShort.data;

            //pixelCount
            tempShort.bytes[1] = message->data[currPos++];
            tempShort.bytes[0] = message->data[currPos++];
            int tempInt2 = tempShort.data;

            //color
            r = message->data[currPos++];
            g = message->data[currPos++];
            b = message->data[currPos++];

            //fill in row
            for(int i = tempInt1; i < tempInt2; i++)
            {
                    NOS_WS2812B_Strip_SetPixel(strip,i,r,g,b);
            }

            return true;
            break;

        case SET_ALL_PIXEL_ONE_COLOR_COMMAND:

            //color
            r = message->data[currPos++];
            g = message->data[currPos++];
            b = message->data[currPos++];

            //fill all pixels
            for(int i = 0; i < strip->pixelCount; i++)
            {
                NOS_WS2812B_Strip_SetPixel(strip,i,r,g,b);
            }
            return true;
            break;

        case SET_ALL_PIXEL_COMMAND:

                strip->bright = 100;
                strip->effects[0].enabled = false;
                strip->effects[1].enabled = false;
                //Pixel count
                tempShort.bytes[1] = message->data[currPos++];
                tempShort.bytes[0] = message->data[currPos++];
                tempInt1 = tempShort.data;

                if(tempInt1 <= strip->pixelCount)
                {
                    for(int i = 0; i < tempInt1; i++)
                    {
                        r = message->data[currPos++];
                        g = message->data[currPos++];
                        b = message->data[currPos++];

                        NOS_WS2812B_Strip_SetPixel(strip,i,r,g,b);
                    }
                }
            
            return true;
            break;


    default:

        break;
    }

    return false;
}

uint16_t getRainbowStageFromColor(PixelColor color)
{
    uint16_t result = 0;

    if(color.R == 0 && color.G == 0 && color.B == 0xFF)
    {
        result = 0;
    }

    if(color.R == 0x0 && color.G == 0x7F && color.B == 0xFF)
    {
        result = 127;
    }

    if(color.R == 0 && color.G == 0xFF && color.B == 0xFF)
    {
        result = 254;
    }

    if(color.R == 0 && color.G == 0xFF && color.B == 0x7F)
    {
        result = 381;
    }

    if(color.R == 0 && color.G == 0xFF && color.B == 0)
    {
        result = 508;
    }

    if(color.R == 0x7F && color.G == 0xFF && color.B == 0)
    {
        result = 635;
    }

    if(color.R == 0xFF && color.G == 0xFF && color.B == 0)
    {
        result = 762;
    }

    if(color.R == 0xFF && color.G == 0x7F && color.B == 0)
    {
        result = 889;
    }

    if(color.R == 0xFF && color.G == 0 && color.B == 0)
    {
        result = 1016;
    }

    if(color.R == 0xFF && color.G == 0 && color.B == 0x7F)
    {
        result = 1143;
    }

    if(color.R == 0xFF && color.G == 0 && color.B == 0xFF)
    {
        result = 1270;
    }

    if(color.R == 0x7F && color.G == 0 && color.B == 0xFF)
    {
        result = 1397;
    }
    
    return result;
}

uint16_t getU16ParamFromString(char* message, int lenght)
{
    int power = lenght - 1;

    uint16_t result = 0;

    for (int i = 0; i < lenght; i++)
    {
        uint8_t num = message[i] - 48;

        if (num >= 0 && num < 10)
        {
            int x = pow(10,power);
            result += num * x;
            power--;
        }
    }

    return result;
}

inline uint8_t getDigitFromChar(char c)
{
    if (c >= 48 && c <= 57)
    {
        return c - 48;
    }

    if (c >= 97 && c <= 102)
    {
        return c - 97 + 10;
    }
}

uint8_t getHex(char* hex)
{
    uint8_t firstDigit = getDigitFromChar(hex[0]);
    uint8_t secondDigit = getDigitFromChar(hex[1]);

    uint8_t result = 0;

    result += firstDigit * 16;
    result += secondDigit;

    return result;
}

PixelColor getPixelColorFromString(char* message, int lenght)
{
    PixelColor result = {0,0,0};
    char* ptr = message;

    if(lenght == 6)
    {
        result.R = getHex(ptr);
        ptr += 2;
        result.G = getHex(ptr);
        ptr += 2;
        result.B = getHex(ptr);
    }
    else
    {
        char digit1[3];
        char digit2[3];
        char digit3[3];
        uint8_t subIndex = 0;

        //skip to (
        while(*ptr != '(')
        {
            ptr++;
        }

        ptr++; //skip (

        while(*ptr != ',')
        {
            digit1[subIndex] = *ptr;
            ptr++;
            subIndex++;
        }

        result.R = getU16ParamFromString(digit1,subIndex);

        subIndex = 0;
        ptr++; //skip ,
        ptr++; //skip space

        while(*ptr != ',')
        {
            digit1[subIndex] = *ptr;
            ptr++;
            subIndex++;
        }

        result.G = getU16ParamFromString(digit1,subIndex);

        subIndex = 0;
        ptr++; //skip ,
        ptr++; //skip space

        while(*ptr != ',')
        {
            digit1[subIndex] = *ptr;
            ptr++;
            subIndex++;
        }

        result.B = getU16ParamFromString(digit1,subIndex);

    }

    return result;
}

bool isEqualStrings(char* message,const char* op,int startPos,int lenght)
{
    for(int i = 0; i < lenght; i++)
    {
        if(message[startPos] == op[i])
        {
            startPos++;
        }
        else
        {
            return false;
        }
    }

    return true;
}

#define EFFECTS_DIVIDER '&'
#define PARAMS_DIVIDER '/'

Effect_Struct parseBreatheEffect(const char* message, int messageLenght)
{
    Effect_Struct result ;

    char* cPtr = message;

    char speedString[2];
    char minString[2];
    char maxString[2];
    char enabledString[5];

    uint8_t paramsDividers[6];
    uint8_t paramsCounter = 0;

    for(int i = 0; i < messageLenght; i++)
    {
        if(*cPtr == PARAMS_DIVIDER)
        {
            paramsDividers[paramsCounter] = i;

            paramsCounter++;
        }
        cPtr++;
    }

    //speed param

    int subIndex = 0;
    for(int index = paramsDividers[1] + 1; index < paramsDividers[2]; index++)
    {
        speedString[subIndex] = message[index];
        subIndex++;
    }

    uint16_t speed = getU16ParamFromString(speedString,2);

    //min param

    subIndex = 0;
    for(int index = paramsDividers[2] + 1; index < paramsDividers[3]; index++)
    {
        minString[subIndex] = message[index];
        subIndex++;
    }
    
    uint16_t min = getU16ParamFromString(minString,2);

    //max param

    subIndex = 0;
    for(int index = paramsDividers[3] + 1; index < paramsDividers[4]; index++)
    {
        maxString[subIndex] = message[index];
        subIndex++;
    }
    
    uint16_t max = getU16ParamFromString(maxString,2);

    //enabled param

    subIndex = 0;
    for(int index = paramsDividers[4] + 1; index < paramsDividers[5]; index++)
    {
        enabledString[subIndex] = message[index];
        subIndex++;
    }
    
    bool enabled = false;
    if(isEqualStrings(enabledString,"true",0,4))
    {
        enabled = true;
    }

    NOS_WS2812B_Strip_Effect_Init(&result,NULL,speed,1,min,max,0,0,0,0,EFFECT_BREATHE_ID,enabled);

    return result;
            
}

bool NOS_Strip_UART_ParseStringCommandTest(WS2812B_Strip* strip,const char* message, int messageLenght)
{
    /*Parse to individual effect strings*/
    char breatheString[32];
    char rainbowString[64];
    char dotsString[32];
    char walkingString[32];
    char steadyString[32];

    int effectDividers[8];

    char* cPtr = message;
    uint8_t dividerCounter = 0;

    //finding indexes of Effect dividers
    for(int i = 0; i < messageLenght; i++)
    {
        if(*cPtr == EFFECTS_DIVIDER)
        {
            effectDividers[dividerCounter] = i; 
            dividerCounter++;
        }
        cPtr++;
    }

    uint8_t subIndex = 0;
    for(int i = effectDividers[0]; i < effectDividers[1]; i++)
    {
        breatheString[subIndex] = message[i];
        subIndex++;
    }

    Effect_Struct effect = parseBreatheEffect(breatheString,subIndex);

    subIndex = 0;
    for(int i = effectDividers[1]; i < effectDividers[2]; i++)
    {
        rainbowString[subIndex] = message[i];
        subIndex++;
    }

    subIndex = 0;
    for(int i = effectDividers[2]; i < effectDividers[3]; i++)
    {
        dotsString[subIndex] = message[i];
        subIndex++;
    }

    subIndex = 0;
    for(int i = effectDividers[3]; i < effectDividers[4]; i++)
    {
        walkingString[subIndex] = message[i];
        subIndex++;
    }

    subIndex = 0;
    for(int i = effectDividers[4]; i < effectDividers[5]; i++)
    {
        steadyString[subIndex] = message[i];
        subIndex++;
    }



}


bool NOS_Strip_UART_ParseStringCommand(WS2812B_Strip* strip, const char* message, int lenght)
{
    char effectDivider = '&';
    char paramDivider = '/';

    uint16_t index = 0;
    uint16_t subIndex = 0;

    uint16_t min,max,speed;
    PixelColor tempColor = {0,0,0};

    Effect_Struct tempEffect = {0};

    char temp[16];

    while(index < lenght)
    {
        if(message[index] == effectDivider)
        {
            index++;

            if(paramDivider == message[index])
            {
                index++;

                if(message[index] == 'B')
                {
                    while(message[index] != paramDivider)
                    {
                        index++;
                    }

                    index++;
                    
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    min = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    max = getU16ParamFromString(temp,subIndex); 

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    speed = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    bool enabled = false;

                    if(isEqualStrings(temp,"true",0,4))
                    {
                        enabled = true;
                    }
                    else if(isEqualStrings(temp,"false",0,5))
                    {
                        enabled = false;
                    }

                    NOS_WS2812B_Strip_Effect_Init(&tempEffect,NULL,speed,1,min,max,0,0,0,0,EFFECT_BREATHE_ID,enabled);
                    NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
                }

                while(message[index] != 'R')
                {
                    index++;
                }

                if(message[index] == 'R')
                {
                    while(message[index] != paramDivider)
                    {
                        index++;
                    }

                    index++;
                    index++;
                    
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    tempColor = getPixelColorFromString(temp,subIndex);

                    min = getRainbowStageFromColor(tempColor);

                    index++;
                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    tempColor = getPixelColorFromString(temp,subIndex);

                    max = getRainbowStageFromColor(tempColor);

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    speed = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    bool enabled = false;

                    if(isEqualStrings(temp,"true",0,4))
                    {
                        enabled = true;
                    }
                    else if(isEqualStrings(temp,"false",0,5))
                    {
                        enabled = false;
                    }

                    NOS_WS2812B_Strip_Effect_Init(&tempEffect,NULL,speed,1,min,max,0,0,0,0,EFFECT_RAINBOW_ID,enabled);
                    NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
                }

                while(message[index] != 'D')
                {
                    index++;
                }

                if(message[index] == 'D')
                {
                    while(message[index] != paramDivider)
                    {
                        index++;
                    }

                    index++;
                    index++;
                    
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    tempColor = getPixelColorFromString(temp,subIndex);

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    speed = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    bool enabled = false;

                    if(isEqualStrings(temp,"true",0,4))
                    {
                        enabled = true;
                    }
                    else if(isEqualStrings(temp,"false",0,5))
                    {
                        enabled = false;
                    }

                    NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempColor,speed,1,0,0,0,0,0,0,EFFECT_DOTS_ID,enabled);
                    NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
                }

                while(message[index] != 'W')
                {
                    index++;
                }

                if(message[index] == 'W')
                {
                    while(message[index] != paramDivider)
                    {
                        index++;
                    }

                    index++;
                    index++;
                    
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    tempColor = getPixelColorFromString(temp,subIndex);

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    min = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    speed = getU16ParamFromString(temp,subIndex);

                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    bool enabled = false;

                    if(isEqualStrings(temp,"true",0,4))
                    {
                        enabled = true;
                    }
                    else if(isEqualStrings(temp,"false",0,5))
                    {
                        enabled = false;
                    }

                    NOS_WS2812B_Strip_Effect_Init(&tempEffect,NULL,speed,1,0,0,min,0,0,0,EFFECT_WALKING_PIXELS_ID,enabled);
                    NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
                }

                while(message[index] != 'S')
                {
                    index++;
                }

                if(message[index] == 'S')
                {
                    while(message[index] != paramDivider)
                    {
                        index++;
                    }

                    index++;
                    index++;
                    
                    subIndex = 0;
                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    tempColor = getPixelColorFromString(temp,subIndex);

                    index++;
                    subIndex = 0;

                    while(message[index] != paramDivider)
                    {
                        temp[subIndex] = message[index];
                        subIndex++;
                        index++;
                    }

                    bool enabled = false;

                    if(isEqualStrings(temp,"true",0,4))
                    {
                        enabled = true;
                    }
                    else if(isEqualStrings(temp,"false",0,5))
                    {
                        enabled = false;
                    }

                    NOS_WS2812B_Strip_Effect_Init(&tempEffect,&tempColor,speed,1,0,0,0,0,0,0,EFFECT_STEADY_COLOR_ID,enabled);
                    NOS_WS2812B_Strip_Effects_UpdateEffect(strip,tempEffect);
                }

                
            }
        }
        index++;
    }

    return true;
}