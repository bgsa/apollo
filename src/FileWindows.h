#ifdef WINDOWS

#pragma once

#include <fstream>
#include "apollo.h"
#include "IFile.h"

class FileWindows : public IFile
{
private:
	FILE *file;

public:
	API_INTERFACE FileWindows(std::string filename);

	API_INTERFACE void read(void* buffer, size_t size, size_t count = 1);
	API_INTERFACE void seek(long offset);
	API_INTERFACE void close();

	API_INTERFACE ~FileWindows();
};

#endif