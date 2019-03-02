#pragma once

#ifdef WINDOWS

#include <fstream>
#include <iostream>

#include "apollo.h"

#ifdef APIENTRY // avoid Windows.h redefine APIENTRY symbol
	#undef APIENTRY
#endif
#include <Windows.h>

#include "StringHelper.h"
#include "IFileManager.h"
#include "IFile.h"
#include "FileWindows.h"

class FileManagerWindows : public IFileManager
{
public:
	API_INTERFACE std::vector<std::string> getFilesFromResource();

	API_INTERFACE std::vector<std::string> getFilesFromFolder(std::string folder, std::string suffix = "");

	API_INTERFACE std::string readTextFile(const char * filename);

	API_INTERFACE char* readBinaryFile(const char * filename, size_t& size);
    
	API_INTERFACE  bool exists(const char * filename);

	API_INTERFACE IFile* open(std::string filename);
};

#endif