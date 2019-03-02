#include "WindowInputDeviceGLFW.h"

#ifdef GLFW

WindowInputDeviceGLFW* instanceWindowDevice;

WindowInputDeviceGLFW::WindowInputDeviceGLFW()
{
}

WindowInputDeviceGLFW* WindowInputDeviceGLFW::getInstance()
{
	if (instanceWindowDevice == nullptr)
		instanceWindowDevice = new WindowInputDeviceGLFW;

	return instanceWindowDevice;
}

static void onClose(GLFWwindow* window)
{
	if (instanceWindowDevice != nullptr)
		instanceWindowDevice->close();
}

static void onResize(GLFWwindow* window, int width, int height)
{
	if (instanceWindowDevice != nullptr)
		instanceWindowDevice->resize(width, height);
}

void WindowInputDeviceGLFW::init(GLFWwindow* window)
{
	this->window = window;

	glfwSetWindowSizeCallback(window, onResize);

	//glfwSetWindowPos(window, positionX, positionY);
	//glfwSetWindowPosCallback(window, onWindowMove);

	glfwSetWindowCloseCallback(window, onClose);

}

void WindowInputDeviceGLFW::addHandler(WindowInputDeviceHandler* handler)
{
	handlers.push_back(handler);
}

void WindowInputDeviceGLFW::removeHandler(WindowInputDeviceHandler* handler)
{
	vector<WindowInputDeviceHandler*>::iterator item = find(handlers.begin(), handlers.end(), handler);

	if (item != handlers.end())
		handlers.erase(item);
}

void WindowInputDeviceGLFW::update(long long elapsedTime)
{
}

void WindowInputDeviceGLFW::close()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onClose();
}

void WindowInputDeviceGLFW::resize(int width, int height)
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onResize(width, height);
}

#endif