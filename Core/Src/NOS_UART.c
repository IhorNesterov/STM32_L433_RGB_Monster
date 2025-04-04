#include "NOS_UART.h"

NOS_UART_Struct* NOS_UART_ReceiveReset(NOS_UART_Struct* data)
{
    data->lastMessageSize = data->currMessageLenght;
    data->rx_buff_ptr = data->rx_buff;
    data->currMessageLenght = 0;
    data->startReceive = false;
    data->rx_flag = true;
    return data;
}

NOS_UART_Struct* NOS_UART_ContinueReceive(NOS_UART_Struct* data)
{
    data->rx_buff[data->currMessageLenght] = *data->rx_buff_ptr;
    ++data->rx_buff_ptr;
    return data;
}

void NOS_UART_ReceiveAbort(NOS_UART_Struct* data,UART_HandleTypeDef* uart)
{
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        data->rx_buff[i] = 0;
    }

    data->rx_buff_ptr = data->rx_buff;
    data->index = 0;
    data->currMessageLenght = 0;
    data->startReceive = false;
    data->endReceive = false;
    data->bufferCommand = false;
    data->rx_flag = false;
    data->receiveTimeAbort = 400;
    HAL_UART_Receive_IT (uart, data->rx_buff_ptr, 1); 
}

void NOS_UART_Timer_Handler(NOS_UART_Struct* uart)
{
    uart->lastReceivedByteTime++;

    if(uart->startReceive)
    {
        uart->receiveTime++;
    }

    if(uart->startReceive && uart->lastReceivedByteTime > 5)
    {
        uart->index = 0;
        uart->receiveTime = 0;
        NOS_UART_ReceiveReset(uart);
    }
}

uint16_t GetCRC16(uint8_t *buf, int len)
{  
  unsigned int crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
  crc ^= (unsigned int)buf[pos];  

  for (int i = 8; i != 0; i--) {    
    if ((crc & 0x0001) != 0) {      
      crc >>= 1;                    
      crc ^= 0xA001;
    }
    else                            
      crc >>= 1;                    
    }
  }

  return crc;
}

void NOS_UART_ReceiveHandler(NOS_UART_Struct* data,UART_HandleTypeDef* uart)
{
    data->startReceive = true;

    data->lastReceivedByteTime = 0; 
    data->currMessageLenght++;
    
    data->rx_buff[data->index] = *data->rx_buff_ptr;
    ++data->index;
    ++data->rx_buff_ptr;
    
    HAL_UART_Receive_IT (uart, data->rx_buff_ptr, 1); 
}

//addr1 addr0 channel1 channel0 count1 count0 packetId3 packetId2 packetId1 packetId0 command3 command2 command1 command0 /* data (16 - 1008) */ crc16_1 crc16_0 / 
//maxLenght 1024B  minLenght 32B packetInfo 16B
NOS_Short currCRC;

bool NOS_UART_ParsePacket(NOS_UART_Struct* data,UART_Message* message)
{
    int currPos = 0;

    message->address.bytes[1] = data->rx_buff[currPos++];
    message->address.bytes[0] = data->rx_buff[currPos++];

    message->channel.bytes[1] = data->rx_buff[currPos++];
    message->channel.bytes[0] = data->rx_buff[currPos++];

    message->byteCount.bytes[1] = data->rx_buff[currPos++];
    message->byteCount.bytes[0] = data->rx_buff[currPos++];

    if(message->byteCount.data > 1024)
    {
        return false;
    }

    message->packetId.bytes[3] = data->rx_buff[currPos++];
    message->packetId.bytes[2] = data->rx_buff[currPos++];
    message->packetId.bytes[1] = data->rx_buff[currPos++];
    message->packetId.bytes[0] = data->rx_buff[currPos++];

    message->command.bytes[3] = data->rx_buff[currPos++];
    message->command.bytes[2] = data->rx_buff[currPos++];
    message->command.bytes[1] = data->rx_buff[currPos++];
    message->command.bytes[0] = data->rx_buff[currPos++];

    for(int i = 0; i < message->byteCount.data - 16; i++)
    {
        message->data[i] = data->rx_buff[currPos++];
    }

    message->CRC16.bytes[1] = data->rx_buff[currPos++];
    message->CRC16.bytes[0] = data->rx_buff[currPos++];

    data->value.data = GetCRC16(&data->rx_buff,message->byteCount.data - 2);

    if(data->value.data == message->CRC16.data)
    {
        return true;
    }

    if(message->address.data != 0)
    {
        if(message->channel.data != 0)
        {
            if(message->byteCount.data != 0)
            {
                return true;            
            }
        }
    }

}

bool NOS_UART_PacketApprovedNotice(UART_Message* message,UART_HandleTypeDef* uart)
{
    uint8_t buff[32];
    int currPos = 0;

    buff[currPos++] = message->address.bytes[1];
    buff[currPos++] = message->address.bytes[0];

    buff[currPos++] = message->channel.bytes[1];
    buff[currPos++] = message->channel.bytes[0];

    buff[currPos++] = message->byteCount.bytes[1];
    buff[currPos++] = message->byteCount.bytes[0];

    buff[currPos++] = message->packetId.bytes[3];
    buff[currPos++] = message->packetId.bytes[2];
    buff[currPos++] = message->packetId.bytes[1];
    buff[currPos++] = message->packetId.bytes[0];

    buff[currPos++] = message->command.bytes[3];
    buff[currPos++] = message->command.bytes[2];
    buff[currPos++] = message->command.bytes[1];
    buff[currPos++] = message->command.bytes[0];

    for(int i = 0; i < 16; i++)
    {
        buff[currPos++] = 0xFF;
    }

    buff[currPos++] = message->CRC16.bytes[1];
    buff[currPos++] = message->CRC16.bytes[0];

    HAL_UART_Transmit(uart,buff,32,1000);

}


bool NOS_UART_CheckReceive(NOS_UART_Struct* data)
{
    return data->rx_flag;   
}

uint8_t* NOS_UART_GetReceivedData(NOS_UART_Struct* data)
{
    return data->rx_buff;
}

void NOS_UART_EndReceive(NOS_UART_Struct* data)
{
    data->rx_flag = false;
}
