#pragma once

#include "InputDevice.h"
#include "KeyboardInputDeviceHandler.h"

class KeyboardInputDevice : public InputDevice
{
public:

	API_INTERFACE virtual void addHandler(KeyboardInputDeviceHandler* handler) = 0;
	API_INTERFACE virtual void removeHandler(KeyboardInputDeviceHandler* handler) = 0;

};