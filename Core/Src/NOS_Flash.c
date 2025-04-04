#include "NOS_Flash.h"

bool NOS_FlashMemory_Struct_Validate(NOS_Flash_Memory_Struct* flashMemory)
{
	bool validated = true;

	size_t _size = flashMemory->totalSize;
	uint32_t address = flashMemory->baseFlashAddress;

	for(int i = 0; i < _size; i++)
	{
		if(*(uint32_t*)address == 0xFFFFFFFF)
		{
			validated = false;
		}
	}

	return validated;
}

void NOS_Flash_Chunk_Init(NOS_Flash_Chunk* chunk,void* dataPtr,size_t size)
{
	chunk->dataPointer = dataPtr;
	chunk->size = size;
	chunk->flashAddress = 0;
}

void NOS_FlashMemory_Struct_Init(NOS_Flash_Memory_Struct* flashMemory,uint32_t baseAddress)
{
	flashMemory->baseFlashAddress = baseAddress;
	flashMemory->chunksCounter = 0;
}

void NOS_Flash_Chunk_Copy(NOS_Flash_Chunk* destination,NOS_Flash_Chunk* source)
{
	destination->dataPointer = source->dataPointer;
	destination->size = source->size;
	destination->flashAddress = 0;
}

void NOS_FlashMemory_Struct_AddChunk(NOS_Flash_Memory_Struct* flashMemory, NOS_Flash_Chunk* chunk)
{
	if(flashMemory->chunksCounter < FLASH_CHUNKS_MAX_COUNTER)
	{
		NOS_Flash_Chunk_Copy(&flashMemory->chunks[flashMemory->chunksCounter],chunk);
		flashMemory->chunks[flashMemory->chunksCounter].flashAddress = flashMemory->baseFlashAddress + flashMemory->totalSize;
		flashMemory->chunksCounter++;
		flashMemory->totalSize += chunk->size;
	}
}

size_t NOS_FlashMemory_Struct_GetTotalSize(NOS_Flash_Memory_Struct* flashMemory)
{
	return flashMemory->totalSize;
}

void NOS_Flash_Memory_Struct_Save(NOS_Flash_Memory_Struct* flashMemory)
{
	uint32_t address = flashMemory->baseFlashAddress;
	uint32_t u32Count = flashMemory->totalSize/4;
	uint32_t data_to_flash[u32Count];
	uint32_t dataCounter = 0;
	uint8_t pageCount = (flashMemory->totalSize / FLASH_PAGE_SIZE) + 1;

	for(int currChunk = 0; currChunk < flashMemory->chunksCounter; currChunk++)
	{
		uint32_t* pointer = flashMemory->chunks[currChunk].dataPointer;
		uint32_t currChunkU32Size = flashMemory->chunks[currChunk].size/4;

		for(int i = 0; i < currChunkU32Size; i++)
		{
			data_to_flash[dataCounter] = *pointer;
			pointer++;
			dataCounter++;
		}
	}

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	
	volatile HAL_StatusTypeDef status = HAL_OK;
	volatile uint32_t write_cnt=0, index=0;

	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = 200;
	EraseInitStruct.NbPages = pageCount;
	uint32_t PageError;
	status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	
	

	while(index < u32Count)
	{
		if (status == HAL_OK)
		{
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, address+write_cnt, data_to_flash[index]);
			if(status == HAL_OK)
			{
				write_cnt += 4;
				index++;
			}
		}
	}

	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}

void NOS_Flash_Memory_Struct_Load(NOS_Flash_Memory_Struct* flashMemory)
{
	for(int currChunk = 0; currChunk < flashMemory->chunksCounter; currChunk++)
	{
		uint32_t currAddress = flashMemory->chunks[currChunk].flashAddress;
		uint32_t* pointer = flashMemory->chunks[currChunk].dataPointer;
		uint32_t currChunkU32Size = flashMemory->chunks[currChunk].size/4;
		uint32_t data = 0;

		for(int i = 0; i < currChunkU32Size; i++)
		{	
			data = *(uint32_t*)currAddress;
			*pointer = data;
			currAddress += 4;
			pointer++;
		}

	}
}