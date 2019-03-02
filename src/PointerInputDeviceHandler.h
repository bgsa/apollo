#pragma once

#include "apollo.h"

enum MouseButton {
	NONE,
	LEFT,
	RIGHT,
	MIDDLE	
};

enum WheelDirection {
	UP,
	DOWN
};

struct MouseState {
	float position[2];
	bool leftButtonPressed;
	bool rightButtonPressed;
	bool middleButtonPressed;
};

class MouseEvent 
{
public:
	MouseButton button;	
	float previousPosition[2];
	float currentPosition[2];
	WheelDirection direction;
	float scrollOffset[2];
	MouseState state;

	void log() {
		Log::info("MOUSE POSITION (" + StringHelper::toString(currentPosition[0]) + " , " + StringHelper::toString(currentPosition[1]) + ")");
	}
};

class PointerInputDeviceHandler
{
private:
	MouseState(*getMouseStateFunction)();

public:
	void init(MouseState(*getMouseStateFunction)()) {
		this->getMouseStateFunction = getMouseStateFunction;
	}

	MouseState getMouseState() {
		return getMouseStateFunction();
	}

	virtual void onMouseMove(MouseEvent& e) {};
	
	virtual void onMouseDown(MouseEvent& e) {};
	virtual void onMouseUp(MouseEvent& e) {};

	virtual void onDoubleClick(MouseEvent& e) {};

	virtual void onScroll(MouseEvent& e) {}

	virtual void onMouseEnter(MouseEvent& e) {};
};
