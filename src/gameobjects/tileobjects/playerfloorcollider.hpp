#pragma once

#include "tile.hpp"

class PlayerFloorCollider : public Tile
{
public:
	PlayerFloorCollider(Game *game);

	bool isColliding(Tile &other) override;
};