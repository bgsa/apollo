#pragma once

#include "apollo.h"
#include "InputDevice.h"
#include "WindowInputDeviceHandler.h"

class WindowInputDevice : public InputDevice
{
public:

	API_INTERFACE virtual void addHandler(WindowInputDeviceHandler* handler) = 0;
	API_INTERFACE virtual void removeHandler(WindowInputDeviceHandler* handler) = 0;

};