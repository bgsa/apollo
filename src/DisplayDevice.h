#pragma once

class DisplayDevice
{
private:
	int width;
	int height;

protected:
	void setWidth(int width);
	void setHeight(int height);

public:
	virtual int getWidth() {
		return width;
	}

	virtual int getHeight() {
		return height;
	}

	virtual void swapBuffer() {};

	virtual ~DisplayDevice() {}
};
