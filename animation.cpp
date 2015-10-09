#include "animation.h"

Animation::Animation() {}

void Animation::setNFrame(int nFrames) {
	_nFrames = nFrames;
}

void Animation::addFrame(Picture picture, int xOffset, int yOffset) {
	picture.setXOffset(xOffset);
	picture.setYOffset(yOffset);
	_frames.push_back(picture);
}

void Animation::draw(int x, int y) const
{
	static int currentFrame = 0;
	_frames[currentFrame++].draw(x, y);
	if (currentFrame == _nFrames) {
		currentFrame = 0;
	}
}
