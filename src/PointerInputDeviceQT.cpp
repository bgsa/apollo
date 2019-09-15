#ifdef QT_ENABLED

#include "PointerInputDeviceQT.h"

std::vector<PointerInputDeviceHandler*> handlersPointer;

float* getMousePosition()
{
	//int screenHeight = RendererSettings::getInstance()->getHeight();
	int screenHeight = QGuiApplication::primaryScreen()->geometry().height();

	QPoint globalCursorPosition = QCursor::pos();
	QRect mouseScreenGeometry = QGuiApplication::primaryScreen()->geometry();
	QPoint localCursorPosition = globalCursorPosition - mouseScreenGeometry.topLeft();

	float* position = new float[2];
	position[0] = float(localCursorPosition.x());
	position[1] = screenHeight - float(localCursorPosition.y());

	return position;
}

MouseState getMouseState()
{
	Qt::MouseButtons mouseButtonState = QGuiApplication::mouseButtons();

	bool leftButtonPressed = mouseButtonState.testFlag(Qt::MouseButton::LeftButton);
	bool rightButtonPressed = mouseButtonState.testFlag(Qt::MouseButton::RightButton);
	bool middleButtonPressed = mouseButtonState.testFlag(Qt::MouseButton::MiddleButton);
	
	float* currentPosition = getMousePosition();

	return MouseState{ {currentPosition[0], currentPosition[1]}, leftButtonPressed, rightButtonPressed, middleButtonPressed };
}

MouseButton getButtonPressed(QMouseEvent* mouseEvent)
{
	switch (mouseEvent->button())
	{
	case Qt::MouseButton::LeftButton:
		return MouseButton::LEFT;
		break;

	case Qt::MouseButton::RightButton:
		return MouseButton::RIGHT;
		break;

	case Qt::MouseButton::MiddleButton:
		return MouseButton::MIDDLE;
		break;
	}

	return MouseButton::NONE;
}

void PointerInputDeviceQT::init(QWidget* window)
{
	this->window = window;
	QGuiApplication::instance()->installEventFilter(this);
}

void PointerInputDeviceQT::addHandler(PointerInputDeviceHandler* handler) 
{
	handler->init(&getMouseState);
	handlersPointer.push_back(handler);
}

void PointerInputDeviceQT::removeHandler(PointerInputDeviceHandler* handler)
{
	std::vector<PointerInputDeviceHandler*>::iterator item = std::find(handlersPointer.begin(), handlersPointer.end(), handler);

	if (item != handlersPointer.end())
		handlersPointer.erase(item);
}

void PointerInputDeviceQT::update(long long elapsedTime)
{
}

bool PointerInputDeviceQT::eventFilter(QObject* object, QEvent *event)
{
	QMouseEvent  *mouseEvent = nullptr;
	MouseEvent e;

	//cout << event->type() << endl;

	switch (event->type())
	{
	case QEvent::MouseMove:
	{
		mouseEvent = static_cast<QMouseEvent *>(event);
		Qt::MouseButtons mouseButtonState = QGuiApplication::mouseButtons();

		e.previousPosition[0] = previousPosition[0];
		e.previousPosition[1] = previousPosition[1];

		e.currentPosition[0] = float(mouseEvent->pos().x());
		e.currentPosition[1] = float(mouseEvent->pos().y());

		e.state = {
			{e.currentPosition[0], e.currentPosition[1]},
			mouseButtonState.testFlag(Qt::MouseButton::LeftButton),
			mouseButtonState.testFlag(Qt::MouseButton::RightButton),
			mouseButtonState.testFlag(Qt::MouseButton::MiddleButton)
		};

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseMove(e);

		previousPosition[0] = e.currentPosition[0];
		previousPosition[1] = e.currentPosition[1];

		break;
	}

	case QEvent::MouseButtonPress:
	{
		mouseEvent = static_cast<QMouseEvent *>(event);

		e.previousPosition[0] = previousPosition[0];
		e.previousPosition[1] = previousPosition[1];

		e.currentPosition[0] = float(mouseEvent->pos().x());
		e.currentPosition[1] = float(mouseEvent->pos().y());

		e.button = getButtonPressed(mouseEvent);

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseDown(e);

		previousPosition[0] = e.currentPosition[0];
		previousPosition[1] = e.currentPosition[1];

		break;
	}

	case QEvent::MouseButtonRelease:
	{
		mouseEvent = static_cast<QMouseEvent *>(event);

		MouseEvent e;

		e.previousPosition[0] = previousPosition[0];
		e.previousPosition[1] = previousPosition[1];

		e.currentPosition[0] = float(mouseEvent->pos().x());
		e.currentPosition[1] = float(mouseEvent->pos().y());

		e.button = getButtonPressed(mouseEvent);

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseUp(e);

		previousPosition[0] = e.currentPosition[0];
		previousPosition[1] = e.currentPosition[1];

		break;
	}

	case QEvent::MouseButtonDblClick:
	{
		mouseEvent = static_cast<QMouseEvent *>(event);

		e.previousPosition[0] = previousPosition[0];
		e.previousPosition[1] = previousPosition[1];

		e.currentPosition[0] = float(mouseEvent->pos().x());
		e.currentPosition[1] = float(mouseEvent->pos().y());

		e.button = getButtonPressed(mouseEvent);

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onDoubleClick(e);

		previousPosition[0] = e.currentPosition[0];
		previousPosition[1] = e.currentPosition[1];

		break;
	}

	case QEvent::Wheel:
	{
		QWheelEvent* wheelEvent = static_cast<QWheelEvent *>(event);
		QPoint delta = wheelEvent->angleDelta();

		e.state = getMouseState();
		e.direction = wheelEvent->delta() > 0 ? WheelDirection::UP : WheelDirection::DOWN;

		e.scrollOffset[0] = float(delta.x());
		e.scrollOffset[1] = float(delta.y());

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onScroll(e);
		
		break;
	}

	case QEvent::Enter:
	{
		mouseEvent = static_cast<QMouseEvent *>(event);

		MouseEvent e;

		e.previousPosition[0] = previousPosition[0];
		e.previousPosition[1] = previousPosition[1];

		e.currentPosition[0] = float(mouseEvent->pos().x());
		e.currentPosition[1] = float(mouseEvent->pos().y());

		e.button = getButtonPressed(mouseEvent);

		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseEnter(e);

		previousPosition[0] = e.currentPosition[0];
		previousPosition[1] = e.currentPosition[1];

		break;
	}

	}

	return false;
}

#endif