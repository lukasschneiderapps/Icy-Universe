#include "background.hpp"

#include "../../game.hpp"

Background::Background(Game *game, std::string textureName) :
	CustomSprite(game, textureName, 0, 0) {}