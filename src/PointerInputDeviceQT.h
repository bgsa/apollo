#ifdef QT_ENABLED

#pragma once

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include "apollo.h"
#include "PointerInputDevice.h"
#include <qwindow.h>
#include <qguiapplication.h>
#include <qevent.h>
#include <qscreen.h>

class PointerInputDeviceQT : public QObject, public PointerInputDevice
{
	Q_OBJECT

private:
	QWidget* window = nullptr;
	float previousPosition[2] = {0.0f, 0.0f};

public:
	API_INTERFACE void init(QWidget* window);
	API_INTERFACE void update(long long elapsedTime);

	API_INTERFACE void addHandler(PointerInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(PointerInputDeviceHandler* handler);

	API_INTERFACE bool eventFilter(QObject *object, QEvent *event);
};

#endif