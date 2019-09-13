#include "WindowInputDeviceQT.h"

#ifdef QT

static WindowInputDeviceQT* instanceWindowDevice = nullptr;

WindowInputDeviceQT* WindowInputDeviceQT::getInstance()
{
	if (instanceWindowDevice == nullptr)
		instanceWindowDevice = new WindowInputDeviceQT;

	return instanceWindowDevice;
}

void WindowInputDeviceQT::init(QWidget* window)
{
	this->window = window;
	QGuiApplication::instance()->installEventFilter(this);
}

void WindowInputDeviceQT::addHandler(WindowInputDeviceHandler* handler)
{
	handlers.push_back(handler);
}

void WindowInputDeviceQT::removeHandler(WindowInputDeviceHandler* handler)
{
	std::vector<WindowInputDeviceHandler*>::iterator item = find(handlers.begin(), handlers.end(), handler);

	if (item != handlers.end())
		handlers.erase(item);
}

void WindowInputDeviceQT::update(long long elapsedTime)
{
}

void WindowInputDeviceQT::close()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onClose();
}

void WindowInputDeviceQT::move(int previousPosition[2], int newPosition[1])
{
	WindowMoveEvent moveEvent(previousPosition, newPosition);

	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onMove(moveEvent);
}

void WindowInputDeviceQT::show()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onShow();
}

void WindowInputDeviceQT::hide()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onHide();
}

void WindowInputDeviceQT::maximize()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onMaximized();
}

void WindowInputDeviceQT::fullscreen()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onFullScreen();
}

void WindowInputDeviceQT::focusIn()
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onFocusIn();
}

void WindowInputDeviceQT::focusOut() 
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onFocusOut();
}

void WindowInputDeviceQT::resize(int width, int height)
{
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onResize(width, height);
}

bool WindowInputDeviceQT::eventFilter(QObject* object, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::Close:
	{
		close();
		break;
	}
	case QEvent::Move:
	{
		QMoveEvent* moveEvent = static_cast<QMoveEvent*>(event);
		QPoint previousPosition = moveEvent->oldPos();
		QPoint newPosition = moveEvent->oldPos();

		int prevPos[2] = { previousPosition.x(), previousPosition.y() };
		int newPos[2] = { newPosition.x(), newPosition.y() };

		move(prevPos, newPos);

		break;
	}
	case QEvent::Resize:
	{
		QResizeEvent* resizeEvent = static_cast<QResizeEvent *>(event);
		QSize size = resizeEvent->size();

		resize(size.width(), size.height());

		break;
	}
	case QEvent::FocusIn:
	{
		focusIn();
		break;
	}
	case QEvent::FocusOut:
	{
		focusOut();
		break;
	}
	case QEvent::WindowStateChange:
	{
		QWindowStateChangeEvent* windowChangedEvent = static_cast<QWindowStateChangeEvent*>(event);
		Qt::WindowStates windowState = window->windowState();

		switch (windowState)
		{		
		case Qt::WindowState::WindowMaximized:
		{
			maximize();
			break;
		}
		case Qt::WindowState::WindowMinimized:
		{
			hide();
			break;
		}
		case Qt::WindowState::WindowFullScreen:
		{
			fullscreen();
			break;
		}
		case Qt::WindowState::WindowNoState:
		case Qt::WindowState::WindowActive:
		default:
			show();
			break;
		}

		break;
	}
	}

	return false;
}

#endif