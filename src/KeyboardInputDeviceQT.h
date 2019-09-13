#pragma once

#ifdef QT

#include <algorithm>
#include "apollo.h"
#include "KeyboardInputDevice.h"
#include <qguiapplication.h>
#include <qevent.h>
#include <qobject.h>

class API_INTERFACE KeyboardInputDeviceQT : public QObject, public KeyboardInputDevice
{
	Q_OBJECT

private:
	QWidget* window = nullptr;
	std::vector<KeyboardInputDeviceHandler*> handlersKeyboard;

public:
	void init(QWidget* window);
	void update(long long elapsedTime);

	bool isKeyPressed(int virtualKey);

	void addHandler(KeyboardInputDeviceHandler* handler);
	void removeHandler(KeyboardInputDeviceHandler* handler);

	bool eventFilter(QObject *object, QEvent *event);

};

#endif