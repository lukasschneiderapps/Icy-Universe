#include "tilemap.hpp"

#include "../states/gamestate.hpp"
#include "../util/constants.hpp"
#include "../gameobjects/tileobjects/tile.hpp"
#include "../gameobjects/tileobjects/player.hpp"
#include "../gameobjects/tileobjects/sting.hpp"
#include "../gameobjects/tileobjects/actiontile.hpp"
#include "../gameobjects/tileobjects/platform.hpp"
#include "../gameobjects/tileobjects/block.hpp"
#include "../gameobjects/tileobjects/star.hpp"
#include "../game.hpp"

#include <fstream>
#include <sstream>

TileMap::TileMap(Game *game) :
	game(game),
	playerStart(-10.0f, -10.0f) {}

TileMap::~TileMap()
{
	for (Tile *tile : tiles)
	{
		delete tile;
	}
	tiles.clear();
}

void TileMap::update(float dt)
{
	for (Tile *tile : tiles)
	{
		tile->update(dt);
	}
}

void TileMap::draw()
{
	for (Tile *tile : tiles)
	{
		tile->draw();
	}
}

void TileMap::reset()
{
	for (Tile *tile : tiles)
	{
		tile->reset();
	}
}

bool TileMap::saveMapToFile(std::string fileName)
{
	std::ofstream file;
	file.open(fileName);

	if (file.is_open())
	{
		for (Tile *tile : tiles)
		{
			file << tile->getTileId() << "a" << tile->getTileX() << "a" << tile->getTileY() << "b";
		}

		file.close();
		return true;
	}

	return false;
}

bool TileMap::loadMapFromFile(std::string fileName)
{
	std::cout << "loading map " << fileName << std::endl;

	std::ifstream file;
	file.open(fileName);

	if (file.is_open())
	{
		std::string data;
		std::getline(file, data);
		file.close();

		return loadMap(data);
	}

	return false;
}

bool TileMap::loadMap(std::string &data)
{
	/* clear tiles from old map */
	clearMap();

	/* split data into single tiles (by 'b') */
	std::stringstream dataStream(data);
	std::string tileToAdd_;
	std::vector<std::string> tilesToAdd;

	while (std::getline(dataStream, tileToAdd_, 'b'))
	{
		tilesToAdd.push_back(tileToAdd_);
	}

	/* iterate trough them, get props by splitting it by a and add it to tiles */
	for (std::string tileToAdd : tilesToAdd)
	{
		std::stringstream tileToAddStream(tileToAdd);
		std::string tileProperty;
		std::vector<std::string> tileProperties;

		while (std::getline(tileToAddStream, tileProperty, 'a'))
		{
			tileProperties.push_back(tileProperty);
		}

		/* add it if size of props == 3 */
		if (tileProperties.size() == 3)
		{
			addTile(std::stoi(tileProperties.at(0)), std::stoi(tileProperties.at(1)), std::stoi(tileProperties.at(2)));
		}
	}

	game->getGameState()->getPlayer().setTilePosition(getPlayerStart().x, getPlayerStart().y);

	return true;
}

void TileMap::clearMap()
{
	/* remove all tiles from vector */
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		delete tiles.at(i);
	}
	tiles.clear();
}


/* add tile to map */
void TileMap::addTile(int tileId, int tileX, int tileY)
{
	/* must be in screen range */
	if (free && (tileX >= 0 && tileX <= TILES_X - 1 && tileY >= 0 && tileY <= TILES_Y - 1))
	{
		/* check if there already is a block */
		bool free = true;
		for (unsigned int i = 0; i < tiles.size(); i++)
		{
			if (tiles.at(i)->getTileX() == tileX && tiles.at(i)->getTileY() == tileY)
			{
				/* don't add a tile */
				free = false;
				return;
			}
		}

		/* if tile is start tile -> set player start position */
		if (tileId == TILE_START)
		{
			//playerStart = sf::Vector2f(tileX + 1.0f / 8.0f, tileY + 1.0f / 8.0f);
			playerStart = sf::Vector2f(tileX, tileY);
			std::cout << "spawn: " << tileX << "," << tileY << std::endl;
		}

		/* add tile to map */
		switch (tileId)
		{
		case TILE_BLOCK_ICE:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_PLAYER:
			/* don't add player */
			std::cerr << "won't add player!" << std::endl;
			break;
		case TILE_STING_ICE_UP:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_START:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_FINISH:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_BOUNCY:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_STONE:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_SPEED_UP_RIGHT:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_SPEED_UP_LEFT:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_SPEED_UP_UP:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_SPEED_UP_DOWN:
			tiles.push_back(new ActionTile(game, tileId, tileX, tileY));
			break;
		case TILE_STAR:
			tiles.push_back(new Star(game, tileX, tileY));
			break;
		case TILE_STING_ICE_DOWN:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_LEFT:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_RIGHT:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_SMALL_UP:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_SMALL_DOWN:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_SMALL_LEFT:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_STING_ICE_SMALL_RIGHT:
			tiles.push_back(new Sting(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_STONE_SMALL_VERTICAL:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_STONE_SMALL_HORIZONTAL:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_ICE_SMALL_VERTICAL:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_ICE_SMALL_HORIZONTAL:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		case TILE_PLATFORM_STONE_VERTICAL:
			tiles.push_back(new Platform(game, tileId, tileX, tileY));
			break;
		case TILE_PLATFORM_STONE_HORIZONTAL:
			tiles.push_back(new Platform(game, tileId, tileX, tileY));
			break;
		case TILE_BLOCK_FIRE:
			tiles.push_back(new Block(game, tileId, tileX, tileY));
			break;
		default:
			/* error */
			std::cerr << "failed to add tile : unknown tile id!! " << tileId << std::endl;
		}
	}
	else
		std::cerr << "failed to add tile : not in screen range!! " << std::endl;
}


void TileMap::removeTile(int tileX, int tileY)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i)->getTileX() == tileX && tiles.at(i)->getTileY() == tileY)
		{
			Tile *t = tiles.at(i);
			tiles.erase(tiles.begin() + i);
			delete t;
			i--;
		}
	}
}

Tile *TileMap::getTile(int tileX, int tileY)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i)->getTileX() == tileX && tiles.at(i)->getTileY() == tileY)
		{
			return tiles.at(i);
		}
	}

	return nullptr;
}

sf::Vector2f &TileMap::getPlayerStart()
{
	return playerStart;
}

bool TileMap::isColliding(Tile &other)
{
	bool collision = false;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (*tiles.at(i) != other && tiles.at(i)->isColliding(other))
		{
			collision = true;
		}
	}
	return collision;
}

std::vector<Tile*> TileMap::getTiles()
{
	return tiles;
}
