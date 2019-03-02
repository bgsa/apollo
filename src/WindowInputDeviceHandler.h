#pragma once

#include "apollo.h"

class WindowMoveEvent 
{
public:
	int previousPostion[2];
	int newPosition[2];

	WindowMoveEvent() {	}
	WindowMoveEvent(int previousPostion[2], int newPosition[2])
	{
		this->previousPostion[0] = previousPostion[0];
		this->previousPostion[1] = previousPostion[1];

		this->newPosition[0] = newPosition[0];
		this->newPosition[1] = newPosition[1];
	}
};

class WindowInputDeviceHandler
{
public:
	virtual void onHide() {};
	virtual void onShow() {};
	virtual void onMove(WindowMoveEvent& moveEvent) {};
	virtual void onClose() {};
	virtual void onResize(int width, int height) {};
	virtual void onMaximized() {};
	virtual void onFullScreen() {};
	virtual void onFocusIn() {};
	virtual void onFocusOut() {};
};

