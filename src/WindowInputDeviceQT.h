#ifdef QT_ENABLED

#pragma once

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include "apollo.h"
#include "WindowInputDevice.h"
#include <qwindow.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qevent.h>

class WindowInputDeviceQT : public QObject, public WindowInputDevice
{
	Q_OBJECT

private:
	QWidget* window;
	std::vector<WindowInputDeviceHandler*> handlers;

public:

	API_INTERFACE static WindowInputDeviceQT* getInstance();

	API_INTERFACE void init(QWidget* window);
	API_INTERFACE void update(long long elapsedTime);

	API_INTERFACE void show();
	API_INTERFACE void hide();
	API_INTERFACE void move(int previousPosition[2], int newPosition[2]);
	API_INTERFACE void resize(int width, int height);
	API_INTERFACE void close();
	API_INTERFACE void maximize();
	API_INTERFACE void fullscreen();
	API_INTERFACE void focusIn();
	API_INTERFACE void focusOut();

	API_INTERFACE void addHandler(WindowInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(WindowInputDeviceHandler* handler);

	API_INTERFACE bool eventFilter(QObject *object, QEvent *event);

};

#endif