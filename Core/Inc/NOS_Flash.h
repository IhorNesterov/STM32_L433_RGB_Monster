#ifndef NOS_FLASH
#define NOS_FLASH

#include "NOS_Includes.h"

#define FLASH_PAGE_SIZE 0x400
#define FLASH_STORAGE_A 0x0800A000

/**
  * @brief  Flash chunk init
  * @param chunk pointer on flash chunk
  * @param dataPtr pointer in ram on object to store
  * @param size size of object in bytes(size_t)
  * @retval void,in future will be NOS_System_State
  */
void NOS_Flash_Chunk_Init(NOS_Flash_Chunk* chunk,void* dataPtr,size_t size);

/**
  * @brief  Flash chunk copy (a.k.a '=' operator overload)
  * @param destination pointer on flash chunk copy to
  * @param source pointer on flash chunk copy from
  * @retval void,in future will be NOS_System_State
  */
void NOS_Flash_Chunk_Copy(NOS_Flash_Chunk* destination,NOS_Flash_Chunk* source);

/**
  * @brief  Flash memory struct validate(check that data in flash is already initialized and not 0xFFFFFFFF)
  * @param flashMemory pointer on flash memory struct
  * @retval bool (if true data is initialized)
  */
bool NOS_FlashMemory_Struct_Validate(NOS_Flash_Memory_Struct* flashMemory);

/**
  * @brief  Flash Memory struct initialization(set base flash address and set all internal struct params to default)
  * @param flashMemory pointer on flash memory struct
  * @param baseAddress pointer on first flash address store to
  * @retval void,in future will be NOS_System_State
  */
void NOS_FlashMemory_Struct_Init(NOS_Flash_Memory_Struct* flashMemory,uint32_t baseAddress);

/**
  * @brief  Add chunk to struct (adding chunk by init of internal chunk,changing total used flash data)
  * @param flashMemory pointer on flash memory struct
  * @param chunk pointer on source chunk 
  * @retval void,in future will be NOS_System_State
  */
void NOS_FlashMemory_Struct_AddChunk(NOS_Flash_Memory_Struct* flashMemory, NOS_Flash_Chunk* chunk);

/**
  * @brief  Flash Memory struct total size getter
  * @param flashMemory pointer on flash memory struct
  * @retval size_t total size of used flash memory
  */
size_t NOS_FlashMemory_Struct_GetTotalSize(NOS_Flash_Memory_Struct* flashMemory);

/**
  * @brief  Flash Memory save (updating flash memory from chunks)
  * @param flashMemory pointer on flash memory struct
  * @retval void,in future will be NOS_System_State
  */
void NOS_Flash_Memory_Struct_Save(NOS_Flash_Memory_Struct* flashMemory);

/**
  * @brief  Flash Memory load (updating ram memory from flash)
  * @param flashMemory pointer on flash memory struct
  * @retval void,in future will be NOS_System_State
  */
void NOS_Flash_Memory_Struct_Load(NOS_Flash_Memory_Struct* flashMemory);


#endif