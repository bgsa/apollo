#ifdef QT

#pragma once

#include "apollo.h"
#include "DisplayDevice.h"
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>

class DisplayDeviceQT : public DisplayDevice
{

private:
	QWidget* window;

public:
	API_INTERFACE DisplayDeviceQT();

	API_INTERFACE void init(QWidget* window);
	API_INTERFACE void swapBuffer() override;
};

#endif