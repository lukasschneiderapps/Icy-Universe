#include "sting.hpp"

#include "../../util/constants.hpp"
#include "../../util/point.hpp"
#include "../../util/math.hpp"
#include "../../game.hpp"

#include <iostream>

/* tileid = up, down, left, right and everything in small */
Sting::Sting(Game *game, int tileId, float x, float y) :
	Tile(game, tileId, x, y, false, true, false, false)
{
	/* don't exactly hit edges */
	switch (tileId)
	{
		/* x */
	case TILE_STING_ICE_SMALL_DOWN: /* intentional fall trough */
	case TILE_STING_ICE_DOWN: /* intentional fall trough */
	case TILE_STING_ICE_SMALL_UP: /* intentional fall trough */
	case TILE_STING_ICE_UP:
		sprite.setScale(0.9f, 1.0f);
		sprite.move(TILE_SIZE * 0.1f / 2.0f, 0.0f);
		updateGlobalBounds();
		break;
		/* y */
	case TILE_STING_ICE_SMALL_RIGHT: /* intentional fall trough */
	case TILE_STING_ICE_RIGHT: /* intentional fall trough */
	case TILE_STING_ICE_SMALL_LEFT: /* intentional fall trough */
	case TILE_STING_ICE_LEFT:
		sprite.setScale(1.0f, 0.9f);
		sprite.move(0.0f, TILE_SIZE * 0.1f / 2.0f);
		updateGlobalBounds();
		break;
	}
}


bool Sting::isColliding(Tile &other)
{
	bool collision = false;

	sf::FloatRect otherRect = other.getGlobalBounds();

	/* check if a point of globalBounds (as triangle) is inside otherRect */
	switch (tileId)
	{
		/* normal size */
	case TILE_STING_ICE_UP:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top + globalBounds.height),
			Point(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height),
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_DOWN:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top),
			Point(globalBounds.left + globalBounds.width, globalBounds.top),
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_LEFT:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top + globalBounds.height / 2.0f),
			Point(globalBounds.left + globalBounds.width, globalBounds.top),
			Point(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_RIGHT:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top),
			Point(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height / 2.0f),
			Point(globalBounds.left, globalBounds.top + globalBounds.height)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
		/* small size */
	case TILE_STING_ICE_SMALL_UP:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top + globalBounds.height),
			Point(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height),
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height / 2.0f)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_SMALL_DOWN:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top),
			Point(globalBounds.left + globalBounds.width, globalBounds.top),
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height / 2.0f)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_SMALL_LEFT:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height / 2.0f),
			Point(globalBounds.left + globalBounds.width, globalBounds.top),
			Point(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	case TILE_STING_ICE_SMALL_RIGHT:
		if (rectIntersectsTriangle(otherRect,
			Point(globalBounds.left, globalBounds.top),
			Point(globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height / 2.0f),
			Point(globalBounds.left, globalBounds.top + globalBounds.height)))
		{
			onCollision(other);
			if (isCollideable())
			{
				collision = true;
			}
		}
		break;
	}
	return collision;
}