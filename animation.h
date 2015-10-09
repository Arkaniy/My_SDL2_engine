#ifndef ANIMATION_H
#define ANIMATION_H

#include "enums.h"
#include "picture.h"
#include <vector>

class Animation {
public:
	Animation();
	void setNFrame(int nFrames);
	void addFrame(Picture picture, int xOffset, int yOffset);
	void draw(int x, int y) const;
private:
	int _nFrames;
	std::vector<Picture> _frames;
};

#endif // ANIMATION_H
