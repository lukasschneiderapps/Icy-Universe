#include "block.hpp"

#include "../../util/constants.hpp"
#include "../../states/gamestate.hpp"
#include "../../game.hpp"

/* tileid: ice/stone normal or vertical / horizontal slim stone block, spring block, fire block */
Block::Block(Game *game, int tileId, float x, float y) :
	Tile(game, tileId, x, y, true,
		/* deadly */
		tileId == TILE_BLOCK_FIRE,
		/* icy */
		tileId == TILE_BLOCK_ICE ||
		tileId == TILE_BLOCK_ICE_SMALL_VERTICAL ||
		tileId == TILE_BLOCK_ICE_SMALL_HORIZONTAL,
		/* bouncy */
		tileId == TILE_BLOCK_BOUNCY) {}

bool Block::isColliding(Tile &other)
{
	switch (tileId)
	{
	case TILE_BLOCK_FIRE: /* intentional fall trough */
	case TILE_BLOCK_BOUNCY: /* intentional fall trough */
	case TILE_BLOCK_ICE: /* intentional fall trough */
	case TILE_BLOCK_STONE:
		return Tile::isColliding(other);
	case TILE_BLOCK_ICE_SMALL_VERTICAL: /* intentional fall trough */
	case TILE_BLOCK_STONE_SMALL_VERTICAL:
	{
		bool collision = false;
		sf::FloatRect ownBounds = globalBounds;
		ownBounds.left += ownBounds.width / 4.0f;
		ownBounds.width /= 2.0f;
		if (other.getSprite().getGlobalBounds().intersects(ownBounds))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		return collision;
	}
	case TILE_BLOCK_ICE_SMALL_HORIZONTAL: /* intentional fall trough */
	case TILE_BLOCK_STONE_SMALL_HORIZONTAL:
	{
		bool collision = false;
		sf::FloatRect ownBounds = globalBounds;
		ownBounds.top += ownBounds.height / 4.0f;
		ownBounds.height /= 2.0f;
		if (other.getSprite().getGlobalBounds().intersects(ownBounds))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		return collision;
	}
	default:
		return true;
	}
}