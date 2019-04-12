#include "gamestate.hpp"

#include "../game.hpp"
#include "../util/constants.hpp"
#include "../gameobjects/guiobjects/background.hpp"
#include "../gameobjects/tileobjects/block.hpp"
#include "../gameobjects/tileobjects/player.hpp"
#include "../gameobjects/tileobjects/sting.hpp"
#include "../gameobjects/tileobjects/platform.hpp"
#include "../gameobjects/tileobjects/star.hpp"
#include "../util/tilemap.hpp"

#include <fstream>
#include <sstream>

GameState::GameState(Game *game) :
	State(game),
	backgroundSky(Background(game, "background_sky")),
	player(Player(game, -10.0f, -10.0f)),
	tileMap(TileMap(game)) {}

GameState::~GameState()
{
	/* call tilemap deconstructor */
	tileMap.~TileMap();
}

/* window events (keyboard / mouse single shot) */
void GameState::processWindowEvent(sf::Event &event)
{
	/* (if window in focus) */
	if (game->isWindowHasFocus())
	{
		if (event.type == sf::Event::KeyPressed)
		{
			/* map editor (only in debug) */
			if (DEBUG)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::E:
					/* e key = next level */
					finish();
					break;

				case sf::Keyboard::C:
					/* keyboard input (save / load map, change brushtileid) */
					/* c key = clear map */
					tileMap.clearMap();
					std::cout << "cleared map!" << std::endl;
					break;
				case sf::Keyboard::S:
					/* s key = save map */
					if (tileMap.saveMapToFile(std::string("map_tmp.txt")))
					{
						std::cout << "saved map. blocks: " << tileMap.getTiles().size() << std::endl;
					}
					else {
						std::cout << "failed to save map!!" << std::endl;
					}
					break;
				case sf::Keyboard::L:
					/* l key = load map */
					/* load map from file*/
					if (tileMap.loadMapFromFile(std::string("map_tmp.txt")))
					{
						std::cout << "loaded map from file! blocks: " << tileMap.getTiles().size() << std::endl;
					}
					else {
						std::cout << "failed to load map from file!!" << std::endl;
					}
					break;
				case sf::Keyboard::Add:
					/* + key = incr brushtileid */
					brushTileId++;
					if (brushTileId > MAX_TILE_ID)
					{
						brushTileId = MAX_TILE_ID;
					}
					std::cout << "brushtileid: " << brushTileId << std::endl;
					break;
				case sf::Keyboard::Subtract:
					/* - key = decr brushtileid */
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
					{
						brushTileId--;
						if (brushTileId < 0) {
							brushTileId = 0;
						}
						std::cout << "brushtileid: " << brushTileId << std::endl;
					}
					break;
				}
			}
		}

	}
}

Player &GameState::getPlayer()
{
	return player;
}

bool GameState::isColliding(Tile &other)
{
	bool collision = false;
	/* player collision only if platform */
	if (player != other)
	{
		if (Platform* platform = dynamic_cast<Platform*>(&other))
		{
			if (player.isColliding(other))
			{
				collision = true;

			}
		}
	}
	return tileMap.isColliding(other) || collision;
}

bool GameState::loadCurrentLevel()
{
	return tileMap.loadMapFromFile(std::string("lvl/" + std::to_string(currentLevel) + ".txt")) ? true : false;
}

/* finish level & load next level */
void GameState::finish()
{
	currentLevel++;

	player.setMovingVector(sf::Vector2f(0.0f, 0.0f));

	if (!loadCurrentLevel())
	{
		std::cerr << "failed to load level " << currentLevel << std::endl;
		currentLevel--;
		reset();
	}
	else {
		/* no error while loading */
		//game->getResourceManager().getSound("game_finish")->play();
	}
}

/* reset (e.g. when player died) */
void GameState::reset()
{
	player.setTilePosition(tileMap.getPlayerStart().x, tileMap.getPlayerStart().y);
	player.setMovingVector(sf::Vector2f(0.0f, 0.0f));

	tileMap.reset(); /* reset tiles */

	//game->getResourceManager().getSound("game_reset")->play();
}

void GameState::changeStarsCollected(int changeValue)
{
	starsCollected += changeValue;
	changeValue > 0 ?
		(std::cout << "+ collected stars: " << starsCollected << std::endl) :
		(std::cout << "- collected stars: " << starsCollected << std::endl);
}

/* temp */
void GameState::mapEditor()
{
	/* mouse input (place / remove block) */
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		/* add block (right mouse) */
		tileMap.addTile(brushTileId,
			static_cast<int>(sf::Mouse::getPosition(game->getRenderWindow()).x / TILE_SIZE),
			static_cast<int>(sf::Mouse::getPosition(game->getRenderWindow()).y / TILE_SIZE));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		/* remove block (left mouse) */
		tileMap.removeTile(
			static_cast<int>(sf::Mouse::getPosition(game->getRenderWindow()).x / TILE_SIZE),
			static_cast<int>(sf::Mouse::getPosition(game->getRenderWindow()).y / TILE_SIZE));
	}
}

void GameState::update(float dt)
{
	/* only in debug version (if window is focused) */
	if (DEBUG && game->isWindowHasFocus())
	{
		mapEditor();
	}

	/* game */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.onSpacePressed();
	}


	/* update custom sprite */
	backgroundSky.update(dt);
	tileMap.update(dt);
	player.update(dt);
}

void GameState::draw()
{
	backgroundSky.draw();
	tileMap.draw();
	player.draw();
}
