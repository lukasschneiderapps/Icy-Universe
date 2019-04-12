#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Tile;
class TileMap {
public:
	TileMap(Game *game);
	~TileMap();

	void update(float dt);
	void draw();
	void reset();
	void clearMap();
	bool saveMapToFile(std::string fileName);
	bool loadMapFromFile(std::string fileName);
	bool loadMap(std::string &data);
	void addTile(int tileId, int tileX, int tileY);
	void removeTile(int tileX, int tileY);
	Tile *getTile(int tileX, int tileY); /* returns nullptr if doesnt exist */
	sf::Vector2f &getPlayerStart();

	bool isColliding(Tile &other);

	std::vector<Tile*> getTiles();

private:
	Game *game;
	std::vector<Tile*> tiles;
	sf::Vector2f playerStart;
};
