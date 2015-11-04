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
		auto res = _pictures.find(pair.first);
		while(res != _pictures.end()) {
			res->second.setExist(false);
			res = std::find_if(++res, _pictures.end(), [pair](std::pair<TilePicture, Picture> pair2){
				return pair.second.getResource() == pair2.second.getResource();
			});
		}
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
	loadPicture("resources/png/walkcycle/BODY_skeleton.png", TP_Man, 0, 128);
	loadPicture("resources/png/walkcycle/BODY_skeleton.png", TP_Man1, 0, 64);
	loadAnimation("resources/png/walkcycle/BODY_skeleton.png", TA_ManLeft, 9, 64);
	loadAnimation("resources/png/walkcycle/BODY_skeleton.png", TA_ManRight, 9, 192);
//	loadPicture("resources/png/walkcycle/BODY_male.png", TP_Man, 0, 128);
//	loadPicture("resources/png/walkcycle/BODY_male.png", TP_Man1, 0, 64);
//	loadAnimation("resources/png/walkcycle/BODY_male.png", TA_ManLeft, 9, 64);
//	loadAnimation("resources/png/walkcycle/BODY_male.png", TA_ManRight, 9, 192);
}

void ResourcesManager::loadAnimation(std::string name, TileAnimation tileAnimation, int nFrames, int yOffset) {
	Animation animation;
	animation.setNFrame(nFrames);
	Picture pic = *getPicture(name);
	for (int i = 0; i < nFrames; ++i) {
		animation.addFrame(pic, i * 64, yOffset);
	}
	_animations[tileAnimation] = animation;
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

Animation *ResourcesManager::getAnimation(const TileAnimation tileAnimation) {
	auto it = _animations.find(tileAnimation);
	if (it == _animations.end()) {
		return nullptr;
	}
	return &it->second;
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
