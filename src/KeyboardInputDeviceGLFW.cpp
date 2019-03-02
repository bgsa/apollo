#include "KeyboardInputDeviceGLFW.h"

#ifdef GLFW

std::vector<KeyboardInputDeviceHandler*> handlersKeyboard;
GLFWwindow* keyboardWindow;

void onKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		for ( KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyDown(key);

	if (action == GLFW_RELEASE)
		for (KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyUp(key);
}

bool isKeyPressedA(int virtualKey)
{
	int state = glfwGetKey(keyboardWindow, virtualKey);

	return state == GLFW_PRESS;
}

void KeyboardInputDeviceGLFW::init(GLFWwindow* window)
{
	this->window = window;
	keyboardWindow = window;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1); // for pooling do not lose any event

	glfwSetKeyCallback(window, onKeyboardEvent);
}

void KeyboardInputDeviceGLFW::addHandler(KeyboardInputDeviceHandler* handler)
{
	handler->init(&isKeyPressedA);
	handlersKeyboard.push_back(handler);
}

void KeyboardInputDeviceGLFW::removeHandler(KeyboardInputDeviceHandler* handler)
{
	vector<KeyboardInputDeviceHandler*>::iterator item = std::find(handlersKeyboard.begin(), handlersKeyboard.end(), handler);

	if (item != handlersKeyboard.end())
		handlersKeyboard.erase(item);
}

void KeyboardInputDeviceGLFW::update(long long elapsedTime)
{

}

bool KeyboardInputDeviceGLFW::isKeyPressed(int virtualKey)
{
	return isKeyPressedA(virtualKey);
}

#endif