#include "resourcesmanager.h"
#include "helper.h"

ResourcesManager& ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

ResourcesManager::ResourcesManager() {}

void ResourcesManager::unload() {
    for (const std::pair<std::string, TTF_Font*> pair : _fonts) {
        TTF_CloseFont(pair.second);
    }
    for (std::pair<std::string, Picture> pair : _pictures) {
        pair.second.free();
    }
}

void ResourcesManager::loadResources() {
    loadFont("resources/font.ttf");
	loadFont("resources/font1.ttf");
    loadPicture("resources/bg_picture.png");
	loadPicture("resources/bg_picture2.png");
    loadPicture("resources/bg_wait.png");
	loadPicture("resources/button.png");
	loadPicture("resources/button_pressed.png");
}

void ResourcesManager::loadFont(std::string name) {
	TTF_Font *font = TTF_OpenFont(name.c_str(), 20);
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

Picture *ResourcesManager::getPicture(const std::string &name) {
    auto it = _pictures.find(name);
	return &it->second;
}

TTF_Font* ResourcesManager::getFont(const std::string &name) const {
    auto it = _fonts.find(name);
    return it->second;
}
