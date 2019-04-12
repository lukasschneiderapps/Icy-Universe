#include "platform.hpp"

#include "../../util/constants.hpp"

#include "../../states/gamestate.hpp"
#include "../../game.hpp"

/* vertical / horizontal */
Platform::Platform(Game *game, int tileId, int tileX, int tileY) :
	Tile::Tile(game, tileId, tileX, tileY, true, false, false, false)
{
	initialPosition = getPosition();
	setScale(1.0f, 0.5f);
	updateGlobalBounds();
}

void Platform::onCollision(Tile &other)
{
	/* player can stand on platform without moving */
	if (other.getTileId() == TILE_PLAYER_COLLIDER_FLOOR)
	{
		game->getGameState()->getPlayer().setOnPlatform(true);
		if (tileId == TILE_PLATFORM_STONE_VERTICAL)
		{
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			//movingVector.x = 0;
			movingVector.y = (moveToNegative ? -1 : 1) * PLATFORM_MOVING_SPEED;
			game->getGameState()->getPlayer().setMovingVector(movingVector);
		}
		else if (tileId == TILE_PLATFORM_STONE_HORIZONTAL) {
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			movingVector.x = (moveToNegative ? -1 : 1) * PLATFORM_MOVING_SPEED;
			//movingVector.y = 0;
			game->getGameState()->getPlayer().setMovingVector(movingVector);
		}
	}

}

void Platform::update(float dt)
{
	/* movement */
	for (int i = 0; i < PLATFORM_MOVEMENT_REPEATS; i++)
	{
		/* y movement */
		if (tileId == TILE_PLATFORM_STONE_VERTICAL)
		{
			translate(0, (moveToNegative ? -1 : 1) * PLATFORM_MOVING_SPEED * dt);
			if (game->getGameState()->isColliding(*this))
			{
				translate(0, (moveToNegative ? -1 : 1) * -PLATFORM_MOVING_SPEED * dt);
				moveToNegative = !moveToNegative;
			}
		}
		/* x movement */
		else if (tileId == TILE_PLATFORM_STONE_HORIZONTAL) {
			translate((moveToNegative ? -1 : 1) * PLATFORM_MOVING_SPEED * dt, 0);
			if (game->getGameState()->isColliding(*this))
			{
				translate((moveToNegative ? -1 : 1) * -PLATFORM_MOVING_SPEED * dt, 0);
				moveToNegative = !moveToNegative;
			}
		}
	}
}

void Platform::reset()
{
	setPosition(initialPosition);
	moveToNegative = false;
}

