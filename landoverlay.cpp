#include "landoverlay.h"
#include "resourcesmanager.h"
#include <iostream>

int LandOverlay::_countLandOverlay = 0;

LandOverlay::LandOverlay() {
	_masterTile = nullptr;
	_picture = nullptr;
	_animation = nullptr;
	_id = ++_countLandOverlay;
}

LandOverlay::~LandOverlay() {}

void LandOverlay::setMasterTile(Tile *masterTile) {
	if (_masterTile != nullptr) {
		_masterTile->setLandOverlay(nullptr);
	}
	_masterTile = masterTile;
	_masterTile->setLandOverlay(this);

}

void LandOverlay::setPicture(const TilePicture tilePicture) {
	_picture = ResourcesManager::getInstance().getPicture(tilePicture);
}

void LandOverlay::setAnimation(const TileAnimation tileAnimation) {
	_animation = ResourcesManager::getInstance().getAnimation(tileAnimation);
}

int LandOverlay::getI() const {
	return _masterTile->getI();
}

int LandOverlay::getJ() const {
	return _masterTile->getJ();
}

int LandOverlay::getX() const {
	return _masterTile->getX();
}

int LandOverlay::getY() const {
	return _masterTile->getY();
}

void LandOverlay::echo() const {
	std::cout << "Hi, there is " << _id << '\n';
}
