#ifndef NOS_UART
#define NOS_UART

#include "NOS_Includes.h"

#define UART_ADDRESS 0x65
#define BUFFER_SIZE 1024

typedef struct NOS_UART_Struct_t
{
    UART_Message message;

    uint8_t rx_buff[BUFFER_SIZE];
    uint8_t* rx_buff_ptr;

    uint32_t receiveTime;
    uint32_t receiveTimeAbort;
    uint32_t lastReceivedByteTime;

    NOS_Short value;

    uint16_t index;
    uint16_t currMessageLenght;
    uint16_t lastMessageSize;
    uint16_t bytesToRead;
    
    bool rx_flag;
    bool tx_flag;
    bool startReceive;
    bool endReceive;
    bool bufferCommand;
    bool receiveAbort;
    bool receiveCheck;
    
}NOS_UART_Struct;



NOS_UART_Struct* NOS_UART_ReceiveReset(NOS_UART_Struct* data);

NOS_UART_Struct* NOS_UART_ContinueReceive(NOS_UART_Struct* data);

void NOS_UART_ReceiveAbort(NOS_UART_Struct* data,UART_HandleTypeDef* uart);

void NOS_UART_Timer_Handler(NOS_UART_Struct* uart);

void NOS_UART_ReceiveHandler(NOS_UART_Struct* data,UART_HandleTypeDef* uart);

bool NOS_UART_CheckReceive(NOS_UART_Struct* data);

uint8_t* NOS_UART_GetReceivedData(NOS_UART_Struct* data);

void NOS_UART_EndReceive(NOS_UART_Struct* data);

bool NOS_UART_ParsePacket(NOS_UART_Struct* data,UART_Message* message);

bool NOS_UART_PacketApprovedNotice(UART_Message* message,UART_HandleTypeDef* uart);

#endif