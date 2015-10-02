#include "resourcesmanager.h"
#include "helper.h"
#include <algorithm>

ResourcesManager& ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

ResourcesManager::ResourcesManager() {}

void ResourcesManager::unload() {
    for (const std::pair<std::string, TTF_Font*> pair : _fonts) {
        TTF_CloseFont(pair.second);
    }
	for (std::pair<TilePicture, Picture> pair : _pictures) {
        pair.second.free();
    }
}

void ResourcesManager::loadResources() {
    loadFont("resources/font.ttf");
	loadFont("resources/font1.ttf");
	loadPicture("resources/bg_picture.png", TP_BackgroundMenu, 0, 0);
	loadPicture("resources/bg_wait.png", TP_BackgroundWait, 0, 0);
	loadPicture("resources/button.png", TP_Button, 0, 0);
	loadPicture("resources/button_pressed.png", TP_ButtonPressed, 0, 0);
	loadPicture("resources/tilemap.png", TP_Tile, 256, 128);
	loadPicture("resources/tilemap.png", TP_Wall, 448,  64);
	loadPicture("resources/png/walkcycle/BODY_male.png", TP_Man, 0, 128);
	loadPicture("resources/png/walkcycle/BODY_male.png", TP_Man1, 0, 64);
}

void ResourcesManager::loadFont(std::string name) {
	TTF_Font *font = TTF_OpenFont(name.c_str(), 20);
    if (font == NULL) {
        Helper::logError("open font");
        return;
    }
    _fonts[name] = font;
}

void ResourcesManager::loadPicture(std::string name, TilePicture tilePicture, int xOffset, int yOffset) {
	Picture pic;
	if (getPicture(name) == nullptr) {
		pic.load(name);
	} else {
		pic = *getPicture(name);
	}
	pic.setXOffset(xOffset);
	pic.setYOffset(yOffset);
	_pictures[tilePicture] = pic;
}

Picture *ResourcesManager::getPicture(const TilePicture tilePicture) {
	auto it = _pictures.find(tilePicture);
	if (it == _pictures.end()) {
		return nullptr;
	}
	return &it->second;
}

Picture *ResourcesManager::getPicture(const std::string resource) {
	auto it = std::find_if(_pictures.begin(), _pictures.end(), [&resource](std::pair<const TilePicture&, Picture> pair) {
		return pair.second.getResource() == resource;
	});
	if (it == _pictures.end()) {
		return nullptr;
	}
	return &it->second;
}

TTF_Font* ResourcesManager::getFont(const std::string &name) const {
    auto it = _fonts.find(name);
    return it->second;
}
