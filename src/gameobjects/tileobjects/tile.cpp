#include "tile.hpp"

#include "../../util/constants.hpp"
#include "../../states/gamestate.hpp"
#include "../../game.hpp"
#include "player.hpp"

#include <iostream>

/* constructor for main tiles (tileid >= 0) */
Tile::Tile(Game *game, int tileId, int tileX, int tileY, bool collideable, bool deadly, bool icy, bool bouncy) :
	CustomSprite(game, "tiles", tileX, tileY),
	tileId(tileId),
	collideable(collideable),
	deadly(deadly),
	icy(icy),
	bouncy(bouncy)
{
	/* get correct TILE_SIZE*TILE_SIZE tile */
	sf::IntRect rect;
	rect.left = TILE_SIZE * (tileId % 10);
	rect.top = TILE_SIZE * static_cast<int>(static_cast<int>(tileId) / 10.0f);
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;

	sprite.setTextureRect(rect);

	updateGlobalBounds();
}

/* alternative constructor for other / custom tiles (e.g. player floor collider; tileId < 0) */
Tile::Tile(Game *game, int tileId, std::string textureName) :
	CustomSprite(game, textureName, 0.0f, 0.0f),
	tileId(tileId),
	collideable(false),
	deadly(false),
	icy(false),
	bouncy(false)
{
	updateGlobalBounds();
}

void Tile::reset() {
}

bool Tile::isColliding(Tile &other)
{
	bool collision = false;
	if (other.getGlobalBounds().intersects(getGlobalBounds()))
	{
		onCollision(other);
		if (isCollideable())
		{
			collision = true;
		}
	}
	return collision;
}

void Tile::onCollision(Tile &other)
{
	if (other.getTileId() == TILE_PLAYER_COLLIDER_FLOOR)
	{
		game->getGameState()->getPlayer().setOnIce(icy);
		if (bouncy)
		{
			game->getGameState()->getPlayer().jump(PLAYER_SPRING_JUMPING_SPEED);
			//game->getResourceManager().getSound("block_bouncy_jump")->play();
		}
	}
	else
	{
		if (deadly && other.getTileId() == TILE_PLAYER)
		{
			game->getGameState()->reset();
		}
	}
}

int Tile::getTileId()
{
	return tileId;
}

bool Tile::isCollideable()
{
	return collideable;
}

bool Tile::isDeadly()
{
	return deadly;
}
