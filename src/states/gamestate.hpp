#pragma once

#include "state.hpp"

#include "../gameobjects/guiobjects/background.hpp"
#include "../gameobjects/tileobjects/player.hpp"
#include "../util/tilemap.hpp"
#include "../game.hpp"

class Tile;
class GameState : public State
{
public:
	GameState(Game *game);
	~GameState();

	void processWindowEvent(sf::Event &event) override;

	Player &getPlayer();
	bool isColliding(Tile &other);
	bool loadCurrentLevel();
	void finish();
	void reset();
	void changeStarsCollected(int changeValue);

private:
	void update(float dt) override;
	void draw() override;

	void mapEditor(); /* temp */

private:
	Background backgroundSky;
	Player player;
	TileMap tileMap;

	int brushTileId = 0;
	int currentLevel = 1;
	int starsCollected = 0;
};

