#pragma once

#include "../customsprite.hpp"

class Button : public CustomSprite
{
public:
	Button(Game *game, std::string textureName, int tileX, int tileY);

	void update(float dt) override;

private:
	sf::IntRect rectHovered;
	sf::IntRect rectUnhovered;

	bool hovered = false;
	bool clickDown = false;
};
