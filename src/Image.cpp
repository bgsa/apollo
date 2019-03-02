#include "Image.h"

Image::Image() {
}

int Image::getWidth() 
{
	return width;
}

int Image::getHeight()
{
	return height;
}

unsigned char * Image::getData() 
{
	return data;
}

unsigned int Image::getColorFormat()
{
	return colorFormat;
}

Image::~Image() 
{
	if (data != nullptr)
		delete[] data;
}