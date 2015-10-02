#ifndef LANDOVERLAY_H
#define LANDOVERLAY_H

#include "tilemap.h"
#include "widget.h"

class LandOverlay : public Widget {
public:
	LandOverlay();
	virtual ~LandOverlay();
	void setMasterTile(Tile *masterTile);
	void setPicture(const TilePicture tilePicture);
	int getI() const;
	int getJ() const;
	int getX() const;
	int getY() const;
protected:
	Tile *_masterTile;
	Picture *_picture;
};

#endif // LANDOVERLAY_H
