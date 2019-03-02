#pragma once

#include "apollo.h"
#include <cstdio>
#include <iostream>
#include <string>
#include "StringHelper.h"

#ifdef ANDROID
#include <android/log.h>
#endif

using namespace std;

class Log
{
public:

	API_INTERFACE static void error(string errorMessage)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", errorMessage.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", errorMessage.c_str(), END_OF_LINE);
#endif
	}

	API_INTERFACE static void info(string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_INFO, "INFO", "%s", message.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif		
	}

	API_INTERFACE static void debug(string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "%s", message.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif		
	}

	API_INTERFACE static void onError(int errorCode, const char* description)
	{
		error("Error: " + string(description));
	}

};
