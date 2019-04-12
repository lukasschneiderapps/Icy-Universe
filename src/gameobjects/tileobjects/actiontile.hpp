#pragma once

#include "tile.hpp"

class ActionTile : public Tile
{
public:
	ActionTile(Game *game, int tileId, float x, float y);
	void onCollision(Tile &other) override;
};