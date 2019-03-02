#pragma once

#include "apollo.h"
#include "ColorRGB.h"

class Image 
{
private:
	
protected:
	int width;
	int height;
	unsigned char* data;
	unsigned int colorFormat;
	
public:
    Image();   
	virtual ~Image();
	
	int getWidth();
	int getHeight();	
	unsigned char * getData();
	unsigned int getColorFormat();
	virtual ColorRGBc getPixelRGB(int x, int y) = 0;    
};
