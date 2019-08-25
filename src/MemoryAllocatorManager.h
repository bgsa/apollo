#ifndef MEMORY_ALLOCATOR_MANAGER
#define MEMORY_ALLOCATOR_MANAGER

#include "apollo.h"
#include <mutex>

#define ONE_MEGA sizeof(char) * 1024 * 1024
#define DEFAULT_SIZE ONE_MEGA * 512

#define ALLOC(type) (type*)MemoryAllocatorManager::alloc(sizeof(type))
#define ALLOC_SIZE(size) MemoryAllocatorManager::alloc(size)
#define ALLOC_ARRAY(type, count) (type*) MemoryAllocatorManager::alloc(count, sizeof(type))
#define ALLOC_RELEASE(objects) MemoryAllocatorManager::free(objects)
#define ALLOC_NEW(type) new (MemoryAllocatorManager::alloc(sizeof(type))) type
#define ALLOC_DELETE(type) delete type; MemoryAllocatorManager::free(type)
#define ALLOC_COPY(source, type, count) (type*) MemoryAllocatorManager::copy(source, sizeof(type) * count)

class MemoryAllocatorManager
{
private:
	MemoryAllocatorManager();

public:

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	API_INTERFACE static void init(size_t initialSize = DEFAULT_SIZE) noexcept;

	/// <summary>
	/// Get the memory size available in manager
	/// </summary>
	API_INTERFACE static size_t memorySize() noexcept;

	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	API_INTERFACE static size_t deviceMemorySize() noexcept;

	/// <summary>
	/// Get the available memory size in manager
	/// </summary>
	API_INTERFACE static size_t availableMemorySize() noexcept;

	/// <summary>
	/// Check if the manager has available memory
	/// </summary>
	API_INTERFACE static bool hasAvailableMemory(size_t size) noexcept;

	/// <summary>
	/// Alloc in the memory
	/// </summary>
	API_INTERFACE static void* alloc(size_t size) noexcept;

	/// <summary>
	/// Alloc (count * size) in the memory
	/// </summary>
	API_INTERFACE static void* alloc(size_t count, size_t size) noexcept;

	/// <summary>
	/// Copy the source to a new memory buffer
	/// </summary>
	API_INTERFACE static void* copy(void* source, size_t size) noexcept;

	/// <summary>
	/// Resize the current memory in manager
	/// </summary>
	API_INTERFACE static void resize(size_t newSize) noexcept;

	/// <summary>
	/// Release the memory
	/// </summary>
	API_INTERFACE static void free(void* buffers) noexcept;
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	API_INTERFACE static void release() noexcept;
};

#endif