#include "resourcesmanager.h"
#include "helper.h"

ResourcesManager& ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

ResourcesManager::ResourcesManager() {}

void ResourcesManager::loadResources() {
    loadFont("resources/font.ttf");
    loadPicture("resources/bg_picture.png");
}

void ResourcesManager::loadFont(std::string name) {
    TTF_Font *font = TTF_OpenFont(name.c_str(), 24);
    if (font == NULL) {
        Helper::logError("open font");
        return;
    }
    _fonts[name] = font;
}

void ResourcesManager::loadPicture(std::string name) {
    Picture pic;
    pic.load(name);
    _pictures[name] = pic;
}

const Picture& ResourcesManager::getPicture(const std::string &name) const {
    auto it = _pictures.find(name);
    return it->second;
}

TTF_Font* ResourcesManager::getFont(const std::string &name) const {
    auto it = _fonts.find(name);
    return it->second;
}
