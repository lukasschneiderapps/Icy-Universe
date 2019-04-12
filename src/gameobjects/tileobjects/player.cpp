#include "player.hpp"

#include "playerfloorcollider.hpp"
#include "../../util/constants.hpp"
#include "../../states/gamestate.hpp"
#include "../../game.hpp"
#include "tile.hpp"

Player::Player(Game *game, float x, float y) :
	Tile(game, TILE_PLAYER, x, y, true, false, false, false),
	playerFloorCollider(game)
{
	/* shrink player */
	setScale(0.8f);
	playerFloorCollider.setScale(0.79f, 0.8f);
}

void Player::update(float dt)
{
	/* check if grounded */
	playerFloorCollider.setPosition(getLeft() + (getWidth() - playerFloorCollider.getWidth()) / 2.0f, getTop() + getHeight() - playerFloorCollider.getHeight() / 2);
	grounded = game->getGameState()->isColliding(playerFloorCollider);

	/* movement */
	for (int i = 0; i < PLAYER_MOVEMENT_REPEATS; i++)
	{
		/* x movement */
		bool noXMovementKeyPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			noXMovementKeyPressed = false;
			if (movingVector.x + PLAYER_MOVEMENT_SPEED < PLAYER_MAX_MOVEMENT_SPEED)
			{
				movingVector.x += PLAYER_MOVEMENT_SPEED;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			noXMovementKeyPressed = false;
			if (movingVector.x - PLAYER_MOVEMENT_SPEED > -PLAYER_MAX_MOVEMENT_SPEED)
			{
				movingVector.x -= PLAYER_MOVEMENT_SPEED;
			}
		}

		if ((noXMovementKeyPressed || movingVector.x > PLAYER_MAX_MOVEMENT_SPEED || movingVector.x < -PLAYER_MAX_MOVEMENT_SPEED) && !onPlatform)
		{
			/* slow down x speed if no key pressed or speed more than player max movement speed (its less slowdown if on ice) */
			if (movingVector.x > 0)
			{
				movingVector.x -= PLAYER_MOVEMENT_SUBSTRACTION * (onIce ? 0.1f : 1.2f) * dt;
				if (movingVector.x < 0)
					movingVector.x = 0;
			}
			else if (movingVector.x < 0)
			{
				movingVector.x += PLAYER_MOVEMENT_SUBSTRACTION * (onIce ? 0.1f : 1.2f) * dt;
				if (movingVector.x > 0)
					movingVector.x = 0;
			}
		}

		/* limit max x speed */
		/*if (movingVector.x > PLAYER_MAX_MOVEMENT_SPEED)
			movingVector.x = PLAYER_MAX_MOVEMENT_SPEED;
		else if (movingVector.x < -PLAYER_MAX_MOVEMENT_SPEED)
			movingVector.x = -PLAYER_MAX_MOVEMENT_SPEED;*/

		/* move with collision check */
		translate(movingVector.x * dt, 0);
		if (game->getGameState()->isColliding(*this))
		{
			translate(-movingVector.x * dt, 0);
			movingVector.x = 0;
		}
		else
		{
			/* check if out of screen on x -> enter on the opposite site */
			if (movingVector.x > 0 && getLeft() > WINDOW_WIDTH - TILE_SIZE / 2.0f)
			{
				setX(-TILE_SIZE / 2.0f);
			}
			else if (movingVector.x < 0 && getRight() < TILE_SIZE / 2.0f)
			{
				setX(WINDOW_WIDTH - TILE_SIZE / 2.0f);
			}
		}

		/* y movement */
		if (jumping) {
			movingVector.y += PLAYER_GRAVITY * dt;
			if (movingVector.y < 0)
			{
				jumping = false;
			}
		}
		/* fall if not on platform and not jumping */
		if (!onPlatform && !jumping)
		{
			movingVector.y += PLAYER_FALLING_SPEED * dt;
		}

		/* limit max y speed */
		if (movingVector.y > PLAYER_MAX_FALLING_SPEED)
			movingVector.y = PLAYER_MAX_FALLING_SPEED;
		else if (movingVector.y < PLAYER_MAX_JUMPING_SPEED)
			movingVector.y = PLAYER_MAX_JUMPING_SPEED;

		/* move with collision check and jump trigger */
		translate(0, movingVector.y * dt);
		if (game->getGameState()->isColliding(*this))
		{
			translate(0, -movingVector.y * dt);
			movingVector.y = 0;
		}
		else
		{
			/* check if out of screen on y -> enter on the opposite site */
			if (movingVector.y > 0 && getTop() > WINDOW_HEIGHT - TILE_SIZE / 2.0f)
			{
				setY(-TILE_SIZE / 2.0f);
			}
			else if (movingVector.y < 0 && getBottom() < TILE_SIZE / 2.0f)
			{
				setY(WINDOW_HEIGHT - TILE_SIZE / 2.0f);
			}
		}
	}

	/* reset stuff */
	onPlatform = false;
}

void Player::setJumping(bool jumping)
{
	this->jumping = jumping;
}

void Player::setOnIce(bool onIce)
{
	this->onIce = onIce;
}

void Player::setOnPlatform(bool onPlatform)
{
	this->onPlatform = onPlatform;
}
bool Player::isJumping()
{
	return jumping;
}
void Player::jump(int speed)
{
	jumping = true;
	movingVector.y = speed;
}

/* try to jump on space press */
void Player::onSpacePressed()
{
	/* only jump if grounded = on floor (checked with player floor collision object) */
	if (grounded)
	{
		if (jumping)
		{
			jumping = false;
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				jump(PLAYER_JUMPING_SPEED);
			}
		}
	}
}

sf::Vector2f Player::getMovingVector()
{
	return movingVector;
}

void Player::setMovingVector(sf::Vector2f movingVector)
{
	this->movingVector = movingVector;
}

