#pragma once

#include "apollo.h"
#include "InputDeviceHandler.h"

class KeyboardInputDeviceHandler : public InputDeviceHandler
{
private:
	bool(*isKeyPressedFunction)(int);

public:	
	API_INTERFACE void init( bool(*isKeyPressedFunction)(int)   ) {
		this->isKeyPressedFunction = isKeyPressedFunction;
	}

	API_INTERFACE bool isKeyPressed(int keyCode)
	{
		return isKeyPressedFunction(keyCode);
	}

	API_INTERFACE virtual void onKeyDown(int keyCode) {};
	API_INTERFACE virtual void onKeyUp(int keyCode) {};
};

