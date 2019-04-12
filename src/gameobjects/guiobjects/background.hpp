#pragma once

#include "../customsprite.hpp"

class GameState;
class Background : public CustomSprite
{
public:
	Background(Game *game, std::string textureName);
};

