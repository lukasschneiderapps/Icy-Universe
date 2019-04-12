#pragma once

#include "../customsprite.hpp"

class GameState;
class Tile : public CustomSprite
{
public:
	Tile(Game *game, int tileId, int tileX, int tileY, bool collideable, bool deadly, bool icy, bool bouncy); /* main tiles */
	Tile(Game *game, int tileId, std::string textureName); /* other tiles */

	/* reset when player died (e.g. if position got changed during playtime) */
	virtual void reset();

	virtual bool isColliding(Tile &other);

	int getTileId();
	bool isCollideable();
	bool isDeadly();

protected:
	virtual void onCollision(Tile &other);

	/* parameters */
	int tileId;
	bool collideable;
	bool deadly;
	bool icy;
	bool bouncy;
};

