#pragma once

#ifdef QT

#include "apollo.h"
#include "PointerInputDevice.h"
#include <qwindow.h>
#include <qguiapplication.h>
#include <qevent.h>
#include <qscreen.h>

class API_INTERFACE PointerInputDeviceQT : public QObject, public PointerInputDevice
{
	Q_OBJECT

private:
	QWidget* window = nullptr;
	float previousPosition[2] = {0.0f, 0.0f};

public:
	void init(QWidget* window);
	void update(long long elapsedTime);

	void addHandler(PointerInputDeviceHandler* handler);
	void removeHandler(PointerInputDeviceHandler* handler);

	bool eventFilter(QObject *object, QEvent *event);
};

#endif