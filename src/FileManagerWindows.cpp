#include "FileManagerWindows.h"

#ifdef WINDOWS

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>

bool checkFile(std::ifstream& file, const char * filename)
{
    if ( file.fail() || file.bad() || ! file.is_open() ) 
    {
		const size_t errorMessageLength = 1024;
		char errorMessage[errorMessageLength];
		strerror_s(errorMessage, errorMessageLength, errno);

		std::string str1 = std::string(errorMessage);
		std::string str = ": ";
		std::string message = str1 + str + filename;
        
		Log::error(message);
        
        return false;
    }
    
    return true;
}

std::vector<std::string> FileManagerWindows::getFilesFromResource()
{
	std::vector<std::string> files;
	files.push_back("teste.txt");
	return files;
}


std::vector<std::string> FileManagerWindows::getFilesFromFolder(std::string folder, std::string suffix)
{
	std::vector<std::string> files;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			bool isDirectory = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			
			if ( ! isDirectory )
			{
				std::string filename = fd.cFileName;

				if (suffix.empty())
					files.push_back(filename);
				else
					if (StringHelper::endWith(filename.c_str(), suffix.c_str()))
						files.push_back(filename);
			}
		} while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}

	return files;
}

bool FileManagerWindows::exists(const char * filename)
{
	std::ifstream file(filename);
    return file.good();
}

std::string FileManagerWindows::readTextFile(const char * filename)
{
	std::ifstream file(filename);

	file.seekg(0, std::ios::end);

	size_t size = (size_t) file.tellg();

	std::string content(size, ' ');

	file.seekg(0);
	file.read(&content[0], size);

	return content;
}

char* FileManagerWindows::readBinaryFile(const char * filename, size_t& size)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	size = (size_t) file.tellg();
	file.seekg(0, std::ios::beg);

	char* content = (char*) malloc(size);

	file.read(content, size);

	return content;
}

IFile* FileManagerWindows::open(std::string filename)
{
	FileWindows* file = new FileWindows(filename);
	return file;
}

#endif