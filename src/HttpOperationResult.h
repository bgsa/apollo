#pragma once

#include <iostream>

struct DownloadData
{
	void* content = malloc(1);
	size_t size = 0;
};

class HttpOperationResult
{
public:
	long httpStatusCode;
	DownloadData data;

	double connectionSpeed;
	double downloadTime;
	double totalSize;

	~HttpOperationResult();
};

