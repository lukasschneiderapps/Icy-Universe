#include "customsprite.hpp"

#include "../states/gamestate.hpp"
#include "../game.hpp"
#include "../util/resourcemanager.hpp"
#include "../util/constants.hpp"

CustomSprite::CustomSprite(Game *game, std::string textureName, int tileX, int tileY) :
	game(game),
	renderWindow(&game->getRenderWindow())
{
	sprite.setTexture(*(game->getResourceManager().getTexture(textureName)));
	setPosition(TILE_SIZE * tileX, TILE_SIZE * tileY);

	updateGlobalBounds();
}

void CustomSprite::update(float dt)
{
}

void CustomSprite::draw()
{
	renderWindow->draw(sprite);
}

void CustomSprite::setTilePosition(int tileX, int tileY)
{
	sprite.setPosition(TILE_SIZE * tileX, TILE_SIZE * tileY);
	updateGlobalBounds();
}

void CustomSprite::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	updateGlobalBounds();
}

void CustomSprite::setX(float x)
{
	sprite.setPosition(x, getY());
	updateGlobalBounds();
}

void CustomSprite::setY(float y)
{
	sprite.setPosition(getX(), y);
	updateGlobalBounds();
}

void CustomSprite::setScale(float scale)
{
	sprite.setScale(scale, scale);
	updateGlobalBounds();
}

void CustomSprite::setScale(float scaleX, float scaleY)
{
	sprite.setScale(scaleX, scaleY);
	updateGlobalBounds();
}


void CustomSprite::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
	updateGlobalBounds();
}

sf::Vector2f CustomSprite::getPosition()
{
	return sprite.getPosition();
}

float CustomSprite::getX()
{
	return globalBounds.left;
}
float CustomSprite::getY()
{
	return globalBounds.top;
}

int CustomSprite::getTileX()
{
	return static_cast<int>(globalBounds.left / TILE_SIZE);
}

int CustomSprite::getTileY()
{
	return static_cast<int>(globalBounds.top / TILE_SIZE);
}

float CustomSprite::getLeft()
{
	return globalBounds.left;
}
float CustomSprite::getRight()
{
	return  globalBounds.left + globalBounds.width;
}

float CustomSprite::getTop()
{
	return globalBounds.top;
}

float CustomSprite::getBottom()
{
	return  globalBounds.top + globalBounds.height;
}

void CustomSprite::translate(float x, float y)
{
	sprite.move(x, y);
	updateGlobalBounds();
}

float CustomSprite::getWidth()
{
	return globalBounds.width;
}

float CustomSprite::getHeight()
{
	return globalBounds.height;
}

void CustomSprite::updateGlobalBounds()
{
	globalBounds = sprite.getGlobalBounds();
}

sf::Sprite &CustomSprite::getSprite()
{
	return sprite;
}

sf::FloatRect &CustomSprite::getGlobalBounds()
{
	return globalBounds;
}

bool CustomSprite::operator==(CustomSprite &other)
{
	return (this == &other) ? true : false;
}

bool CustomSprite::operator!=(CustomSprite &other)
{
	return (this == &other) ? false : true;
}
