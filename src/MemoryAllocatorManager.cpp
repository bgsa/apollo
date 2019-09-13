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

std::mutex locker;

static void* initialPointer = NULL;
static void* lastPointer = NULL;
static void* currentPointer = NULL;

MemoryAllocatorManager::MemoryAllocatorManager()
{
	;
}

void MemoryAllocatorManager::init(size_t initialSize) noexcept
{
	locker.lock();

	initialPointer = std::malloc(initialSize);

	assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = ((int*)initialPointer) + initialSize;

	locker.unlock();
}

void MemoryAllocatorManager::free(void* buffer) noexcept
{
	locker.lock();

	assert(buffer >= initialPointer && buffer <= lastPointer);

	if (currentPointer > buffer) // memory has already freed by previous pointer
		currentPointer = buffer;

	locker.unlock();
}

size_t MemoryAllocatorManager::deviceMemorySize() noexcept
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

void* MemoryAllocatorManager::alloc(size_t size) noexcept
{
	locker.lock();

	assert(hasAvailableMemory(size));

	void* buffer = currentPointer;

	currentPointer = ((int*)currentPointer) + size;

	locker.unlock();
	return buffer;
}

void* MemoryAllocatorManager::alloc(size_t count, size_t size) noexcept
{
	return MemoryAllocatorManager::alloc(count * size);
}

void* MemoryAllocatorManager::copy(void* source, size_t size) noexcept
{
	void* newBuffer = ALLOC_SIZE(size);

	std::memcpy(newBuffer, source, size);

	return newBuffer;
}

void MemoryAllocatorManager::resize(size_t newSize) noexcept
{
	locker.lock();

	initialPointer = std::realloc(initialPointer, newSize);

	assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = ((int*)initialPointer) + newSize;

	locker.unlock();
}

bool MemoryAllocatorManager::hasAvailableMemory(size_t size) noexcept
{
	return ((int*)lastPointer) - ((int*)currentPointer) + size > 0;
}

size_t MemoryAllocatorManager::memorySize() noexcept
{
	return ((int*)lastPointer) - ((int*)initialPointer);
}

size_t MemoryAllocatorManager::availableMemorySize() noexcept
{
	return ((int*)lastPointer) - ((int*)currentPointer);
}

void MemoryAllocatorManager::release() noexcept
{
	locker.lock();

	lastPointer = NULL;
	currentPointer = NULL;

	std::free(initialPointer);

	initialPointer = NULL;

	locker.unlock();
}