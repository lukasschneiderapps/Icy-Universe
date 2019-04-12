#pragma once

#include "tile.hpp"

class Platform : public Tile
{
public:
	Platform(Game *game, int tileId, int tileX, int tileY);

	void onCollision(Tile &other) override;
	void update(float dt) override;
	void reset() override;

private:
	sf::Vector2f initialPosition;
	bool moveToNegative = false;
};