#pragma once

#ifdef GLFW

#include "DisplayDevice.h"

class DisplayDeviceGLFW : public DisplayDevice
{
private:
	GLFWwindow* window;

public:
	API_INTERFACE void API_INTERFACE init(GLFWwindow* window);
	API_INTERFACE void API_INTERFACE swapBuffer() override;
};

#endif