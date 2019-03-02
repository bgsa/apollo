#pragma once

#ifdef GLFW

#include "apollo.h"
#include <algorithm>
#include "PointerInputDevice.h"
#include "PointerInputDeviceHandler.h"

class PointerInputDeviceGLFW : public PointerInputDevice
{
private:
		
public:
	API_INTERFACE void init(GLFWwindow* window);
	API_INTERFACE void update(long long elapsedTime);
	
	API_INTERFACE void addHandler(PointerInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(PointerInputDeviceHandler* handler);
};

#endif