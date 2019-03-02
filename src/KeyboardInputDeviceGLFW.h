#pragma once

#ifdef GLFW

#include "KeyboardInputDevice.h"
#include <algorithm>

using namespace std;

class KeyboardInputDeviceGLFW : public KeyboardInputDevice
{
private:
	GLFWwindow* window;
	
public:
	API_INTERFACE void init(GLFWwindow*);
	API_INTERFACE void update(long long elapsedTime);

	API_INTERFACE bool isKeyPressed(int virtualKey);

	API_INTERFACE void addHandler(KeyboardInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(KeyboardInputDeviceHandler* handler);
};

#endif