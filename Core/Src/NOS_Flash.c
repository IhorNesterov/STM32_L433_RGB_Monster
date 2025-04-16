#include "NOS_Flash.h"

bool NOS_FlashMemory_Struct_Validate(NOS_Flash_Memory_Struct* flashMemory)
{
	bool validated = true;

	size_t _size = flashMemory->totalSize;
	uint32_t address = flashMemory->baseFlashAddress;

	for(int i = 0; i < _size; i++)
	{
		if(*(uint64_t*)address == 0xFFFFFFFFFFFFFFFF)
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

		if(chunk->size % 8 != 0)
		{
			flashMemory->totalSize += chunk->size % 8;
		}
	}
}

size_t NOS_FlashMemory_Struct_GetTotalSize(NOS_Flash_Memory_Struct* flashMemory)
{
	return flashMemory->totalSize;
}

void NOS_Flash_Memory_Struct_Save(NOS_Flash_Memory_Struct* flashMemory)
{
	uint32_t address = flashMemory->baseFlashAddress;

	uint32_t u64Count = 0;

	uint16_t sizes[FLASH_CHUNKS_MAX_COUNTER];

	for(int i = 0; i < FLASH_CHUNKS_MAX_COUNTER; i++)
	{
		sizes[i] = 0;
	}

	for(int i = 0; i < flashMemory->chunksCounter; i++) //checking every chunk for size an adding to u64Count
	{
		u64Count += flashMemory->chunks[i].size / 8;
		sizes[i] += flashMemory->chunks[i].size / 8;
	}

	uint64_t data_to_flash[u64Count];
	uint32_t dataCounter = 0;

	for(int i = 0; i < u64Count; i++)
	{
		data_to_flash[i] = 0;
	}

	for(int currChunk = 0; currChunk < flashMemory->chunksCounter; currChunk++)
	{
		uint64_t* pointer = flashMemory->chunks[currChunk].dataPointer;
		uint64_t* bufferPointer = &data_to_flash[dataCounter];

		uint16_t currChunkU64Size = sizes[currChunk];

		for(int i = 0; i < currChunkU64Size; i++)
		{
			data_to_flash[dataCounter] = *pointer;
			pointer++;
			dataCounter++;
			bufferPointer++;
		}
	}

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	
	volatile HAL_StatusTypeDef status = HAL_OK;
	volatile uint32_t write_cnt=0, index=0;

	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = FLASH_PAGE_NUMBER;
	EraseInitStruct.NbPages = 1;
	uint32_t PageError;
	status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	
	

	while(index < u64Count)
	{
		if (status == HAL_OK)
		{
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address+write_cnt, data_to_flash[index]);
			if(status == HAL_OK)
			{
				write_cnt += 8;
				index++;
			}
		}
	}

	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}

void NOS_Flash_Memory_Struct_Load(NOS_Flash_Memory_Struct* flashMemory)
{
	uint64_t data = 0;
	uint16_t lastBytes = 0;

	for(int currChunk = 0; currChunk < flashMemory->chunksCounter; currChunk++)
	{
		uint32_t currAddress = flashMemory->chunks[currChunk].flashAddress;
		uint64_t* pointer = flashMemory->chunks[currChunk].dataPointer;
		uint16_t currChunkU64Size = flashMemory->chunks[currChunk].size / 8;

		for(int i = 0; i < currChunkU64Size; i++)
		{	
			data = *(uint64_t*)currAddress;
			*pointer = data;
			currAddress += 8;
			pointer++;
		}
	}
}

uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}

uint32_t GetAddress(uint32_t page)
{
	uint32_t address = NULL;

	return FLASH_BASE + FLASH_PAGE_SIZE * page;
}