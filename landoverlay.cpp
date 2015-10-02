#include "landoverlay.h"
#include "resourcesmanager.h"

LandOverlay::LandOverlay() {
	_masterTile = nullptr;
	_picture = nullptr;
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
