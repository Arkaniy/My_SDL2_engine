#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <map>
#include "picture.h"
#include <SDL2/SDL_ttf.h>

class ResourcesManager {
public:
    static ResourcesManager& getInstance();
    void loadResources();
    void unload();
    void loadPicture(std::string name);
    void loadFont(std::string name);
    const Picture& getPicture(const std::string &name) const;
    TTF_Font* getFont(const std::string &name) const;
private:
    ResourcesManager();
private:
    std::map<std::string, Picture> _pictures;
    std::map<std::string, TTF_Font*> _fonts;
};

#endif // RESOURCESMANAGER_H
