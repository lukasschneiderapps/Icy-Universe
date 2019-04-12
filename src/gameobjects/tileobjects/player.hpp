#pragma once

#include "tile.hpp"

#include "playerfloorcollider.hpp"

#include <SFML/Graphics.hpp>

class GameState;
class Player : public Tile
{
public:
	Player(Game *game, float x, float y);

	void update(float dt) override;
	sf::Vector2f getMovingVector();
	void setMovingVector(sf::Vector2f movingVector);
	void jump(int speed);
	void onSpacePressed();
	void setJumping(bool jumping);
	void setOnIce(bool onIce);
	void setOnPlatform(bool onPlatform);
	bool isJumping();

private:
	PlayerFloorCollider playerFloorCollider;
	sf::Vector2f movingVector;
	bool grounded = false;
	bool jumping = false;
	bool onIce = false;
	bool onPlatform = false;
};

