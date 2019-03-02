#pragma once

#include "apollo.h"
#include "InputDevice.h"
#include "PointerInputDeviceHandler.h"

class PointerInputDevice : public InputDevice
{
public:

	API_INTERFACE virtual void addHandler(PointerInputDeviceHandler* handler) = 0;
	API_INTERFACE virtual void removeHandler(PointerInputDeviceHandler* handler) = 0;

};