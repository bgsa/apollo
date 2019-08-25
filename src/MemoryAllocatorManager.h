#ifndef MEMORY_ALLOCATOR_MANAGER
#define MEMORY_ALLOCATOR_MANAGER

#include "apollo.h"

#define ONE_MEGA sizeof(char) * 1024 * 1024
#define DEFAULT_SIZE ONE_MEGA * 512

#define NEW(type) (type*)MemoryAllocatorManager::alloc(sizeof(type))
#define NEW_ARRAY(count, type) (type*) MemoryAllocatorManager::alloc(count, sizeof(type))
#define RELEASE(object) MemoryAllocatorManager::free(object)

class MemoryAllocatorManager
{
private:
	MemoryAllocatorManager();

public:

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	API_INTERFACE static void init(size_t initialSize = DEFAULT_SIZE);

	/// <summary>
	/// Get the memory size available in manager
	/// </summary>
	API_INTERFACE static size_t memorySize();

	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	API_INTERFACE static size_t deviceMemorySize();

	/// <summary>
	/// Get the available memory size in manager
	/// </summary>
	API_INTERFACE static size_t availableMemorySize();

	/// <summary>
	/// Check if the manager has available memory
	/// </summary>
	API_INTERFACE static bool hasAvailableMemory(size_t size);

	/// <summary>
	/// Alloc in the memory
	/// </summary>
	API_INTERFACE static void* alloc(size_t size);

	/// <summary>
	/// Alloc (count * size) in the memory
	/// </summary>
	API_INTERFACE static void* alloc(size_t count, size_t size);

	/// <summary>
	/// Resize the current memory in manager
	/// </summary>
	API_INTERFACE static void resize(size_t newSize);

	/// <summary>
	/// Release the memory
	/// </summary>
	API_INTERFACE static void free(void* buffer);
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	API_INTERFACE static void release();
};

#endif