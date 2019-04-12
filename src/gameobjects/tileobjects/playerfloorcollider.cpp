#include "playerfloorcollider.hpp"

#include "../../util/constants.hpp"
#include "../../game.hpp"
#include "../../states/gamestate.hpp"

PlayerFloorCollider::PlayerFloorCollider(Game *game) :
	Tile(game, TILE_PLAYER_COLLIDER_FLOOR, "player_collider_floor") {}


bool PlayerFloorCollider::isColliding(Tile &other)
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

	/* no platform collision */
	if (other.getTileId() == TILE_PLATFORM_STONE_VERTICAL || other.getTileId() == TILE_PLATFORM_STONE_HORIZONTAL)
	{
		collision = false;
	}

	return collision;
}