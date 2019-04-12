#include "menustate.hpp"

#include "../game.hpp"
#include "../util/constants.hpp"
#include "../gameobjects/guiobjects/background.hpp"
#include "../util/tilemap.hpp"

#include <fstream>
#include <sstream>

MenuState::MenuState(Game *game) :
	State(game),
	backgroundMenu(Background(game, "background_menu")),
	startButton(Button(game, std::string("button_start"), 4, 6))
{
}

/* window events (keyboard / mouse single shot) */
void MenuState::processWindowEvent(sf::Event &event)
{
}

void MenuState::onButtonPressed(Button *button)
{
	if (startButton == *button)
	{
		game->setCurrentState(STATE_GAME);
	}
}

void MenuState::update(float dt)
{
	backgroundMenu.update(dt);
	startButton.update(dt);
}

void MenuState::draw()
{
	backgroundMenu.draw();
	startButton.draw();
}