#include "state.hpp"

#include "../gameobjects/guiobjects/button.hpp"
#include "../util/resourcemanager.hpp"
#include "../game.hpp"

State::State(Game *game) :
	game(game) {}

State::~State() {}

/* process state */
void State::processState(float dt)
{
	update(dt);
	draw();
}

void State::onButtonPressed(Button * button) {}

void State::processWindowEvent(sf::Event &event)
{
	/* override with code */
}

Game *State::getGame()
{
	return game;
}

/* to be overwritten */
void State::update(float dt) {}
void State::draw() {}
