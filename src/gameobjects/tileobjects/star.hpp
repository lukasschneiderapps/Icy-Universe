#pragma once

#include "tile.hpp"

class Star : public Tile
{
public:
	Star(Game *game, float x, float y);
	void draw() override;
	void reset() override;
	void onCollision(Tile &other) override;
	bool isCollected();
	void setCollected(bool collected);

private:
	bool collected;
};