#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <map>
#include "animation.h"
#include "enums.h"

class ResourcesManager {
public:
    static ResourcesManager& getInstance();
    void loadResources();
    void unload();
	void loadAnimation(std::string name, TileAnimation tileAnimation, int nFrames, int yOffset);
	void loadPicture(std::string name, TilePicture tilePicture, int xOffset, int yOffset);
	void loadFont(std::string name, FontCollection fontCollection);
	Animation* getAnimation(const TileAnimation tileAnimation);
	Picture* getPicture(const TilePicture tilePicture);
	Picture* getPicture(const std::string resource);
	TTF_Font* getFont(const FontCollection fontCollection);
private:
    ResourcesManager();
private:
	std::map<TileAnimation, Animation>	_animations;
	std::map<TilePicture, Picture>		_pictures;
	std::map<FontCollection, TTF_Font*>	_fonts;
};

#endif // RESOURCESMANAGER_H
