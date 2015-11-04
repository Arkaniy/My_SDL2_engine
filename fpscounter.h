#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "picture.h"

class FpsCounter {
public:
	static FpsCounter& getInstance();
	void draw() const;
    void calculateFps();
	int getFps() const;
private:
	FpsCounter();
private:
    int _currentFps;
    int _currentFrame;
	TextPicture _text;
};

#endif // FPSCOUNTER_H
