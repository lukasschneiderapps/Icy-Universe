#pragma once

#include "tile.hpp"

class Sting : public Tile
{
public:
	Sting(Game *game, int tileId, float x, float y);
	bool isColliding(Tile &other) override;
};