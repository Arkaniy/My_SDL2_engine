#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <map>
#include "picture.h"
#include <SDL2/SDL_ttf.h>
#include "enums.h"

class ResourcesManager {
public:
    static ResourcesManager& getInstance();
    void loadResources();
    void unload();
	void loadPicture(std::string name, TilePicture tilePicture, int xOffset, int yOffset);
    void loadFont(std::string name);
	Picture* getPicture(const TilePicture tilePicture);
	Picture* getPicture(const std::string resource);
    TTF_Font* getFont(const std::string &name) const;
private:
    ResourcesManager();
private:
	std::map<TilePicture, Picture> _pictures;
    std::map<std::string, TTF_Font*> _fonts;
};

#endif // RESOURCESMANAGER_H
