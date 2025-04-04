/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#include <stdint.h>

#include "WS2812B_Core.h"
#include <stdlib.h>

extern WS2812_Struct ws2812b;
// RGB Framebuffers
uint8_t frameBufferA[3*512];
uint8_t frameBufferB[3*512];
uint8_t frameBufferC[3*512];
uint8_t frameBufferD[3*512];

// Helper defines
#define newColor(r, g, b) (((uint32_t)(r) << 16) | ((uint32_t)(g) <<  8) | (b))
#define Red(c) ((uint8_t)((c >> 16) & 0xFF))
#define Green(c) ((uint8_t)((c >> 8) & 0xFF))
#define Blue(c) ((uint8_t)(c & 0xFF))




void visInit()
{
		// Set output channel/pin, GPIO_PIN_0 = 0, for GPIO_PIN_5 = 5 - this has to correspond to WS2812B_PINS
		ws2812b.item[0].channel = 4;
		ws2812b.item[0].frameBufferPointer = frameBufferA;
	    ws2812b.item[0].frameBufferSize = sizeof(frameBufferA);
		ws2812b.item[1].channel = 5;
		ws2812b.item[1].frameBufferPointer = frameBufferB;
	    ws2812b.item[1].frameBufferSize = sizeof(frameBufferB);
		ws2812b.item[2].channel = 6;
		ws2812b.item[2].frameBufferPointer = frameBufferC;
	    ws2812b.item[2].frameBufferSize = sizeof(frameBufferC);
		ws2812b.item[3].channel = 7;
		ws2812b.item[3].frameBufferPointer = frameBufferD;
	    ws2812b.item[3].frameBufferSize = sizeof(frameBufferD);
		ws2812b_init();
}


void visHandle()
{

	if(ws2812b.transferComplete)
	{
		// Update your framebuffer here or swap buffers
		//visHandle2();

		// Signal that buffer is changed and transfer new data
		ws2812b.startTransfer = 1;
		ws2812b_handle();
	}
}


