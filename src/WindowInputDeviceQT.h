#ifdef QT

#pragma once

#include "apollo.h"
#include "WindowInputDevice.h"
#include <qwindow.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qevent.h>

class API_INTERFACE WindowInputDeviceQT : public QObject, public WindowInputDevice
{
	Q_OBJECT

private:
	QWidget* window;
	vector<WindowInputDeviceHandler*> handlers;

public:

	static WindowInputDeviceQT* getInstance();

	void init(QWidget* window);
	void update(long long elapsedTime);

	void show();
	void hide();
	void move(int previousPosition[2], int newPosition[2]);
	void resize(int width, int height);
	void close();
	void maximize();
	void fullscreen();
	void focusIn();
	void focusOut();

	void addHandler(WindowInputDeviceHandler* handler);
	void removeHandler(WindowInputDeviceHandler* handler);

	bool eventFilter(QObject *object, QEvent *event);

};

#endif