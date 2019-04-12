#pragma once

#include <SFML/Graphics.hpp>

class GameState;
class Game;
class ResourceManager;
class CustomSprite
{
public:
	CustomSprite(Game *game, std::string textureName, int tileX, int tileY);

	virtual void update(float dt);
	virtual void draw();
	void setTilePosition(int tileX, int tileY);
	void setPosition(float x, float y);
	void setX(float x);
	void setY(float y);
	void setScale(float scale);
	void setScale(float scaleX, float scaleY);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	float getX();
	float getY();
	int getTileX();
	int getTileY();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	void translate(float x, float y);
	float getWidth();
	float getHeight();

	void updateGlobalBounds();

	sf::Sprite &getSprite();
	sf::FloatRect &getGlobalBounds();

	bool operator==(CustomSprite &other);
	bool operator!=(CustomSprite &other);

protected:
	sf::FloatRect globalBounds;
	sf::RenderWindow *renderWindow;
	Game *game;
	sf::Sprite sprite;
};

