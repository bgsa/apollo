#pragma once

#ifdef GLFW

#include <algorithm>
#include "apollo.h"
#include "WindowInputDevice.h"

class WindowInputDeviceGLFW : public WindowInputDevice
{
private:
	WindowInputDeviceGLFW();

	GLFWwindow* window;
	vector<WindowInputDeviceHandler*> handlers;

public:

	API_INTERFACE static WindowInputDeviceGLFW* getInstance();

	API_INTERFACE void init(GLFWwindow* window);
	API_INTERFACE void update(long long elapsedTime);

	API_INTERFACE void close();
	API_INTERFACE void resize(int width, int height);

	API_INTERFACE void addHandler(WindowInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(WindowInputDeviceHandler* handler);
};

#endif