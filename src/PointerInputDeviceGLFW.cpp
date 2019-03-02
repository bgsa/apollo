#include "PointerInputDeviceGLFW.h"

#ifdef GLFW

GLFWwindow* mouseWindow;
std::vector<PointerInputDeviceHandler*> handlersPointer;
Vec2f previousPointerPositionDevice = { 0.0f, 0.0f };

void onClick(GLFWwindow* window, int button, int action, int mods)
{
	double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	int screenHeight = RendererSettings::getInstance()->getHeight();

	MouseEvent e;
	e.currentPosition = Vec2f{ float(posx), screenHeight - float(posy) };

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		e.button = MouseButton::LEFT;
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		e.button = MouseButton::RIGHT;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		e.button = MouseButton::MIDDLE;
		break;
	}

	if (action == GLFW_PRESS)
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseDown(e);
	else
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseUp(e);
}

void onMove(GLFWwindow* window, double posx, double posy)
{
	int screenHeight = RendererSettings::getInstance()->getHeight();

	MouseEvent e;
	e.previousPosition = previousPointerPositionDevice;
	e.currentPosition = Vec2f{ float(posx), screenHeight - float(posy) };

	int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);
	
	e.state = {
		e.currentPosition,
		leftButtonState == GLFW_PRESS, 
		rightButtonState == GLFW_PRESS,
		middleButtonState == GLFW_PRESS
	};

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onMouseMove(e);

	previousPointerPositionDevice = e.currentPosition;
}

MouseState getMouseState()
{
	double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	int screenHeight = RendererSettings::getInstance()->getHeight();
	Vec2f position{ float(posx), screenHeight - float(posy) };

	int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);

	bool leftButtonPressed = leftButtonState == GLFW_PRESS;
	bool rightButtonPressed = rightButtonState == GLFW_PRESS;
	bool middleButtonPressed = middleButtonState == GLFW_PRESS;

	return MouseState{ position, leftButtonPressed, rightButtonPressed, middleButtonPressed };
}

void onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseState state = getMouseState();
	WheelDirection direction = WheelDirection::UP;

	if (xoffset == 0.0)
		if (yoffset > 0)
			direction = WheelDirection::UP;
		else
			direction = WheelDirection::DOWN;

	MouseEvent e;
	e.currentPosition = state.position;
	e.direction = direction;
	e.scrollOffset = Vec2f(float(xoffset), float(yoffset));

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onScroll(e);
}

void PointerInputDeviceGLFW::init(GLFWwindow* window)
{
	mouseWindow = window;

	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1); // for pooling do not lose event

	glfwSetMouseButtonCallback(window, onClick);
	glfwSetCursorPosCallback(window, onMove);
	glfwSetScrollCallback(window, onScroll);
}

void PointerInputDeviceGLFW::addHandler(PointerInputDeviceHandler* handler) {
	handler->init(&getMouseState);
	handlersPointer.push_back(handler);
}

void PointerInputDeviceGLFW::removeHandler(PointerInputDeviceHandler* handler)
{
	vector<PointerInputDeviceHandler*>::iterator item = std::find(handlersPointer.begin(), handlersPointer.end(), handler);

	if (item != handlersPointer.end())
		handlersPointer.erase(item);
}

void PointerInputDeviceGLFW::update(long long elapsedTime)
{
}

#endif