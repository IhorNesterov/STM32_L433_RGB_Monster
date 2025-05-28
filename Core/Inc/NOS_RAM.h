#include "NOS_Includes.h"

#define RAM_OVERFLOW 0x01

#define RAM_CHUNK_MAX_COUNT 128
#define RAM_SIZE 16384

typedef struct NOS_RAM_Chunk_T
{
    void* dataPtr;
    size_t size;
    bool isFree;
}NOS_RAM_Chunk;


typedef struct NOS_RAM_Struct_T
{
    NOS_RAM_Chunk chunks[RAM_CHUNK_MAX_COUNT];
    uint8_t data[RAM_SIZE];
    uint8_t* topPointer;
    uint8_t chunksCount;
    uint16_t totalSize;
}NOS_RAM_Struct;

void NOS_RAM_Init(NOS_RAM_Struct* ram)
{
    for(int i = 0; i < RAM_CHUNK_MAX_COUNT; i++)
    {
        ram->chunks[i].dataPtr = NULL;
        ram->chunks[i].size = 0;
    }

    for(int i = 0; i < RAM_SIZE; i++)
    {
        ram->data[i] = 0xFF;
    }

    ram->topPointer = ram->data;
    ram->chunksCount = 0;
    ram->totalSize = 0;
}

inline void ram_chunk_setBusy(NOS_RAM_Chunk* chunk)
{
    chunk->isFree = false;
}

void* NOS_RAM_Alloc(NOS_RAM_Struct* ram,size_t size)
{
    void* result = NULL;

    for(int i = 0; i < RAM_CHUNK_MAX_COUNT; i++)
    {
        if(ram->chunks[i].isFree)
        {
            if(ram->chunks[i].size == size)
            {
                result = ram->chunks[i].dataPtr;

                ram_chunk_setBusy(&ram->chunks[i]);

                return result;
            }
        }
    }

    if(ram->totalSize + size > RAM_SIZE)
    {
        return NULL;
    }

    uint16_t startPos = ram->totalSize;

    ram->totalSize += size;

    for(int i = startPos; i < ram->totalSize; i++)
    {
        ram->data[i] = 0x00;
    }

    result = ram->topPointer;

    ram->topPointer = &ram->data[ram->totalSize];

    ram->chunks[ram->chunksCount].dataPtr = result;
    ram->chunks[ram->chunksCount].size = size;

    ram->chunksCount++;

    return result;
}

void NOS_RAM_Free(NOS_RAM_Struct* ram, void* ptr)
{

    for(int i = 0; i < ram->chunksCount; i++)
    {
        if(ram->chunks[i].dataPtr == ptr)
        {
            uint8_t* dptr = (uint8_t*)ptr;
            for(int x = 0; x < ram->chunks[i].size; x++)
            {
                *dptr = 0xFF;
                dptr++;
            }

            ram->chunks[i].isFree = true;
        }
    }

    ptr = NULL;
}