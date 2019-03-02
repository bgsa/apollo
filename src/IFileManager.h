#pragma once

#include "IFile.h"

class IFileManager
{
public:
	virtual ~IFileManager() {};

	virtual std::vector<std::string> getFilesFromResource() = 0;

	virtual std::vector<std::string> getFilesFromFolder(std::string folder, std::string suffix = "") = 0;

	virtual std::string readTextFile(const char * filename) = 0;

	virtual char* readBinaryFile(const char * filename, size_t& size) = 0;

	virtual bool exists(const char * filename) = 0;

	virtual IFile* open(std::string filename) = 0;
};