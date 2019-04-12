#pragma once

#include "tile.hpp"

class Block : public Tile
{
public:
	Block(Game *game, int tileId, float x, float y);
	bool isColliding(Tile &other) override;
};