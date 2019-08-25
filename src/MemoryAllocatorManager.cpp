#include "MemoryAllocatorManager.h"

#ifdef WINDOWS
	#include <windows.h>
#elif UNIX
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/sysctl.h>
	#include <sys/vmmeter.h>
	#include <sys/limits.h>
	#include <vm/vm_param.h>

	struct vmtotal getVMinfo() {
		struct vmtotal vm_info;
		int mib[2];

		mib[0] = CTL_VM;
		mib[1] = VM_TOTAL;

		size_t len = sizeof(vm_info);
		sysctl(mib, 2, &vm_info, &len, NULL, 0);

		return vm_info;
	}

	int getSysCtl(int top_level, int next_level) {
		int mib[2], ctlvalue;
		size_t len;

		mib[0] = top_level;
		mib[1] = next_level;
		len = sizeof(ctlvalue);

		sysctl(mib, 2, &ctlvalue, &len, NULL, 0);

		return ctlvalue;
	}
#endif

static void* initialPointer = NULL;
static void* lastPointer = NULL;
static void* currentPointer = NULL;

MemoryAllocatorManager::MemoryAllocatorManager() 
{
	;
}

void MemoryAllocatorManager::init(size_t initialSize)
{
	initialPointer = std::malloc(initialSize);

	assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = ((int*)initialPointer) + initialSize;
}

void MemoryAllocatorManager::free(void* buffer)
{
	currentPointer = buffer;
}

size_t MemoryAllocatorManager::deviceMemorySize()
{
#ifdef WINDOWS
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return (size_t) status.ullTotalPhys;
#elif UNIX
	return vmsize.t_rm;
#endif
}

void* MemoryAllocatorManager::alloc(size_t size)
{
	assert(!hasAvailableMemory(size));

	void* buffer = currentPointer;

	currentPointer = ((int*)currentPointer) + size;

	return buffer;
}

void* MemoryAllocatorManager::alloc(size_t count, size_t size)
{
	return MemoryAllocatorManager::alloc(count * size);
}

void MemoryAllocatorManager::resize(size_t newSize)
{
	initialPointer = std::realloc(initialPointer, newSize);

	assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = ((int*)initialPointer) + newSize;
}

bool MemoryAllocatorManager::hasAvailableMemory(size_t size)
{
	return ((int*)currentPointer) + size - ((int*)lastPointer) > 0;
}

size_t MemoryAllocatorManager::memorySize()
{
	return ((int*)lastPointer) - ((int*)initialPointer);
}

size_t MemoryAllocatorManager::availableMemorySize()
{
	return ((int*)lastPointer) - ((int*)currentPointer);
}

void MemoryAllocatorManager::release()
{
	std::free(initialPointer);

	initialPointer = NULL;
	lastPointer = NULL;
	currentPointer = NULL;
}