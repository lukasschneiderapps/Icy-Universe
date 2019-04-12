#pragma once

#include "state.hpp"

#include "../gameobjects/guiobjects/background.hpp"
#include "../gameobjects/tileobjects/player.hpp"
#include "../gameobjects/guiobjects/button.hpp"
#include "../util/tilemap.hpp"

class Tile;
class MenuState : public State
{
public:
	MenuState(Game *game);

	void processWindowEvent(sf::Event &event) override;
	void onButtonPressed(Button *button) override;

private:
	void update(float dt) override;
	void draw() override;

private:
	Background backgroundMenu;
	Button startButton;
};

