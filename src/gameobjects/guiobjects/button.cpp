#include "button.hpp"

#include "../../game.hpp"
#include "../../states/state.hpp"

#include <iostream>

Button::Button(Game *game, std::string textureName, int tileX, int tileY) :
	CustomSprite(game, textureName, tileX, tileY)
{
	rectUnhovered.left = 0;
	rectUnhovered.top = 0;
	rectUnhovered.width = getWidth();
	rectUnhovered.height = static_cast<int>(getHeight() / 2.0f);

	rectHovered.left = 0;
	rectHovered.top = static_cast<int>(getHeight() / 2.0f);
	rectHovered.width = getWidth();
	rectHovered.height = static_cast<int>(getHeight() / 2.0f);

	sprite.setTextureRect(rectUnhovered);

	updateGlobalBounds();
}

void Button::update(float dt)
{
	sf::Vector2f mousePos = game->getMousePosition();
	hovered = globalBounds.contains(mousePos);

	sprite.setTextureRect(hovered ? rectHovered : rectUnhovered);

	if (hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (!clickDown)
		{
			clickDown = true;
			//game->getResourceManager().getSound("button_click")->play();
		}
	}
	else {
		if (clickDown)
		{
			clickDown = false;
			if (hovered)
			{
				game->getCurrentState()->onButtonPressed(this);
			}
		}
	}
}
