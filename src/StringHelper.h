#pragma once

#include "apollo.h"
#include <sstream>

#ifdef __cplusplus
	#include <vector>
#endif // __cplusplus

#define DEFAULT_STRING_LENGTH 256

class StringHelper
{
public:

	API_INTERFACE static inline sp_char* crate(sp_uint length = DEFAULT_STRING_LENGTH)
	{
		sp_char* buffer = ALLOC_ARRAY(sp_char, length);
		buffer[length] = END_OF_STRING;

		return buffer;
	}

	API_INTERFACE static inline void copy(const sp_char* source, sp_char* destination, sp_uint maxLength = 1024)
	{
		const sp_uint sourceLength = strnlen_s(source, maxLength);

		strcpy_s(destination, SIZEOF_CHAR * (sourceLength + 1), source);

		destination[sourceLength] = '\0';
	}

	API_INTERFACE static inline void append(const sp_char* source, sp_char* destination, sp_uint destinationLength)
	{
		strcat_s(destination, SIZEOF_CHAR * destinationLength, source);
	}
	
#ifdef __cplusplus

	static std::string toLowerCase(std::string value)
	{
		sp_char* stringAsArray = (sp_char*)value.c_str();

		for (sp_uint i = 0; i < value.length(); i++)
			stringAsArray[i] = (sp_char) tolower(stringAsArray[i]);

		return std::string(stringAsArray);
	}

	static std::string toUpperCase(std::string value)
	{
		sp_char* stringAsArray = (sp_char*) value.c_str();

		for (sp_uint i = 0; i < value.length(); i++)
			stringAsArray[i] = (sp_char) toupper(stringAsArray[i]);

		return std::string(stringAsArray);
	}

	static sp_bool startWith(std::string text, std::string value)
	{
		sp_uint textLength = text.length();
		sp_uint valueLength = value.length();

		if (valueLength > textLength)
			return false;
				
		std::string startSubstring = text.substr(0, valueLength);
		
		return std::strcmp(startSubstring.c_str(), value.c_str()) == 0;
	}

	static sp_bool endWith(const sp_char* text, const sp_char* suffix)
	{
		if (text == nullptr || suffix == nullptr)
			return false;

		sp_uint textLength = strlen(text);
		sp_uint suffixLength = strlen(suffix);

		if (suffixLength > textLength)
			return false;

		return std::strncmp(text + textLength - suffixLength, suffix, suffixLength) == 0;
	}

	template <typename T>
	static std::string toString(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	static std::vector<std::string> split(std::string text, const sp_char* separator)
	{
		std::vector<std::string> result;
		sp_char *nextToken;

		sp_char* values = strtok_s( (sp_char*) text.c_str(), separator, &nextToken);

		while (values != nullptr)
		{
			result.push_back(values);
			values = strtok_s(nullptr, separator, &nextToken);
		}

		return result;
	}

#endif // __cplusplus

};

