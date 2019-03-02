#pragma once

#include "apollo.h"
#include <sstream>
#include <vector>

class StringHelper
{
public:

	static std::string toLowerCase(std::string value)
	{
		char* stringAsArray = (char*)value.c_str();

		for (size_t i = 0; i < value.length(); i++)
			stringAsArray[i] = (char) tolower(stringAsArray[i]);

		return std::string(stringAsArray);
	}

	static std::string toUpperCase(std::string value)
	{
		char* stringAsArray = (char*) value.c_str();

		for (size_t i = 0; i < value.length(); i++)
			stringAsArray[i] = (char) toupper(stringAsArray[i]);

		return std::string(stringAsArray);
	}

	static bool startWith(std::string text, std::string value)
	{
		size_t textLength = text.length();
		size_t valueLength = value.length();

		if (valueLength > textLength)
			return false;
				
		std::string startSubstring = text.substr(0, valueLength);
		
		return std::strcmp(startSubstring.c_str(), value.c_str()) == 0;
	}

	static bool endWith(const char * text, const char * suffix)
	{
		if (text == nullptr || suffix == nullptr)
			return false;

		size_t textLength = strlen(text);
		size_t suffixLength = strlen(suffix);

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

	static std::vector<std::string> split(std::string text, const char* separator)
	{
		std::vector<std::string> result;
		char *nextToken;

		char* values = strtok_s( (char*) text.c_str(), separator, &nextToken);

		while (values != nullptr)
		{
			result.push_back(values);
			values = strtok_s(nullptr, separator, &nextToken);
		}

		return result;
	}

};

